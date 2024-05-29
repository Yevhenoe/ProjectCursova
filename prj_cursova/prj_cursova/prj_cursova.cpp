#include "restaurant.h"
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void displayMenu() {
    wcout << L"1. Переглянути меню\n";
    wcout << L"2. Додати страву до замовлення\n";
    wcout << L"3. Переглянути поточне замовлення\n";
    wcout << L"4. Порахувати загальну суму\n";
    wcout << L"5. Вийти\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Ukrainian");

    // Ініціалізація інгредієнтів
    vector<wstring> ingredientNames = { L"Помідор", L"Сир", L"Тісто", L"Соус", L"Листя салату", L"Курка" };
    vector<Ingredient> ingredients = initializeIngredients(ingredientNames);

    // Ініціалізація страв
    vector<wstring> dishNames = { L"Піца", L"Салат", L"Курячий сендвіч" };
    vector<vector<wstring>> ingredientsForDishes = {
        {L"Помідор", L"Сир", L"Тісто", L"Соус"},
        {L"Листя салату", L"Помідор", L"Сир"},
        {L"Курка", L"Листя салату", L"Помідор", L"Соус"}
    };
    vector<Dish> dishes = initializeDishes(dishNames, ingredientsForDishes);

    // Створення прейскуранту
    PriceList priceList;
    priceList.addDish(dishes[0], 12.99); // Додавання піци
    priceList.addDish(dishes[1], 6.99);  // Додавання салату
    priceList.addDish(dishes[2], 8.99);  // Додавання курячого сендвічу

    // Створення замовлення
    Order order;

    int choice;
    while (true) {
        displayMenu();
        wcout << L"Введіть ваш вибір: ";
        cin >> choice;
        system("CLS");
        if (choice == 1) {
            wcout << L"\n";
            priceList.displayMenu();
            wcout << L"\n";
        }
        else if (choice == 2) {
            wstring dishName;
            int portion;
            wcout << L"Введіть назву страви: ";
            cin.ignore();
            getline(wcin, dishName);
            wcout << L"Введіть кількість порцій: ";
            cin >> portion;
            order.addDish(dishName, portion);
            wcout << L"Додано " << portion << L" порцій " << dishName << L" до замовлення.\n";
        }
        else if (choice == 3) {
            wcout << L"Поточне замовлення:\n" << order.toString();
        }
        else if (choice == 4) {
            wcout << L"Загальна сума: $" << order.calculateTotal(priceList) << L"\n";
        }
        else if (choice == 5) {
            wcout << L"Вихід...\n";
            break;
        }
        else {
            wcout << L"Невірний вибір. Спробуйте ще раз.\n";
        }
    }

    return 0;
}