// BookStore.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//#include <windows.h>
#include <limits> // Include limits for numeric_limits
//#undef max // Undefine the max macro

#include <iostream>
#include "classes.h"
#include <string>

using namespace std;

//--------------------- ПЕРЕМЕННЫЕ -------------------------------
int option;             // выбранная пользователем команда
BookStore newStore;     // объект BookStore
string bookMain;
string authorMain;
int yearMain;
int priceMain;
TableParams paramMain;  // Параметры для рисования таблицы
int minPrice, maxPrice; // ценовой диапазон



int main()
{
    //SetConsoleCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "Russian");
    newStore = BookStore();
    paramMain = findBiggestWidths(newStore.getBookList());  // Определяем размеры столбцов по умолчанию

    // Основной цикл
    cout << "Добро пожаловать в программу магазин книг!" << endl;
    while (1) {
        cout<< "1. Добавить книгу\n"
            << "2. Удалить книгу" <<
            "\n3.Найти книгу по названию\n" <<
            "4.Показать все книги(сортировка по названию / автору / году издания)\n" <<
            "5.Найти книги в ценовом диапазоне\n"
            << "6.Выйти\n"
            << "Выберете опцию:";
        cin >> option;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (cin.fail()) { // проверить на число
            cout << "\nВведите, пожалуйста, номер варианта (число)\n" << endl;
            continue;
        } // if

        if (option == 1) { // Добавить книгу
            

            cout << "\nВведите название книги: "; getline(cin, bookMain);
            cout << "\nВведите автора книги: "; getline(cin, authorMain);
            cout << "\nВведите год издания: "; cin >> yearMain;
            if (cin.fail()) {
                cout << "\nНекорректный тип\n";
                continue;
            } // if
            cout << "\nВведите цену: "; cin >> priceMain;
            if (cin.fail()) {
                cout << "\nНекорректный тип\n";
                continue;
            } // if
            Book newBook = Book(bookMain, authorMain, yearMain, priceMain);
            newStore.addBook(&newBook);
            cout << "\n\nКнига успешно добавлена!" << endl;
            cout << bookMain << "\t" << authorMain << endl;

            paramMain = findBiggestWidths(newStore.getBookList());  // Обновляем размеры столбцов

        } // if 1

        else if (option == 2) { // Удалить книгу

            cout << "\nВведите название книги: "; getline(cin, bookMain);
            newStore.removeBook(bookMain);
            paramMain = findBiggestWidths(newStore.getBookList());  // Обновляем размеры столбцов

        } // else if 2

        else if (option == 3) { // Найти книгу по названию
            
            cout << "\nВведите название книги: "; getline(cin, bookMain);
            Book* target = newStore.findBook(bookMain);
            if (target == NULL) {
                cout << "\nКнига не найдена. " << endl;
                continue;
            } // if

            list<Book*> oneBook{ target };          // Инициализация списка для вывода ответа в виде таблицы
            newStore.PrintConstrainedList(oneBook, paramMain);      // Печать таблицы

        } // else if 3

        else if (option == 4) { // Показать все книги(сортировка по названию / автору / году издания)

            cout << "\nПоля сортировки: " 
                << "\n0 - сортировка по названию"
                << "\n1 - сортировка по автору"
                << "\n2 - сортировка по году издания";
            cout << "\nВыберете число: ";
            cin >> option;

            if (cin.fail()) {
                cout << "\nНекорректный тип" << endl;
                continue;
            } // if
            if (option < 0 || option>2) {                                               // option м.б. только из {0,1,2}
                cout << "\nНекорректное число" << endl;
                continue;
            } // if

            SortType optionType = static_cast<SortType>(option);                        // Перевод номера опции option в SortType
            newStore.PrintConstrainedList(newStore.listBooks(optionType), paramMain);   // Печать отсортированного списка

        } // else if 4

        else if (option == 5) {  // Найти книги в ценовом диапазоне

            cout << "\nВведите минимальную цену: "; cin >> minPrice;
            if (cin.fail()) {
                cout << "\nНекорректный тип" << endl;
                continue;
            } // if

            cout << "\nВведите максимальную цену: "; cin >> maxPrice;
            if (cin.fail()) {
                cout << "\nНекорректный тип" << endl;
                continue;
            } // if

            if (maxPrice < minPrice) {
                cout << "\nМаксимальная цена д.б. больше минимальной!" << endl;
                continue;
            } // if

            newStore.PrintConstrainedList(newStore.findBooksInPriceRange(minPrice, maxPrice), paramMain);   // Печать списка книг из ценового диапазона

        } // else if 5

        else if (option == 6) {

            cout << "\nВы выходите из программы магазина книг.\n";
            return 0;

        } // else if 6

        else {

            cout << "\nВведите номер от 1 до 6\n";
            continue;

        } // else
        
    } // while
} // main

