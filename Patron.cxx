#include <iostream>
#include <string>
#include <vector>

class Book {
private:
    std::string ISBN;
    std::string title;
    std::string author;
    int copyrightDate;
    bool checkedOut;
    std::string genre;

public:
    Book(std::string isbn, std::string t, std::string a, int cd, std::string g)
        : ISBN(isbn), title(t), author(a), copyrightDate(cd), genre(g), checkedOut(false) {}

    std::string getISBN() const { return ISBN; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    bool isCheckedOut() const { return checkedOut; }
    void checkOut() { checkedOut = true; }
    void checkIn() { checkedOut = false; }
    std::string getGenre() const { return genre; }

    bool operator==(const Book& other) const { return ISBN == other.ISBN; }
    bool operator!=(const Book& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& os, const Book& book);
};

std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "Title: " << book.title << "\nAuthor: " << book.author
       << "\nISBN: " << book.ISBN << "\nGenre: " << book.genre;
    return os;
}

class Patron {
private:
    std::string userName;
    std::string cardNumber;
    int owedFees;

public:
    Patron(std::string name, std::string card)
        : userName(name), cardNumber(card), owedFees(0) {}

    std::string getUserName() const { return userName; }
    std::string getCardNumber() const { return cardNumber; }
    int getOwedFees() const { return owedFees; }
    bool owesFees() const { return owedFees > 0; }
    void setFees(int fees) { owedFees = fees; }
};

class Transaction {
private:
    Book book;
    Patron patron;
    std::string activity;
    std::string date;

public:
    Transaction(const Book& b, const Patron& p, std::string act, std::string d)
        : book(b), patron(p), activity(act), date(d) {}
};

class Library {
private:
    std::vector<Book> books;
    std::vector<Patron> patrons;
    std::vector<Transaction> transactions;

public:
    void addBook(const Book& book) { books.push_back(book); }

    void checkOutBook(const Book& book, const Patron& patron, std::string date) {
        if (std::find(books.begin(), books.end(), book) == books.end()) {
            std::cout << "Error: Book not found in the library." << std::endl;
            return;
        }

        if (std::find(patrons.begin(), patrons.end(), patron) == patrons.end()) {
            std::cout << "Error: Patron not found in the library." << std::endl;
            return;
        }

        if (patron.owesFees()) {
            std::cout << "Error: Patron owes fees." << std::endl;
            return;
        }

        book.checkOut();
        transactions.push_back(Transaction(book, patron, "Check Out", date));
    }

    void displayPatronsWithFees() {
        for (const Patron& patron : patrons) {
            if (patron.owesFees()) {
                std::cout << "Patron with fees: " << patron.getUserName() << std::endl;
            }
        }
    }
};

int main() {
    // Create instances of Book, Patron, and Library
    Book book("123456789", "The Catcher in the Rye", "J.D. Salinger", 1951, "Fiction");
    Patron patron("Alice Smith", "P12345");
    Library library;

    // Add book to library
    library.addBook(book);

    // Check out the book
    library.checkOutBook(book, patron, "2023-08-15");

    // Display patrons with fees
    library.displayPatronsWithFees();

    return 0;
}
