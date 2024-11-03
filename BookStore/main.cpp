// BookStore.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <limits> 
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
Book* pNewBook;         // Указатель на очередную книгу

//-------------------- ПРОТОТИПЫ ФУНКЦИЙ ---------------------------

int askSelectOption(int& choice);                                               // Функция вывода списка опций и запроса на выбор
int inputOption1(string& book, string& author, int& year, int& price);          // Функция запроса данных для опции Добавить книгу
int inputOption4(int&choice);                                                   // Функция запроса данных для опции Показать все книги
int inputOption5(int& minPrice, int& maxPrice);                                 // Функция запроса данных для опции Найти книги в ценовом диапазоне

int main()
{
    system("chcp 1251");
    newStore = BookStore();
    paramMain = findBiggestWidths(newStore.getBookList());  // Определяем размеры столбцов по умолчанию
    

    // Основной цикл
    cout << "\nДобро пожаловать в программу магазин книг!\n" << endl;
    while (1) {

        if (askSelectOption(option) != 0) {                                     // Вывести список опций и прочитать ввод + проверить на ошибки
            continue;
        }

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option == 1) { // Добавить книгу
            
            if (inputOption1(bookMain, authorMain, yearMain, priceMain) != 0) { // Запросить ввод полей
                continue;
            } // if
            
            pNewBook = new Book(bookMain, authorMain, yearMain, priceMain);
            newStore.addBook(pNewBook);
            cout << "\n\nКнига успешно добавлена!" << endl;

            paramMain = findBiggestWidths(newStore.getBookList());              // Обновляем размеры столбцов

        } // if 1

        else if (option == 2) { // Удалить книгу

            cout << "\nВведите название книги: "; getline(cin, bookMain);
            newStore.removeBook(bookMain);                                     // Удаление книги
            paramMain = findBiggestWidths(newStore.getBookList());             // Обновляем размеры столбцов

        } // else if 2

        else if (option == 3) { // Найти книгу по названию
            
            cout << "\nВведите название книги: "; getline(cin, bookMain);
            Book* target = newStore.findBook(bookMain);                        // Поиск книги

            if (target == NULL) {
                cout << "\nКнига не найдена. " << endl;
                continue;
            } // if

            list<Book*> oneBook{ target };                                     // Инициализация списка для вывода ответа в виде таблицы
            newStore.PrintConstrainedList(oneBook, paramMain);                 // Печать таблицы

        } // else if 3

        else if (option == 4) { // Показать все книги(сортировка по названию / автору / году издания)

            if (inputOption4(option) != 0) {                                            // Запросить ввод критерия сортировки
                continue;
            } // if

            SortType optionType = static_cast<SortType>(option);                        // Перевод номера опции option в SortType
            newStore.PrintConstrainedList(newStore.listBooks(optionType), paramMain);   // Печать отсортированного списка

        } // else if 4

        else if (option == 5) {  // Найти книги в ценовом диапазоне

            if (inputOption5(minPrice, maxPrice) != 0) {    // Если ошибка ввода
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



// ---------------- РЕАЛИЗАЦИЯ ФУНКЦИЙ ------------------

int askSelectOption(int& choice) {

    cout << "1. Добавить книгу\n"
        << "2. Удалить книгу" <<
        "\n3. Найти книгу по названию\n" <<
        "4. Показать все книги(сортировка по названию / автору / году издания)\n" <<
        "5. Найти книги в ценовом диапазоне\n"
        << "6. Выйти\n"
        << "Выберете опцию:";
    cin >> choice;

    if (cin.fail()) { // проверить на букву
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nВведите, пожалуйста, номер варианта (число)\n" << endl;
        return 1;
    } // if

    return 0;

} // askSelectOption

int inputOption1(string& book, string& author, int& year, int& price) {

    cout << "\nВведите название книги: "; getline(cin, book);
    cout << "\nВведите автора книги: "; getline(cin, author);
    cout << "\nВведите год издания: "; cin >> year;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nНекорректный тип\n";
        return 1;
    } // if

    cout << "\nВведите цену: "; cin >> price;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nНекорректный тип\n";
        return 1;
    } // if
    return 0;

} // inputOption1

int inputOption4(int& choice) {

    cout << "\nПоля сортировки: "
        << "\n0 - сортировка по названию"
        << "\n1 - сортировка по автору"
        << "\n2 - сортировка по году издания";
    cout << "\nВыберете число: ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nНекорректный тип" << endl;
        return 1;
    } // if
    if (choice < 0 || choice>2) {                                               // choice м.б. только из {0,1,2}
        cout << "\nНекорректное число" << endl;
        return 1;
    } // if

    return 0;

} // inputOption4

int inputOption5(int& minPrice, int& maxPrice) {

    cout << "\nВведите минимальную цену: "; cin >> minPrice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nНекорректный тип" << endl;
        return 1;
    } // if

    cout << "\nВведите максимальную цену: "; cin >> maxPrice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nНекорректный тип" << endl;
        return 1;
    } // if

    if (maxPrice < minPrice) {
        cout << "\nМаксимальная цена д.б. больше минимальной!" << endl;
        return 1;
    } // if

    return 0;

} // inputOption5
