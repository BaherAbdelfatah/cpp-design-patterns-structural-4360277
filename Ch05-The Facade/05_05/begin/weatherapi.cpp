#include <iostream>
#include <string>
#include <tuple>
#include <sstream>

using namespace std;

class WorldWeatherAPI
{
public:
    tuple<float, float, string> getWeather(string location)
    {
        cout << "Calling worldWeather with location: " << location << endl;
        float temperature = 20.0f;
        float windSpeed = 5.5f;
        string shortDescription = "Sunny";
        return make_tuple(temperature, windSpeed, shortDescription);
    }
};

class FreeWeather
{
public:
    tuple<float, string> retrieve_weather(string location)
    {
        cout << "Calling freeWeather with location: " << location << endl;
        float temperature = 22.0f;
        string shortDescription = "Sunny";
        return make_tuple(temperature, shortDescription);
    }
};

class RealtimeWeatherService
{
public:
    tuple<float, float, string> weatherConditions(string location)
    {
        cout << "Calling realtimeWeather with location: " << location << endl;
        float temperature = 19.5f;
        float humidity = 60.0f;
        string shortDescription = "Partly cloudy with a chance of rain";
        return make_tuple(temperature, humidity, shortDescription);
    }
};

class WeatherFacade {
public:
    WeatherFacade() : m_WorldWeather(), m_FreeWeather(), m_RealtimeWeather() {}

    const std::string CurrentWeather(string location) {
        // Call each API and combine the results
        tuple<float, float, string> worldWeatherResult = m_WorldWeather.getWeather(location);
        tuple<float, string> freeWeatherResult = m_FreeWeather.retrieve_weather(location);
        tuple<float, float, string> realtimeWeatherResult = m_RealtimeWeather.weatherConditions(location);

        // Combine the results into a single string
        float temperature = get<0>(worldWeatherResult);
        float humidity = get<1>(realtimeWeatherResult);
        string shortDescription = get<1>(freeWeatherResult);

        std::stringstream result;

        result << "\nWeather for " << location << endl
            << shortDescription << endl
            << "Temperature: " << temperature << " C" << endl
            << "Humidity: " << humidity << " %" << endl;

        return result.str();
    }
private:
    WorldWeatherAPI m_WorldWeather;
    FreeWeather m_FreeWeather;
    RealtimeWeatherService m_RealtimeWeather;
};

int main()
{
    WeatherFacade weatherFacade;

    auto const location = "San Francisco, CA, US";
    // Call CurrentWeather API to combine the results
    cout << weatherFacade.CurrentWeather(location) << endl;

    return 0;
}
