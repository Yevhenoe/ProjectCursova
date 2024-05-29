#include "restaurant.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

// Ingredient class implementation
Ingredient::Ingredient(const wstring& name) {
    this->name = name;
}

wstring Ingredient::getName() const {
    return name;
}

// Dish class implementation
Dish::Dish(const wstring& name) {
    this->name = name;
}

void Dish::addIngredient(const Ingredient& ingredient) {
    ingredients.push_back(ingredient);
}

wstring Dish::getName() const {
    return name;
}

vector<Ingredient> Dish::getIngredients() const {
    return ingredients;
}

// PriceList class implementation
void PriceList::addDish(const Dish& dish, double price) {
    dishNames.push_back(dish.getName());
    dishes.push_back(dish);
    prices.push_back(price);
}

double PriceList::getPrice(const wstring& dishName) const {
    for (size_t i = 0; i < dishNames.size(); ++i) {
        if (dishNames[i] == dishName) {
            return prices[i];
        }
    }
    return 0.0;
}

Dish PriceList::getDish(const wstring& dishName) const {
    for (size_t i = 0; i < dishNames.size(); ++i) {
        if (dishNames[i] == dishName) {
            return dishes[i];
        }
    }
    throw invalid_argument("Страву не знайдено");
}

void PriceList::displayMenu() const {
    wcout << L"Меню:\n";
    for (size_t i = 0; i < dishNames.size(); ++i) {
        wcout << dishNames[i] << L" - $" << prices[i] << L"\n";
        wcout << L"Інгредієнти: ";
        const auto& ingredients = dishes[i].getIngredients();
        for (size_t j = 0; j < ingredients.size(); ++j) {
            wcout << ingredients[j].getName();
            if (j != ingredients.size() - 1) {
                wcout << L", ";
            }
        }
        wcout << L"\n";
    }
}

// Order class implementation
void Order::addDish(const wstring& dishName, int portion) {
    bool found = false;
    for (size_t i = 0; i < dishNames.size(); ++i) {
        if (dishNames[i] == dishName) {
            portions[i] += portion;
            found = true;
            break;
        }
    }
    if (!found) {
        dishNames.push_back(dishName);
        portions.push_back(portion);
    }
}

double Order::calculateTotal(const PriceList& priceList) const {
    double total = 0.0;
    for (size_t i = 0; i < dishNames.size(); ++i) {
        total += priceList.getPrice(dishNames[i]) * portions[i];
    }
    return total;
}

wstring Order::toString() const {
    wstring result;
    for (size_t i = 0; i < dishNames.size(); ++i) {
        result += dishNames[i] + L": " + to_wstring(portions[i]) + L" порцій\n";
    }
    return result;
}

// Function to initialize multiple ingredients
vector<Ingredient> initializeIngredients(const vector<wstring>& ingredientNames) {
    vector<Ingredient> ingredients;
    for (const wstring& name : ingredientNames) {
        ingredients.push_back(Ingredient(name));
    }
    return ingredients;
}

// Function to initialize multiple dishes
vector<Dish> initializeDishes(const vector<wstring>& dishNames, const vector<vector<wstring>>& ingredientsForDishes) {
    vector<Dish> dishes;
    for (size_t i = 0; i < dishNames.size(); ++i) {
        Dish dish(dishNames[i]);
        for (const wstring& ingredientName : ingredientsForDishes[i]) {
            dish.addIngredient(Ingredient(ingredientName));
        }
        dishes.push_back(dish);
    }
    return dishes;
}