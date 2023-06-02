#include <iostream>
#include <memory>

using namespace std;

class ITextHandler {
public:
  virtual std::string prepareMessage(const std::string &text) const = 0;
  virtual ~ITextHandler() = default;
};

class ITextSharer {
public:
  explicit ITextSharer(const ITextHandler &handler) : m_textHandler(handler) {}

  bool shareText(const std::string &text) {
    const std::string preparedText = m_textHandler.prepareMessage(text);
    return sharePreparedText(preparedText);
  }

  virtual ~ITextSharer() = default;

protected:
  virtual bool sharePreparedText(const std::string &text) = 0;

private:
  const ITextHandler &m_textHandler;
};

class PlainTextHandler : public ITextHandler {
public:
  std::string prepareMessage(const std::string &text) const override {
    std::cout << "PlainTextHandler::prepareMessage() returning original text..." << std::endl;
    return text;
  }
};

class EmailShare : public ITextSharer {
public:
  explicit EmailShare(const PlainTextHandler &handler) : ITextSharer(handler) {}
protected:
  bool sharePreparedText(const std::string &text) override {
    std::cout << "EmailShare::shareText() sharing text: " << text << std::endl;
    return true;
  }
};

class SMSShare : public ITextSharer {
public:
  explicit SMSShare(const PlainTextHandler &handler) : ITextSharer(handler) {}
protected:
  bool sharePreparedText(const std::string &text) override {
    std::cout << "SMSShareEncrypted::shareText() sharing text: " << text << std::endl;
    return true;
  }
};


class EncryptedTextHandler : public ITextHandler {
public:
  std::string prepareMessage(const std::string &text) const override {
    std::cout << "EncryptedTextHandler::prepareMessage() encrypting text..." << std::endl;
    std::string encrypted = xorEncrypted(text);
    return encrypted;
  }
private:
  std::string xorEncrypted(const std::string &input) const {
    char key = 64;
    std::string output = input;

    for (int i = 0; i < input.size(); ++i) {
      output[i] = input[i] ^ key;
    }
    return output;
  }
};

class EmailShareEncrypted : public ITextSharer {
public:
  explicit EmailShareEncrypted(const EncryptedTextHandler &handler) : ITextSharer(handler) {}
protected:
  bool sharePreparedText(const std::string &text) override {
    std::cout << "EmailShareEncrypted::shareText() sharing text: " << text << std::endl;
    return true;
  }
};

class SMSShareEncrypted : public ITextSharer {
public:
  explicit SMSShareEncrypted(const EncryptedTextHandler &handler) : ITextSharer(handler) {}
protected:
  bool sharePreparedText(const std::string &text) override {
    std::cout << "SMSShareEncrypted::shareText() sharing text: " << text << std::endl;
    return true;
  }
};

int main()
{
  PlainTextHandler handler{};
  EncryptedTextHandler encryptedHandler{};
  // Create an array of pointers to CloudStorage objects.
    const std::unique_ptr<ITextSharer> sharingServices[]
    {
        make_unique<EmailShare>(handler),
        make_unique<SMSShare>(handler),
        make_unique<EmailShareEncrypted>(encryptedHandler),
        make_unique<SMSShareEncrypted>(encryptedHandler)
    };

    // Iterate through the array and invoke the uploadContents and getFreeSpace
    // methods on each object
    const string content = "Beam me up, Scotty!";
    for (const auto& service : sharingServices)
    {        
        service->shareText(content);
        cout << endl;
    }

    return 0;
}