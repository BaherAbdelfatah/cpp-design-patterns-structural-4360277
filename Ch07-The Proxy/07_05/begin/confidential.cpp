#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Storage
{
public:
    virtual const string getContents() = 0;
    virtual ~Storage() = default;
};

class SecureStorage : public Storage
{
public:
    explicit SecureStorage(const string &data) : m_Contents(data) {}

    const string getContents() override
    {
        return m_Contents;
    }

private:
    const string m_Contents;
};

class SecureStorageProxy : public Storage {
public:
    explicit SecureStorageProxy(const string &data, const int code) : m_SecureStorage(std::make_unique<SecureStorage>(data)), m_SecretCode(code) {}

    const string getContents() override
    {
        if (true == authorized()) {
            return m_SecureStorage->getContents();
        } else {
            return "Not Authorized";
        }
    }
private:
    bool authorized() {
        return m_SecretCode == 42;
    }
    std::unique_ptr<SecureStorage> m_SecureStorage;
    const int m_SecretCode;
};

int main()
{
    SecureStorageProxy secureStorage("Top Secret Information", 42);

    // Limit access to sensitive data
    cout << "Sensitive Data: " << secureStorage.getContents() << endl;

    return 0;
}