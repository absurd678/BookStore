#pragma once
#include <iostream>
#include <iterator>
#include <list>
using namespace std;




//---------------------------- Класс Перечисление ----------------------------------
enum class SortType { Title, Author, Year };												// Перечисление для выбора поля сортировки


//------------------- Класс Book -------------------------------
class Book {

private:
	char* bookName;		// Название книги
	char* authorName;	// Имя автора
	int year;			// Год издания
	int price;			// Цена книги
	SortType cmpCriterium;   // Сортировка по заголовку/автору/году

public:
	Book(char* init_bookName, char* init_authorName, int init_year, int init_price);	// Создать книгу
	~Book(){}																			// Деструктор

	char* getBookName() { return bookName; }											// Получить поле названия
	char* getAuthorName() { return authorName; }										// Получить Имя автора
	int getYear() { return year; }														// Получить Год издания
	int getPrice() { return price; }													// Получить Цену книги
	SortType getCmpCriterium() { return cmpCriterium; }									// Получить Сравнение по заголовку/автору/году

	void setBookName(char * newBookName) { bookName = newBookName; }					// Изменить поле названия
	void setAuthorName(char* newAuthorName) { authorName = newAuthorName; }				// Изменить Имя автора
	void setYear(int newYear) { year= newYear; }										// Изменить Год издания
	void setPrice(int newPrice) { price = newPrice; }									// Изменить Цену книги
	void setCmpCriterium(SortType newCmpCriterium) { cmpCriterium = newCmpCriterium; }	// Изменить Сравнение по заголовку/автору/году

	// Перегрузка операторов сравнения (для корректной сортировки)

	friend bool operator==(Book Book1, Book Book2) {

		switch (Book1.getCmpCriterium()) {
		case SortType::Title:
			return Book1.getBookName()[0] == Book2.getBookName()[0];
		case SortType::Author:
			return Book1.getAuthorName()[0] == Book2.getAuthorName()[0];
		case SortType::Year:
			return Book1.getYear() == Book2.getYear();
		default:
			cout << "Неизвестный параметр сортировки книг" << endl;
			return false;
		} // switch
	} // operator==

	friend bool operator<(Book Book1, Book Book2) {

		switch (Book1.getCmpCriterium()) {
		case SortType::Title:
			return Book1.getBookName()[0] < Book2.getBookName()[0];
		case SortType::Author:
			return Book1.getAuthorName()[0] < Book2.getAuthorName()[0];
		case SortType::Year:
			return Book1.getYear() < Book2.getYear();
		default:
			cout << "Неизвестный параметр сортировки книг" << endl;
			return false;
		} // switch
	} // operator<

	friend bool operator>(Book Book1, Book Book2) {

		switch (Book1.getCmpCriterium()) {
		case SortType::Title:
			return Book1.getBookName()[0] > Book2.getBookName()[0];
		case SortType::Author:
			return Book1.getAuthorName()[0] > Book2.getAuthorName()[0];
		case SortType::Year:
			return Book1.getYear() > Book2.getYear();
		default:
			cout << "Неизвестный параметр сортировки книг" << endl;
			return false;
		} // switch
	} // operator>

}; // Book


//--------------------- Структура параметров таблицы, в которой содержатся данные о книгах -----------------------
struct TableParams {
	int colBookName;		// Ширина столбца 1 (bookName)
	int colAuthorName;		// Ширина столбца 2 (authorName)
	int colYear;			// Ширина столбца 3 (year)
	int colPrice;			// Ширина столбца 4 (price)
}; // TableParams

// Служебные функции для вывода таблицы
TableParams findBiggestWidths(list<Book*> anyBookList);	// Ф-я нахождения самых длинных имен
void PrintHeaders(TableParams param);					// Ф-я печати заголовков
void PrintLine(TableParams param);						// Ф-я печати разделяющей линии
void PrintContent(TableParams param, Book* pBook);		// Ф-я печати данных о книге


//---------------------------- Класс BookStore -------------------------------------
class BookStore {

private:
	list<Book*> BookList;																// Контейнер книг

public:
	BookStore() { list<Book*> BookList{}; }												// Создание контейнера
	~BookStore() {}																		// Деструктор

	list<Book*> getBookList() { return BookList; }										// Получить Контейнер книг
	void addBook(Book* _book);															//— добавляет новую книгу в магазин.
	void removeBook(char* _title);														//— удаляет книгу по названию.
	Book* findBook(char* _title);														//— находит книгу по названию и возвращает указатель на неё(если книга найдена).
	list<Book*> listBooks(SortType sortType);											//— возвращает список всех книг, отсортированных по названию, автору или году издания(в зависимости от значения аргумента SortType).
	list<Book*> findBooksInPriceRange(int minPrice, int maxPrice);						//— возвращает <корректный_контейнер> книг, цена которых находится в указанном диапазоне.
	void PrintConstrainedList(list<Book*> anyBookList, TableParams param);				// Печать отсортированного списка книг или списка с ценой в диапазоне или данного списка

}; // BookStore