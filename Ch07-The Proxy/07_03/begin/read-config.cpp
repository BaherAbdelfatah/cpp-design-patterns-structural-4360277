#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Define an abstract base class for our configuration file
class ConfigFile
{
public:
    virtual vector<string> getSettings() = 0;
    virtual ~ConfigFile() = default;
};

// Define a concrete implementation of the ConfigFile
class RealConfigFile : public ConfigFile
{
public:
    explicit RealConfigFile(const string &filename)
    {
        cout << "RealConfigFile created." << endl;
        // Open the file and read its contents into a vector of strings
        ifstream file(filename);
        string line;
        while (getline(file, line))
        {
            settings.push_back(line);
        }
        cout << settings.size() << " settings loaded." << endl;
    }

    vector<string> getSettings() override
    {
        return settings;
    }

private:
    vector<string> settings;
};

class ConfigFileProxy : public ConfigFile {
public:
    explicit ConfigFileProxy(const string &filename) : filename(filename), realConfigFile(nullptr) {
        std::cout << "ConfigFileProxy created." << std::endl;
    }

    vector<string> getSettings() override
    {
        if (nullptr == realConfigFile) {
            realConfigFile = std::make_unique<RealConfigFile>(filename);
        }
        return realConfigFile->getSettings();
    }

private:
    std::string filename;
    std::unique_ptr<RealConfigFile> realConfigFile;
};

int main()
{
    ConfigFileProxy configFile("config.txt");

    bool useSettings = true;

    if (useSettings)
    {
        vector<string> settings = configFile.getSettings();
        for (const auto &setting : settings)
        {
            cout << setting << endl;
        }
    }
    else
    {
        cout << "Configuration not used." << endl;
    }

    return 0;
}
