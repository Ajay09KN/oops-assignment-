/* 9.Improve the system design in exercise 8 to incorporate the following features:
(a) The price of the books should be updated as and when required. Use a private meneber function to
implement this.
(b) The stock value of each book should be automatically updated as soon as a transaction is completed.
(c) The number of successful transactions should be recorded for the purpose of statistical analysis. Use
static data members to keep count of transaction. */

#include <iostream>
#include <cstring>

class Book {
private:
    char *author;
    char *title;
    float price;
    char *publisher;
    int stock;
    static int successfulTransactions;

    // Private member function to update the price
    void updatePrice(float newPrice) {
        price = newPrice;
    }

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
        std::cout << "Author: " << author << std::endl;
        std::cout << "Title: " << title << std::endl;
        std::cout << "Price: $" << price << std::endl;
        std::cout << "Publisher: " << publisher << std::endl;
        std::cout << "Stock: " << stock << " copies" << std::endl;
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
            successfulTransactions++;
            std::cout << "Total cost: $" << price * requestedCopies << std::endl;
        } else {
            std::cout << "Required copies not in stock" << std::endl;
        }
    }

    // Function to update the price (public interface)
    void changePrice(float newPrice) {
        updatePrice(newPrice);
    }

    // Static function to get the count of successful transactions
    static int getSuccessfulTransactions() {
        return successfulTransactions;
    }
};

// Initialize static member
int Book::successfulTransactions = 0;

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
    std::cout << "Enter book title: ";
    std::cin.getline(searchTitle, 100);
    std::cout << "Enter book author: ";
    std::cin.getline(searchAuthor, 100);

    // Search for the book
    bool found = false;
    for (int i = 0; i < numBooks; ++i) {
        if (books[i].isMatch(searchTitle, searchAuthor)) {
            found = true;
            books[i].display();
            int requestedCopies;
            std::cout << "Enter number of copies required: ";
            std::cin >> requestedCopies;
            books[i].sell(requestedCopies);
            break;
        }
    }

    if (!found) {
        std::cout << "Book not found" << std::endl;
    }

    // Update book price (example)
    std::cout << "\nUpdating the price of 'Title A' by 'Author A' to $30.0" << std::endl;
    book1.changePrice(30.0);
    book1.display();

    // Display the number of successful transactions
    std::cout << "\nNumber of successful transactions: " << Book::getSuccessfulTransactions() << std::endl;

    return 0;
}
