#pragma once

#include <string>
#include <vector>

class Ingredient {
public:
    explicit Ingredient(const std::wstring& name);
    std::wstring getName() const;

private:
    std::wstring name;
};

class Dish {
public:
    explicit Dish(const std::wstring& name);
    void addIngredient(const Ingredient& ingredient);
    std::wstring getName() const;
    std::vector<Ingredient> getIngredients() const;

private:
    std::wstring name;
    std::vector<Ingredient> ingredients;
};

class PriceList {
public:
    void addDish(const Dish& dish, double price);
    double getPrice(const std::wstring& dishName) const;
    Dish getDish(const std::wstring& dishName) const;
    void displayMenu() const;

private:
    std::vector<std::wstring> dishNames;
    std::vector<Dish> dishes;
    std::vector<double> prices;
};

class Order {
public:
    void addDish(const std::wstring& dishName, int portion);
    double calculateTotal(const PriceList& priceList) const;
    std::wstring toString() const;

private:
    std::vector<std::wstring> dishNames;
    std::vector<int> portions;
};

std::vector<Ingredient> initializeIngredients(const std::vector<std::wstring>& ingredientNames);
std::vector<Dish> initializeDishes(const std::vector<std::wstring>& dishNames, const std::vector<std::vector<std::wstring>>& ingredientsForDishes);