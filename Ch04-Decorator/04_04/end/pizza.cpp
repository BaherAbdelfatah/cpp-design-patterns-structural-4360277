#include <iostream>
#include <memory>

class Pizza
{
public:
    virtual std::string description() const = 0;
    virtual double price() const = 0;
    virtual ~Pizza() = default;
};

class ToppingDecorator : public Pizza
{
public:
    explicit ToppingDecorator(std::unique_ptr<Pizza> pizza) : m_Pizza(std::move(pizza)) {}

    virtual ~ToppingDecorator() = default;

    std::string description() const override
    {
        return m_Pizza->description();
    }

    double price() const override
    {
        return m_Pizza->price();
    }

protected:
    std::unique_ptr<Pizza> m_Pizza;
};

class MargheritaPizza : public Pizza
{
public:
    std::string description() const override
    {
        return "Margherita Pizza";
    }

    double price() const override
    {
        return 9.99;
    }
};

class HawaiianPizza : public Pizza
{
public:
    std::string description() const override
    {
        return "Hawaiian Pizza";
    }

    double price() const override
    {
        return 11.99;
    }
};

class PepperoniPizza : public Pizza
{
public:
    std::string description() const override
    {
        return "Pepperoni Pizza";
    }

    double price() const override
    {
        return 12.99;
    }
};

class MushroomDecorator: public ToppingDecorator {
public:
    explicit MushroomDecorator(std::unique_ptr<Pizza> pizza) : ToppingDecorator(std::move(pizza)) {}

    std::string description() const override
    {
        return ToppingDecorator::description() + " with mushroom";
    }

    double price() const override
    {
        return m_Pizza->price() + 2.00;
    }
};

class TomatoDecorator: public ToppingDecorator {
public:
    explicit TomatoDecorator(std::unique_ptr<Pizza> pizza) : ToppingDecorator(std::move(pizza)) {}

    std::string description() const override
    {
        return ToppingDecorator::description() + " with tomato";
    }

    double price() const override
    {
        return m_Pizza->price() + 1.50;
    }
};

class ExtraCheeseDecorator: public ToppingDecorator {
public:
    explicit ExtraCheeseDecorator(std::unique_ptr<Pizza> pizza) : ToppingDecorator(std::move(pizza)) {}

    std::string description() const override
    {
        return ToppingDecorator::description() + " with extra cheese";
    }

    double price() const override
    {
        return m_Pizza->price() + 2.50;
    }
};

int main()
{
    // MargheritaPizza with mushrooms and extra cheese
    auto margheritaPizza = std::make_unique<MargheritaPizza>();
    auto margheritaWithMushrooms = std::make_unique<MushroomDecorator>(std::move(margheritaPizza));
    auto margheritaExtraCheeseMushrooms = std::make_unique<ExtraCheeseDecorator>(std::move(margheritaWithMushrooms));

    std::cout << margheritaExtraCheeseMushrooms->description() << " costs $" << margheritaExtraCheeseMushrooms->price() << std::endl;

    // Pepperoni pizza with mushrooms, tomatoes, and extra cheese
    auto pepperoniPizza = std::make_unique<PepperoniPizza>();
    auto pepperoniWithMushrooms = std::make_unique<MushroomDecorator>(std::move(pepperoniPizza));
    auto pepperoniWithTomatoMushrooms = std::make_unique<TomatoDecorator>(std::move(pepperoniWithMushrooms));
    auto pepperoniTomatoMushroomsExtraCheese = std::make_unique<ExtraCheeseDecorator>(std::move(pepperoniWithTomatoMushrooms));

    std::cout << pepperoniTomatoMushroomsExtraCheese->description() << " costs $" << pepperoniTomatoMushroomsExtraCheese->price() << std::endl;

    return 0;
}
