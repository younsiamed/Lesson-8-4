#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <stdexcept>

class IFormatter {
public:
    virtual ~IFormatter() = default;
    virtual std::string format(const std::string& data) const = 0;
};

class HTMLFormatter : public IFormatter {
public:
    std::string format(const std::string& data) const override {
        return "<html>" + data + "</html>";
    }
};

class TextFormatter : public IFormatter {
public:
    std::string format(const std::string& data) const override {
        return data;
    }
};

class JSONFormatter : public IFormatter {
public:
    std::string format(const std::string& data) const override {
        return "{ \"data\": \"" + data + "\" }";
    }
};

class Data {
public:
    Data(std::string data, std::shared_ptr<IFormatter> formatter)
        : data_(std::move(data)), formatter_(std::move(formatter)) {}

    std::string print() const {
        return formatter_->format(data_);
    }

private:
    std::string data_;
    std::shared_ptr<IFormatter> formatter_;
};

void saveTo(std::ofstream& file, const Data& data) {
    file << data.print();
}

int main() {
    std::ofstream file("output.html");

    Data dataHTML("Hello, World!", std::make_shared<HTMLFormatter>());
    saveTo(file, dataHTML);

    file.close();

    return 0;
}
