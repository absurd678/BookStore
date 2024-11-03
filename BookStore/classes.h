#pragma once
#include <iostream>
#include <iterator>
#include <list>
#include <string>
using namespace std;




//---------------------------- ����� ������������ ----------------------------------

enum class SortType { Title, Author, Year };												// ������������ ��� ������ ���� ����������


//------------------- ����� Book -------------------------------

class Book {

private:
	string bookName;		// �������� �����
	string authorName;	// ��� ������
	int year;			// ��� �������
	int price;			// ���� �����
	SortType cmpCriterium;   // ���������� �� ���������/������/����

public:
	Book(string init_bookName, string init_authorName, int init_year, int init_price);	// ������� �����
	~Book(){}																			// ����������

	string getBookName() { return bookName; }											// �������� ���� ��������
	string getAuthorName() { return authorName; }										// �������� ��� ������
	int getYear() { return year; }														// �������� ��� �������
	int getPrice() { return price; }													// �������� ���� �����
	SortType getCmpCriterium() { return cmpCriterium; }									// �������� ��������� �� ���������/������/����

	void setBookName(string newBookName) { bookName = newBookName; }					// �������� ���� ��������
	void setAuthorName(string newAuthorName) { authorName = newAuthorName; }				// �������� ��� ������
	void setYear(int newYear) { year= newYear; }										// �������� ��� �������
	void setPrice(int newPrice) { price = newPrice; }									// �������� ���� �����
	void setCmpCriterium(SortType newCmpCriterium) { cmpCriterium = newCmpCriterium; }	// �������� ��������� �� ���������/������/����

	// ���������� ���������� ��������� (��� ���������� ����������)

	friend bool operator==(Book Book1, Book Book2) {

		switch (Book1.getCmpCriterium()) {
		case SortType::Title:
			return Book1.getBookName()[0] == Book2.getBookName()[0];
		case SortType::Author:
			return Book1.getAuthorName()[0] == Book2.getAuthorName()[0];
		case SortType::Year:
			return Book1.getYear() == Book2.getYear();
		default:
			cout << "����������� �������� ���������� ����" << endl;
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
			cout << "����������� �������� ���������� ����" << endl;
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
			cout << "����������� �������� ���������� ����" << endl;
			return false;
		} // switch
	} // operator>

}; // Book


//--------------------- ��������� ���������� �������, � ������� ���������� ������ � ������ -----------------------

struct TableParams {
	int colBookName;		// ������ ������� 1 (bookName)
	int colAuthorName;		// ������ ������� 2 (authorName)
	int colYear;			// ������ ������� 3 (year)
	int colPrice;			// ������ ������� 4 (price)
}; // TableParams

// ��������� ������� ��� ������ �������
TableParams findBiggestWidths(list<Book*> anyBookList);	// �-� ���������� ����� ������� ����
void PrintHeaders(TableParams param);					// �-� ������ ����������
void PrintLine(TableParams param);						// �-� ������ ����������� �����
void PrintContent(TableParams param, Book* pBook);		// �-� ������ ������ � �����


//---------------------------- ����� BookStore -------------------------------------

class BookStore {

private:
	list<Book*> BookList;																// ��������� ����

public:
	BookStore() { list<Book*> BookList{}; }												// �������� ����������
	~BookStore() {}																		// ����������

	list<Book*> getBookList() { return BookList; }										// �������� ��������� ����
	void addBook(Book* _book);															//� ��������� ����� ����� � �������.
	void removeBook(string _title);														//� ������� ����� �� ��������.
	Book* findBook(string _title);														//� ������� ����� �� �������� � ���������� ��������� �� ��(���� ����� �������).
	list<Book*> listBooks(SortType sortType);											//� ���������� ������ ���� ����, ��������������� �� ��������, ������ ��� ���� �������(� ����������� �� �������� ��������� SortType).
	list<Book*> findBooksInPriceRange(int minPrice, int maxPrice);						//� ���������� <����������_���������> ����, ���� ������� ��������� � ��������� ���������.
	void PrintConstrainedList(list<Book*> anyBookList, TableParams param);				// ������ ���������������� ������ ���� ��� ������ � ����� � ��������� ��� ������� ������

}; // BookStore