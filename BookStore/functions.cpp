//------------------------���� � ����������� ������� �������----------------------------------
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include "classes.h"
using namespace std;


// -------------------------������� ������ �������-------------------------------------------

TableParams findBiggestWidths(list<Book*> anyBookList) {	// �-� ���������� ����� ������� ����
	
	// ������� � Year ����� �� ��������, � � ������������, ��� � ���� ����� ������ 4 �����

	TableParams newParam{ 0,0,0,0 };					// ����������� ��������� ������ ������� �������

	list<Book*>::iterator pBook;
	for (pBook = anyBookList.begin(); pBook != anyBookList.end(); pBook++) {

		int priceLen = (int)log10(((*pBook)->getPrice()))+1; // ���-�� ���� � ����� price

		if (strlen((*pBook)->getBookName()) > newParam.colBookName) {		// �������� ����� ���� bookName
			newParam.colBookName = strlen((*pBook)->getBookName());
		}
		if (strlen((*pBook)->getAuthorName()) > newParam.colAuthorName) {   // �������� ����� ���� authorName
			newParam.colAuthorName = strlen((*pBook)->getAuthorName());
		}
		if (priceLen > newParam.colPrice) {									// �������� ����� ���� price
			newParam.colPrice = priceLen;
		}

	} // for

	return newParam;
} // findBiggestWidths

void PrintHeaders(TableParams param)					// �-� ������ ����������
{
	cout << char(218) << setfill(char(196)) << setw(param.colBookName) << char(194) << setfill(char(196)) << setw(width) << char(194) << setfill(char(196)) << setw(width) << char(194) << setfill(char(196)) << setw(width) << char(191) << endl;
	cout << char(179) << 'N' << setfill(' ') << setw(width - 1) << char(179) << 'X' << setfill(' ') << setw(width - 1) << char(179) << "F(x)" << setfill(' ') << setw(width - 4) << char(179) << "G(x)" << setfill(' ') << setw(width - 4) << char(179) << endl;

}
void PrintLine(TableParams param);						// �-� ������ ����������� �����
void PrintContent(TableParams param, Book* pBook);		// �-� ������ ������ � �����

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
		BookArray[i] = *pBook;
		i++;
	} // for

	// ����������� ������
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

	// ��������� ������ � ����� ��������������� ������
	for (i = 0; i < bookAmount; i++) {
		sortedList.push_back(BookArray[i]);
	} // for

	return sortedList;
} // listBooks