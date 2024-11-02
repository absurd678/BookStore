//------------------------���� � ����������� ������� �������----------------------------------
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include "classes.h"
using namespace std;

//-----------------------���������--------------------------
const int minColBookName = 10;
const int minColAuthorName = 7;
const int minColYear = 5;
const int minColPrice = 6;


// -------------------------������� ������ �������-------------------------------------------

TableParams findBiggestWidths(list<Book*> anyBookList) {	// �-� ���������� ����� ������� ����

	TableParams newParam{ minColBookName,minColAuthorName,minColYear,minColPrice };					// ����������� ��������� ������ ������� �������

	list<Book*>::iterator pBook;
	for (pBook = anyBookList.begin(); pBook != anyBookList.end(); pBook++) {

		int priceLen = (int)log10(((*pBook)->getPrice()))+1; // ���-�� ���� � ����� price
		int yearLen = (int)log10(((*pBook)->getYear())) + 1; // ���-�� ���� � ����� year

		if (strlen((*pBook)->getBookName()) > newParam.colBookName) {		// �������� ����� ���� bookName
			newParam.colBookName = strlen((*pBook)->getBookName()) + 2;
		}
		if (strlen((*pBook)->getAuthorName()) > newParam.colAuthorName) {   // �������� ����� ���� authorName
			newParam.colAuthorName = strlen((*pBook)->getAuthorName()) + 2;
		}
		if (yearLen > newParam.colYear) {									// �������� ����� ���� year
			newParam.colYear = yearLen + 2;
		}
		if (priceLen > newParam.colPrice) {									// �������� ����� ���� price
			newParam.colPrice = priceLen + 2;
		}

	} // for

	return newParam;
} // findBiggestWidths

void PrintHeaders(TableParams param)					// �-� ������ ����������
{
	cout << "+" << setfill('-') << setw(param.colBookName) << "+" << setfill('-') << setw(param.colAuthorName) << "+" << setfill('-') << setw(param.colYear) << "+" << setfill('-') << setw(param.colPrice) << "+" << endl;
	cout << "|" << "��������" << setfill(' ') << setw(param.colBookName - minColBookName + 2) << "|" << "�����" << setfill(' ') << setw(param.colAuthorName - minColAuthorName + 2) << "|" << "���" << setfill(' ') << setw(param.colYear - minColYear + 2) << "|" << "����" << setfill(' ') << setw(param.colPrice - minColPrice + 2) << "|" << endl;
	cout << "+" << setfill('-') << setw(param.colBookName) << "+" << setfill('-') << setw(param.colAuthorName) << "+" << setfill('-') << setw(param.colYear) << "+" << setfill('-') << setw(param.colPrice) << "+" << endl;
} // PrintHeaders

void PrintLine(TableParams param)						// �-� ������ ����������� �����
{
	cout << "+" << setfill('-') << setw(param.colBookName) << "+" << setfill('-') << setw(param.colAuthorName) << "+" << setfill('-') << setw(param.colYear) << "+" << setfill('-') << setw(param.colPrice) << "+" << endl;
} // PrintLine

void PrintContent(TableParams param, Book* pBook)		// �-� ������ ������ � �����
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

//-------------------------����� Book--------------------------------

Book::Book(char* init_bookName, char* init_authorName, int init_year, int init_price) {
	bookName = init_bookName;
	authorName = init_authorName;
	year = init_year;
	price = init_price;
	cmpCriterium = SortType::Title; // �� ��������� - �������� Title
} // Book


//-------------------------����� BookStore--------------------------------

void BookStore::addBook(Book* _book) {															//� ��������� ����� ����� � �������.
	BookList.push_back(_book);
} // addBook

void BookStore::removeBook(char* _title) {														//� ������� ����� �� ��������.
	
	Book* target = findBook(_title);
	if (target == NULL) {
		cout << "����� �� �������." << endl;
		return;
	}
	cout << "������� �����: " << target->getBookName()<<endl;
	BookList.remove(target);

} // removeBook

Book* BookStore::findBook(char* _title) {														//� ������� ����� �� �������� � ���������� ��������� �� ��(���� ����� �������).
	
	list<Book*>::iterator pBook;
	for (pBook = BookList.begin(); pBook != BookList.end(); pBook++) {
		if (strcmp(_title, (*pBook)->getBookName()) == 0) {
			return *pBook;
		}
	}
	
	return NULL;							// ����� �� ������� => NULL
} // findBook

void BookStore::PrintConstrainedList(list<Book*> anyBookList, TableParams param) {									// ������ ���������������� ������ ���� ��� ������ � ����� � ��������� ��� ������� ������
	list<Book*>::iterator pbook;
	
	PrintHeaders(param);
	for (pbook = anyBookList.begin(); pbook != anyBookList.end(); pbook++) {
		PrintLine(param);
		PrintContent(param, *pbook);
		PrintLine(param);
	} // for
	
} // PrintConstrainedList

list<Book*> BookStore::listBooks(SortType sortType) {											//� ���������� ������ ���� ����, ��������������� �� ��������, ������ ��� ���� �������(� ����������� �� �������� ��������� SortType).
	
	int bookAmount = BookList.size();								// ���-�� ����
	list<Book*> sortedList{};										// ��������������� ������
	Book** BookArray = new Book * [bookAmount];						// ������ ���� ��� ���������� ���������
	int i, j;														// ���������� ��� ������� �� ������� 
	
	if (bookAmount == 1) return BookList;							// ������� ��� �� ������, ���� ����� ����� ���� 
	
	// ��������� ������ � ������
	list<Book*>::iterator pBook;
	i = 0;
	for (pBook = BookList.begin(); pBook != BookList.end(); pBook++) {
		(*pBook)->setCmpCriterium(sortType);
		BookArray[i] = *pBook;
		i++;
	} // for

	// ����������� ������
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

	// ��������� ������ � ����� ��������������� ������
	for (i = 0; i < bookAmount; i++) {
		sortedList.push_back(BookArray[i]);
	} // for

	return sortedList;
} // listBooks

list<Book*> BookStore::findBooksInPriceRange(int minPrice, int maxPrice) {
	list<Book*> filteredList{}; // ������ � ������� � �������� ������� ���������

	// ��������� ������ � ������
	list<Book*>::iterator pBook;
	for (pBook = BookList.begin(); pBook != BookList.end(); pBook++) {
		if ((*pBook)->getPrice() >= minPrice && (*pBook)->getPrice() <= maxPrice) {
			filteredList.push_back((*pBook));
		} // if
	} // for

	return filteredList;
}