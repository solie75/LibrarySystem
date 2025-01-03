#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

static void Padding()
{
    cout << "\n" << "\n";
}

struct sBookCount
{
    sBookCount(int _max, int _cur) : Max(_max), Cur(_cur) {}

    int Max;
    int Cur;
};

class Book
{
private:
    string title;
    string author;

public:
    Book() {};
    Book(string _title, string _author) : title(_title), author(_author) {};
    ~Book() {};

    string GetTitle() { return title; }
    string GetAuthor() { return author; }
};

class BookManager
{
private:
    vector<Book> books;

public:
    bool AddBook(string _title, string _author)
    {
        bool isAleadyExit = false;
        for (Book book : books)
        {
            if (book.GetTitle() == _title)
            {
                return true;
            }
        }
        books.push_back(Book(_title, _author));
        return isAleadyExit;
    }

    void PrintBookData(Book& _book, int _index = 0)
    {
        cout << "-------------------------------------" << "\n";
        if (_index != 0)
        {
            cout << _index << ". ";
        }
        cout << "Title : " << _book.GetTitle() << "," << "\n" << "Author : " << _book.GetAuthor() << "\n";
        cout << "-------------------------------------" << "\n";
    }

    void DisplayAllBooks()
    {
        cout << "Display all books" << "\n";
        int index = 0;
        for (Book book : books)
        {
            PrintBookData(book, ++index);
        }
    }

    string SearchByTitle(string _title)
    {
        for (Book book : books)
        {
            if (book.GetTitle() == _title)
            {
                cout << "\n";
                cout << "the book is available" << "\n";
                PrintBookData(book);
                return _title;
            }
        }
        cout << "the book is not available" << "\n";
        return "";
    }

    string SearchByAuthor(string _author)
    {
        for (Book book : books)
        {
            if (book.GetAuthor() == _author)
            {
                cout << "\n";
                cout << "the book is available" << "\n";
                PrintBookData(book);

                return book.GetTitle();
            }
        }

        cout << "the book is not available" << "\n";
        return "";
    }

    string SearchBook()
    {
        while (true)
        {
            int inputDial = -1;
            cout << "To search by Title, press 1. To search by Author, press 2." << "\n";
            cin >> inputDial;
            if (inputDial == 1)
            {
                string title;

                cout << "Enter the book title" << "\n";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, title);
                return SearchByTitle(title);
            }
            else if (inputDial == 2)
            {
                string author;

                cout << "Enter the book author" << "\n";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin, author);
                return SearchByAuthor(author);
            }
            else
            {
                cout << "This is not a valid selection. Please choose again.";
            }
        }
    }
};

class BorrowManager
{
private:
    unordered_map<string, sBookCount> stock;
    
public:
    BorrowManager() {};
    ~BorrowManager() {};

    void InitializeStock(string _title , int _quantity = 3)
    {
        stock.insert(make_pair(_title, sBookCount(_quantity, _quantity)));
    }

    unordered_map<string, sBookCount>::iterator FindStock(string _title)
    {
        unordered_map<string, sBookCount>::iterator iter = stock.find(_title);
        return iter;
    }

    void BorrowBook()
    {
        string title;
        cout << "Enter Book title to Borrow" << "\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, title);

        while (true)
        {
            unordered_map<string, sBookCount>::iterator iter = FindStock(title);
            if (iter != stock.end())
            { // å�� �����ϴ� ���
                if (iter->second.Cur > 0)
                {
                    cout << "Complete Borrow '" << iter->first << "'" << "\n";
                    iter->second.Cur -= 1;
                    cout << "There are " << iter->second.Cur << " Books left." << "\n";
                }
                else if (iter->second.Cur == 0)
                {
                    cout << "All of The Book already been checked out" << "\n";
                }
                DisplayStock(title);
                return;
            }
            else
            { // å�� ���� ���
                cout << "The Book is not available. Enter title again." << "\n";
            }
        }
    }

    void ReturnBook()
    {
        string title;
        cout << "Enter Book title to Return" << "\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(cin, title);

        while (true)
        {
            unordered_map<string, sBookCount>::iterator iter = FindStock(title);
            if (iter != stock.end())
            { // å�� �����ϴ� ���
                if (iter->second.Cur < iter->second.Max)
                {
                    cout << "Complete return '" << iter->first << "'" << "\n";
                    iter->second.Cur += 1;
                }
                else if (iter->second.Cur == iter->second.Max)
                {
                    cout << "All books of this are already fully stocked." << "\n";
                }
                DisplayStock(title);
                return;
            }
            else
            {
                cout << "The Book is not available. Enter title again." << "\n";
            }
        }
    }

    void DisplayStock(string _title)
    {
        unordered_map<string, sBookCount>::iterator iter = stock.find(_title);
        cout << "Title : " << iter->first << ", " << " ( Cur : " << iter->second.Cur << ", Max" << iter->second.Max << " )" << "\n";
    }
};

void DonateBook(BookManager& _bookManager, BorrowManager& _borrowManager)
{
    string title;
    string author;

    cout << "Enter Book title." << "\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, title);
    cout << "Enter Book author." << "\n";
    getline(cin, author);
    

    if (_bookManager.AddBook(title, author))
    {
        // å�� �̹� ���� �ϴ� ���
        unordered_map<string, sBookCount>::iterator iter = _borrowManager.FindStock(title);
        iter->second.Max += 1;
        iter->second.Cur += 1;
    }
    else
    {
        _borrowManager.InitializeStock(title);
    }
};

int Manual()
{
    int inputDial = -1;

    cout << "1. Display All Books" << "\n";
    cout << "2. Search Books" << "\n";
    cout << "3. Donate Book" << "\n";
    cout << "4. Borrow Book" << "\n";
    cout << "5. Return Book" << "\n";
    cout << "\n";
    cout << "Enter the Dial" << "\n";

    cin >> inputDial;
    if (inputDial < 1 || inputDial > 5)
    {
        cout << "Invalid selection. Try again." << "\n";
    }

    Padding();
    
    return inputDial;
}

int main()
{
    BookManager bookManager;
    BorrowManager borrowManager;

    bookManager.AddBook("To Kill a Mockingbird", "Harper Lee");
    bookManager.AddBook("1984", "George Orwell");
    bookManager.AddBook("The Great Gatsby", "F. Scott Fitzgerald");
    bookManager.AddBook("Pride and Prejudice", "Jane Austen");
    bookManager.AddBook("Moby-Dick", "Herman Melville");
    bookManager.AddBook("War and Peace", "Leo Tolstoy");
    bookManager.AddBook("The Catcher in the Rye", "J.D. Salinger");
    bookManager.AddBook("The Hobbit", "J.R.R. Tolkien");
    bookManager.AddBook("Crime and Punishment", "Fyodor Dostoevsky");
    bookManager.AddBook("The Odyssey", "Homer");

    borrowManager.InitializeStock("To Kill a Mockingbird");
    borrowManager.InitializeStock("1984");
    borrowManager.InitializeStock("The Great Gatsby");
    borrowManager.InitializeStock("Pride and Prejudice");
    borrowManager.InitializeStock("Moby-Dick");
    borrowManager.InitializeStock("War and Peace");
    borrowManager.InitializeStock("The Catcher in the Rye");
    borrowManager.InitializeStock("The Hobbit");
    borrowManager.InitializeStock("Crime and Punishment");
    borrowManager.InitializeStock("The Odyssey");

    cout << "Welcome to Library !"; Padding();

    while (true)
    {
        switch (Manual())
        {
        case 1:
            bookManager.DisplayAllBooks();
            break;
        case 2:
            {
                string title = bookManager.SearchBook();
                if (title != "")
                {
                    borrowManager.DisplayStock(title);
                }
            }            break;
        case 3:
            DonateBook(bookManager, borrowManager);
            break;
        case 4:
            borrowManager.BorrowBook();
            break;
        case 5:
            borrowManager.ReturnBook();
            break;
        }

        Padding();
    }
}
