#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Mock class for database library
class Database
{
public:
    void storeReservation(const string &reservation)
    {
        cout << "Database: Storing reservation: " << reservation << endl;
    }
};

// Mock class for payment gateway
class PaymentGateway
{
public:
    void processPayment(const string &paymentInfo)
    {
        cout << "Payment Gateway: Processing payment with info: " << paymentInfo << endl;
    }
};

// Mock class for messaging service
class MessagingService
{
public:
    void sendConfirmation(const string &message)
    {
        cout << "Messaging Service: Sending confirmation message: " << message << endl;
    }
};

class ReservationSystemFacade {
public:
    ReservationSystemFacade() : m_Database(), m_PaymentGateway(), m_MessagingService() {}

    void MakeReservation(const std::string& reservationInfo, const std::string& paymentInfo) {
        m_Database.storeReservation(reservationInfo);
        m_PaymentGateway.processPayment(paymentInfo);
        m_MessagingService.sendConfirmation("Reservation confirmed.");
    }
private:
    Database m_Database;
    PaymentGateway m_PaymentGateway;
    MessagingService m_MessagingService;
};

int main()
{
    ReservationSystemFacade reservationSystem;

    const string reservation = "Room reservation info";
    const string paymentInfo = "Payment info";

    reservationSystem.MakeReservation(reservation, paymentInfo);
    return 0;
}
