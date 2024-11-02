//------------------------ФАЙЛ С РЕАЛИЗАЦИЕЙ МЕТОДОВ КЛАССОВ----------------------------------
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include "classes.h"
using namespace std;

//-----------------------КОНСТАНТЫ--------------------------
const int minColBookName = 10;
const int minColAuthorName = 7;
const int minColYear = 5;
const int minColPrice = 6;


// -------------------------Функции вывода таблицы-------------------------------------------

TableParams findBiggestWidths(list<Book*> anyBookList) {	// Ф-я нахождения самых длинных имен

	TableParams newParam{ minColBookName,minColAuthorName,minColYear,minColPrice };					// Минимальные параметры ширины каждого столбца

	list<Book*>::iterator pBook;
	for (pBook = anyBookList.begin(); pBook != anyBookList.end(); pBook++) {

		int priceLen = (int)log10(((*pBook)->getPrice()))+1; // кол-во цифр в числе price
		int yearLen = (int)log10(((*pBook)->getYear())) + 1; // кол-во цифр в числе year

		if (strlen((*pBook)->getBookName()) > newParam.colBookName) {		// Проверка длины поля bookName
			newParam.colBookName = strlen((*pBook)->getBookName()) + 2;
		}
		if (strlen((*pBook)->getAuthorName()) > newParam.colAuthorName) {   // Проверка длины поля authorName
			newParam.colAuthorName = strlen((*pBook)->getAuthorName()) + 2;
		}
		if (yearLen > newParam.colYear) {									// Проверка длины поля year
			newParam.colYear = yearLen + 2;
		}
		if (priceLen > newParam.colPrice) {									// Проверка длины поля price
			newParam.colPrice = priceLen + 2;
		}

	} // for

	return newParam;
} // findBiggestWidths

void PrintHeaders(TableParams param)					// Ф-я печати заголовков
{
	cout << "+" << setfill('-') << setw(param.colBookName) << "+" << setfill('-') << setw(param.colAuthorName) << "+" << setfill('-') << setw(param.colYear) << "+" << setfill('-') << setw(param.colPrice) << "+" << endl;
	cout << "|" << "Название" << setfill(' ') << setw(param.colBookName - minColBookName + 2) << "|" << "Автор" << setfill(' ') << setw(param.colAuthorName - minColAuthorName + 2) << "|" << "Год" << setfill(' ') << setw(param.colYear - minColYear + 2) << "|" << "Цена" << setfill(' ') << setw(param.colPrice - minColPrice + 2) << "|" << endl;
	cout << "+" << setfill('-') << setw(param.colBookName) << "+" << setfill('-') << setw(param.colAuthorName) << "+" << setfill('-') << setw(param.colYear) << "+" << setfill('-') << setw(param.colPrice) << "+" << endl;
} // PrintHeaders

void PrintLine(TableParams param)						// Ф-я печати разделяющей линии
{
	cout << "+" << setfill('-') << setw(param.colBookName) << "+" << setfill('-') << setw(param.colAuthorName) << "+" << setfill('-') << setw(param.colYear) << "+" << setfill('-') << setw(param.colPrice) << "+" << endl;
} // PrintLine

void PrintContent(TableParams param, Book* pBook)		// Ф-я печати данных о книге
{
	int BookNameLen = strlen(pBook->getBookName());
	int AuthorNameLen = strlen(pBook->getAuthorName());
	int YearLen = (int)log10(((pBook)->getYear())) + 1;
	int PriceLen = (int)log10(((pBook)->getPrice())) + 1;

	cout << "|" << pBook->getBookName() << setfill(' ') << setw(param.colBookName - BookNameLen) << "|"
		<< pBook->getAuthorName() << setfill(' ') << setw(param.colAuthorName - AuthorNameLen) << "|"
		<< pBook->getYear() << setfill(' ') << setw(param.colYear - YearLen) << "|"
		<< pBook->getPrice() << setfill(' ') << setw(param.colPrice - PriceLen) << "|" << endl;

} // PrintContent

//-------------------------Класс Book--------------------------------

Book::Book(char* init_bookName, char* init_authorName, int init_year, int init_price) {
	bookName = init_bookName;
	authorName = init_authorName;
	year = init_year;
	price = init_price;
	cmpCriterium = SortType::Title; // По умолчанию - критерий Title
} // Book


//-------------------------Класс BookStore--------------------------------

void BookStore::addBook(Book* _book) {															//— добавляет новую книгу в магазин.
	BookList.push_back(_book);
} // addBook

void BookStore::removeBook(char* _title) {														//— удаляет книгу по названию.
	
	Book* target = findBook(_title);
	if (target == NULL) {
		cout << "Книга не найдена." << endl;
		return;
	}
	cout << "Удалена книга: " << target->getBookName()<<endl;
	BookList.remove(target);

} // removeBook

Book* BookStore::findBook(char* _title) {														//— находит книгу по названию и возвращает указатель на неё(если книга найдена).
	
	list<Book*>::iterator pBook;
	for (pBook = BookList.begin(); pBook != BookList.end(); pBook++) {
		if (strcmp(_title, (*pBook)->getBookName()) == 0) {
			return *pBook;
		}
	}
	
	return NULL;							// Книга не найдена => NULL
} // findBook

void BookStore::PrintConstrainedList(list<Book*> anyBookList, TableParams param) {									// Печать отсортированного списка книг или списка с ценой в диапазоне или данного списка
	list<Book*>::iterator pbook;
	
	PrintHeaders(param);
	for (pbook = anyBookList.begin(); pbook != anyBookList.end(); pbook++) {
		PrintLine(param);
		PrintContent(param, *pbook);
		PrintLine(param);
	} // for
	
} // PrintConstrainedList

list<Book*> BookStore::listBooks(SortType sortType) {											//— возвращает список всех книг, отсортированных по названию, автору или году издания(в зависимости от значения аргумента SortType).
	
	int bookAmount = BookList.size();								// Кол-во книг
	list<Book*> sortedList{};										// Отсортированный список
	Book** BookArray = new Book * [bookAmount];						// Массив книг для сортировки вставками
	int i, j;														// Переменные для прохода по массиву 
	
	if (bookAmount == 1) return BookList;							// Вернуть тот же список, если книга всего одна 
	
	// Скопируем список в массив
	list<Book*>::iterator pBook;
	i = 0;
	for (pBook = BookList.begin(); pBook != BookList.end(); pBook++) {
		(*pBook)->setCmpCriterium(sortType);
		BookArray[i] = *pBook;
		i++;
	} // for

	// Отсортируем массив
	for (i = 1; i < bookAmount; i++) {
		j = i - 1;
		Book* currBook = BookArray[i];
		while (j >= 0  && *BookArray[j] > *currBook ) {
			Book* temp = BookArray[j];
			BookArray[j] = BookArray[j + 1];
			BookArray[j + 1] = temp;
			j--;
		} // while
		BookArray[j + 1] = currBook;
	} // for

	// Скопируем массив в новый отсортированный список
	for (i = 0; i < bookAmount; i++) {
		sortedList.push_back(BookArray[i]);
	} // for

	return sortedList;
} // listBooks

list<Book*> BookStore::findBooksInPriceRange(int minPrice, int maxPrice) {
	list<Book*> filteredList{}; // Список с книгами в заданном ценовом диапазоне

	// Скопируем список в массив
	list<Book*>::iterator pBook;
	for (pBook = BookList.begin(); pBook != BookList.end(); pBook++) {
		if ((*pBook)->getPrice() >= minPrice && (*pBook)->getPrice() <= maxPrice) {
			filteredList.push_back((*pBook));
		} // if
	} // for

	return filteredList;
}