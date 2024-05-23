/* 8.A book shop maintains the inventory of books that are being sold at the shop. The list includes details such
as author, title, price, publisher and stock position. Whenever a customer wants a book, the sales person
inputs the title and author and the system searches the list and displays whether it is available or not. If it is
not, an appropriate message is displayed. If it is, then the system displays the book details and requests for
the number of copies required. If the requested copies book details and requests for the number of copies
required. If the requested copies are available, the total cost of the requested copies is displayed; otherwise
the message “Required copies not in stock” is displayed.
 Design a system using a class called books with suitable member functions and Constructors. Use new
operator in constructors to allocate memory space required.*/

#include <iostream>
#include <cstring>

using namespace std;

class Book {
private:
    char *author;
    char *title;
    float price;
    char *publisher;
    int stock;

public:
    // Constructor
    Book(const char *author, const char *title, float price, const char *publisher, int stock) {
        this->author = new char[strlen(author) + 1];
        strcpy(this->author, author);
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
        this->price = price;
        this->publisher = new char[strlen(publisher) + 1];
        strcpy(this->publisher, publisher);
        this->stock = stock;
    }

    // Destructor
    ~Book() {
        delete[] author;
        delete[] title;
        delete[] publisher;
    }

    // Function to display book details
    void display() const {
        cout << "Author: " << author << std::endl;
        cout << "Title: " << title << std::endl;
        cout << "Price: $" << price << std::endl;
        cout << "Publisher: " << publisher << std::endl;
        cout << "Stock: " << stock << " copies" << std::endl;
    }

    // Function to check if a book matches the given title and author
    bool isMatch(const char *searchTitle, const char *searchAuthor) const {
        return (strcmp(title, searchTitle) == 0) && (strcmp(author, searchAuthor) == 0);
    }

    // Function to check if the requested copies are available
    bool isAvailable(int requestedCopies) const {
        return stock >= requestedCopies;
    }

    // Function to process the sale of requested copies
    void sell(int requestedCopies) {
        if (isAvailable(requestedCopies)) {
            stock -= requestedCopies;
            cout << "Total cost: $" << price * requestedCopies << std::endl;
        } else {
            cout << "Required copies not in stock" << std::endl;
        }
    }
};

int main() {
    // Create some books
    Book book1("Author A", "Title A", 25.5, "Publisher A", 10);
    Book book2("Author B", "Title B", 15.0, "Publisher B", 5);
    Book book3("Author C", "Title C", 20.0, "Publisher C", 2);

    // Array of books
    Book books[] = {book1, book2, book3};
    int numBooks = sizeof(books) / sizeof(books[0]);

    // Customer request
    char searchTitle[100];
    char searchAuthor[100];
    cout << "Enter book title: ";
    cin.getline(searchTitle, 100);
    cout << "Enter book author: ";
    cin.getline(searchAuthor, 100);

    // Search for the book
    bool found = false;
    for (int i = 0; i < numBooks; ++i) {
        if (books[i].isMatch(searchTitle, searchAuthor)) {
            found = true;
            books[i].display();
            int requestedCopies;
            cout << "Enter number of copies required: ";
            cin >> requestedCopies;
            books[i].sell(requestedCopies);
            break;
        }
    }

    if (!found) {
        cout << "Book not found" << std::endl;
    }

    return 0;
}
