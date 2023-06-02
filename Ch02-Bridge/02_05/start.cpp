#include <iostream>
#include <memory>

class IEngine {
public:
    virtual void start() const = 0;
    virtual ~IEngine() = default;
};

class IVehicle {
public:
    explicit IVehicle(IEngine& engine) : m_engine(engine) {}

    void drive() const {
        m_engine.start();
        driveVehicle();
    }

protected:
    virtual void driveVehicle() const = 0;

private:
    IEngine& m_engine;
};

class GasEngine : public IEngine {
public:
    void start() const override {
        std::cout << "GasEngine Started ...." << std::endl;
    }
};

class ElectricEngine : public IEngine {
public:
    void start() const override {
        std::cout << "ElectricEngine Started ...." << std::endl;
    }
};

class HybridEngine : public IEngine {
public:
    void start() const override {
        std::cout << "HybridEngine Started ...." << std::endl;
    }
};

class Car : public IVehicle {
public:
    Car(IEngine &engine) : IVehicle(engine) {}

    void driveVehicle() const override {
        std::cout << "Driving a Car type Vehicle...";
    }
};

class Truck : public IVehicle {
public:
    Truck(IEngine &engine) : IVehicle(engine) {}
    
    void driveVehicle() const override {
        std::cout << "Driving a Truck type Vehicle...";
    }
};

int main() {
    GasEngine gasEngine{};
    ElectricEngine electricEngine{};
    HybridEngine hybridEngine{};

    const std::unique_ptr<IVehicle> vehicles[] {
        std::make_unique<Car>(gasEngine),
        std::make_unique<Truck>(electricEngine),
        std::make_unique<Car>(hybridEngine),
    };

    for (auto &vehicle : vehicles)
    {
        vehicle->drive();
        std::cout << std::endl;
    }
}