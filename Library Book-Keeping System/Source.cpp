#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;
struct Book {
	string author;
	string title;
	string publisher;
	string genre;
	int serialNumber;
	int edition;
	int year;
};
void viewBook();
void searchBook(fstream& file, Book book);
void removeBook(Book book);
void recordBook(Book& book, fstream& file);
void editBook();
int main() {
	Book book;
	fstream file;
	int choice;
	system("color 0A");
	cout << "======WELCOME TO THE LIBRARY BOOK KEEPING SYSTEM======" << endl
		<< "Press any key to continue." << endl;
	cin.get();
	system("CLS");
	do {
		cout << "Press 1 to record book information." << endl
			<< "Press 2 to display all of the books in the inventory." << endl
			<< "Press 3 to search a book." << endl
			<< "Press 4 to edit book information." << endl
			<< "Press 5 to remove a book from the inventory" << endl
			<< "Press 6 to exit" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			recordBook(book, file);
			break;
		case 2:
			viewBook();
			break;
		case 3:
			searchBook(file, book);
			break;
		case 4:
			editBook();
			break;
		case 5:
			removeBook(book);
			break;
		case 6:
			cout << "End of program." << endl;
			break;
		default:
			cout << "Invalid input, please try again." << endl;
			break;
		}
	} while (choice != 6);
	file.close();
}
void viewBook() {
	Book information;
	fstream file("Book Inventory.txt", ios::in);
	if (!file) {
		cout << "Failed to fetch file\n.";
		exit(1);
	}
	string line;
	file.seekg(0, ios::beg);
	cout << "DISPAYING ALL BOOKS IN THE INVENTORY" << endl;
	cout << left << setw(20) << "AUTHOR" << setw(25) << "TITLE" << setw(25) << "GENRE" << setw(20) << "EDITION" << setw(20) << "PUBLISHER" << setw(10) << "Serial Number(ISBN)" << setw(10) << "YEAR" << endl;
	while (
		getline(file, information.title) &&
		getline(file, information.author) &&
		getline(file, information.genre) &&
		file >> information.edition &&
		file >> information.publisher &&
		file >> information.serialNumber &&
		file >> information.year) {
		cout << left << setw(20) << information.title << setw(25) << information.author << setw(25) << information.genre << setw(20) << information.edition << setw(20)
			<< information.publisher << setw(20) << information.serialNumber << setw(5) << information.year << endl;
		file.ignore();
	}
	file.close();
}
void searchBook(fstream& file, Book book) {
	string searchTitle;
	cout << "Enter the title of the book you want to search for: ";
	cin.ignore();
	getline(cin, searchTitle);
	file.open("Book Inventory.txt");
	if (!file)
	{
		cout << "Failed to open file." << endl;
		return;
	}
	bool found = false;
	while (getline(file, book.author))
	{
		getline(file, book.title);
		getline(file, book.genre);
		file >> book.edition;
		file.ignore();
		getline(file, book.publisher);
		file >> book.serialNumber;
		file >> book.year;
		file.ignore();
		if (book.title == searchTitle)
		{
			found = true;
			cout << "Book found. Here is the information: " << endl;
			cout << "Title: " << book.title << endl;
			cout << "Author: " << book.author << endl;
			cout << "Genre: " << book.genre << endl;
			cout << "Edition: " << book.edition << endl;
			cout << "Publisher: " << book.publisher << endl;
			cout << "Serial Number (ISBN): " << book.serialNumber << endl;
			cout << "Year: " << book.year << endl;
			break;
		}
	}
	file.close();
	if (!found)
	{
		cout << "Book not found." << endl;
	}
}
void removeBook(Book book) {
	string searchTitle;
	cout << "Enter the title of the book you want to delete: ";
	cin.ignore();
	getline(cin, searchTitle);
	ifstream inputFile("Book Inventory.txt");
	if (!inputFile)
	{
		cout << "Failed to open file." << endl;
		return;
	}
	ofstream outputFile("temp.txt");
	if (!outputFile)
	{
		cout << "Failed to create temporary file." << endl;
		inputFile.close();
		return;
	}
	bool found = false;
	while (getline(inputFile, book.author))
	{
		getline(inputFile, book.title);
		getline(inputFile, book.genre);
		inputFile >> book.edition;
		inputFile.ignore();
		getline(inputFile, book.publisher);
		inputFile >> book.serialNumber;
		inputFile >> book.year;
		inputFile.ignore();
		if (book.title != searchTitle)
		{
			outputFile << book.title << endl
				<< book.author << endl
				<< book.genre << endl
				<< book.edition << endl
				<< book.publisher << endl
				<< book.serialNumber << endl
				<< book.year << endl;
		}
		else
		{
			found = true;
		}
	}
	inputFile.close();
	outputFile.close();
	if (found)
	{
		if (remove("Book Inventory.txt") != 0)
		{
			cout << "Failed to delete the book." << endl;
			return;
		}
		if (rename("temp.txt", "Book Inventory.txt") != 0)
		{
			cout << "Failed to update the book inventory." << endl;
			return;
		}
		cout << "Book deleted successfully." << endl;
	}
	else
	{
		cout << "Book not found." << endl;
	}
}
void recordBook(Book& book, fstream& file) {
	char ans;
	int i = 0;//this variable will count the number of books recorded.
	file.open("Book Inventory.txt", ios::out | ios::app);
	if (file.fail()) {
		cout << "Cannot open file";
		exit(1);
	}
	cout << "RECORDING BOOK INFORMATION\n";
	do {
		cin.ignore();
		cout << "enter the info of book " << i + 1 << endl;
		cout << "***********************\n";
		cout << "the author: " << endl;
		getline(cin, book.author);
		file << book.author << endl;
		cout << "title: ";
		getline(cin, book.title);
		file << book.title << endl;
		cout << "genre: ";
		getline(cin, book.genre);
		file << book.genre << endl;
		cout << "edition: ";
		cin >> book.edition;
		file << book.edition << endl;
		cin.ignore();
		cout << "publisher: ";
		getline(cin, book.publisher);
		file << book.publisher << endl;
		cout << "serial number: ";
		cin >> book.serialNumber;
		file << book.serialNumber << endl;
		cout << "the year: ";
		cin >> book.year;
		file << book.year << endl;
		cout << "congratulations you have successfully recorded " << i + 1 << " books\n";
		i++;
		cout << "Would you like to add another book? Press Y for yes and N for no.\n";
		cin >> ans;
		ans = toupper(ans);
	} while (ans == 'Y');
	file.close();
}
void editBook() {
	Book book;
	fstream file;
	cout << "BOOK EDITING IN PROGRESS" << endl
		<< "FIRST, THE DELETING WILL TAKE PLACE" << endl;
	removeBook(book);
	cout << "NOW ENTER THE THE NEW INFORMATION" << endl;
	recordBook(book, file);
}