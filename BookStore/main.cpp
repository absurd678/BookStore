// BookStore.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

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



int main()
{
    
    setlocale(LC_ALL, "");
    newStore = BookStore();
    paramMain = findBiggestWidths(newStore.getBookList());  // Определяем размеры столбцов по умолчанию

    // Основной цикл
    while (1) {
        cout<< "1. Добавить книгу\n"
            << "2. Удалить книгу" <<
            "\n3.Найти книгу по названию\n" <<
            "4.Показать все книги(сортировка по названию / автору / году издания)\n" <<
            "5.Найти книги в ценовом диапазоне\n"
            << "6.Выйти\n"
            << "Выберете опцию:";
        cin >> option; 

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

            paramMain = findBiggestWidths(newStore.getBookList());  // Обновляем размеры столбцов

        } // if 1

        else if (option == 2) { // Удалить книгу

            cout << "\nВведите название книги: "; getline(cin, bookMain);
            newStore.removeBook(bookMain);
            paramMain = findBiggestWidths(newStore.getBookList());  // Обновляем размеры столбцов

        } // if 2

        else if (option == 3) { // Найти книгу по названию
            
            cout << "\nВведите название книги: "; getline(cin, bookMain);
            Book* target = newStore.findBook(bookMain);
            if (target == NULL) {
                cout << "\nКнига не найдена. " << endl;
                continue;
            } // if

            list<Book*> oneBook{ target };          // Инициализация списка для вывода ответа в виде таблицы
            newStore.PrintConstrainedList(oneBook, paramMain);      // Печать таблицы

        } // if 3

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
            }
            
            SortType optionType = static_cast<SortType>(option);

        } // if 4

        
    } // while
} // main

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
