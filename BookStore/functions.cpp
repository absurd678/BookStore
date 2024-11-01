//------------------------ФАЙЛ С РЕАЛИЗАЦИЕЙ МЕТОДОВ КЛАССОВ----------------------------------
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include "classes.h"
using namespace std;


// -------------------------Функции вывода таблицы-------------------------------------------

TableParams findBiggestWidths(list<Book*> anyBookList) {	// Ф-я нахождения самых длинных имен
	
	// Столбец с Year можно не смотреть, т к предполагаем, что в этом числе всегда 4 цифры

	TableParams newParam{ 0,0,0,0 };					// Минимальные параметры ширины каждого столбца

	list<Book*>::iterator pBook;
	for (pBook = anyBookList.begin(); pBook != anyBookList.end(); pBook++) {

		int priceLen = (int)log10(((*pBook)->getPrice()))+1; // кол-во цифр в числе price

		if (strlen((*pBook)->getBookName()) > newParam.colBookName) {		// Проверка длины поля bookName
			newParam.colBookName = strlen((*pBook)->getBookName());
		}
		if (strlen((*pBook)->getAuthorName()) > newParam.colAuthorName) {   // Проверка длины поля authorName
			newParam.colAuthorName = strlen((*pBook)->getAuthorName());
		}
		if (priceLen > newParam.colPrice) {									// Проверка длины поля price
			newParam.colPrice = priceLen;
		}

	} // for

	return newParam;
} // findBiggestWidths

void PrintHeaders(TableParams param)					// Ф-я печати заголовков
{
	cout << char(218) << setfill(char(196)) << setw(param.colBookName) << char(194) << setfill(char(196)) << setw(width) << char(194) << setfill(char(196)) << setw(width) << char(194) << setfill(char(196)) << setw(width) << char(191) << endl;
	cout << char(179) << 'N' << setfill(' ') << setw(width - 1) << char(179) << 'X' << setfill(' ') << setw(width - 1) << char(179) << "F(x)" << setfill(' ') << setw(width - 4) << char(179) << "G(x)" << setfill(' ') << setw(width - 4) << char(179) << endl;

}
void PrintLine(TableParams param);						// Ф-я печати разделяющей линии
void PrintContent(TableParams param, Book* pBook);		// Ф-я печати данных о книге

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
		BookArray[i] = *pBook;
		i++;
	} // for

	// Отсортируем массив
	for (i = 1; i < bookAmount; i++) {
		j = i - 1;
		Book* currBook = BookArray[i];
		while (*BookArray[j] < *currBook) {
			Book* temp = BookArray[j];
			BookArray[j] = BookArray[j + 1];
			BookArray[j + 1] = temp;
			j--;
		} // while
	} // for

	// Скопируем массив в новый отсортированный список
	for (i = 0; i < bookAmount; i++) {
		sortedList.push_back(BookArray[i]);
	} // for

	return sortedList;
} // listBooks