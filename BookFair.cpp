#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Book;
class Customer;

class Book {
    string name, author;
    int numberOfCopiesAvailable;
    double price;
public:
    Book() {
        name = "";
        author = "";
        numberOfCopiesAvailable = 0;
        price = 0;
    }
    Book(string n, string a, int copies, double p) {
        name = n;
        author = a;
        numberOfCopiesAvailable = copies;
        price = p;
    }
    void setName(string n)
    {
        name=n;
    }
    void setAuthor(string a)
    {
        author=a;
    }
    void setCopies(int c)
    {
        numberOfCopiesAvailable=c;
    }
    void setPrice(double p)
    {
        price=p;
    }
    string getName()
    {
        return name;
    }
    string getAuthor()
    {
        return author;
    }
    int getCopies()
    {
        return numberOfCopiesAvailable;
    }
    double getPrice()
    {
        return price;
    }

    friend void purchase(Customer &c, Book &b);
};

class BookStall {
    string name, address, contactInfo;
    vector<Book> bookList;
public:
    BookStall() {
        name = "";
        address = "";
        contactInfo = "";
    }
    BookStall(string n, string a, string cinfo) {
        name = n;
        address = a;
        contactInfo = cinfo;
        for(int i=1;i<=15;i++){
            string bname="Book_"+to_string(i);
            bookList.push_back(Book(bname,"Author_"+to_string(i),10,100+i));
        }
    }
    string getName()
    {
        return name;
    }
    vector<Book>& getBookList()
    {
        return bookList;
    }

    void showBooks(){
        cout<<"\n--- "<<name<<" Book List ---\n";
        for(auto &b:bookList)
            cout<<b.getName()<<" ("<<b.getAuthor()<<") - Copies: "<<b.getCopies()<<" - Price: "<<b.getPrice()<<endl;
    }
};

class Customer {
    string name, nationalId, deliveryAddress, contactInfo;
    double wallet;
    vector<Book> purchasedBooks;
public:
    Customer(){
        name="";
        nationalId="";
        deliveryAddress="";
        contactInfo="";
        wallet=0;
    }
    Customer(string n,string id,string addr,string cinfo,double w){
        name=n;
        nationalId=id;
        deliveryAddress=addr;
        contactInfo=cinfo;
        wallet=w;
    }
    void visitBookStall(BookStall &stall){
        cout<<"\n"<<name<<" is visiting "<<stall.getName()<<endl;
        stall.showBooks();
    }
    void showPersonalInfo(){
        cout<<"\n--- Customer Info ---\n";
        cout<<"Name: "<<name<<"\nNational ID: "<<nationalId<<"\nWallet: "<<wallet
            <<"\nAddress: "<<deliveryAddress<<"\nContact: "<<contactInfo<<endl;
        cout<<"\nPurchased Books:\n";
        for(auto &b:purchasedBooks)
            cout<<b.getName()<<" by "<<b.getAuthor()<<" Price: "<<b.getPrice()<<endl;
    }
    
    friend void purchase(Customer &c, Book &b);
};

void purchase(Customer &c, Book &b){
    if(b.getCopies()<=0){
        cout<<"Sorry, "<<b.getName()<<" is out of stock.\n";
        return;
    }
    if(c.wallet < b.getPrice()){
        cout<<"Not enough balance to buy "<<b.getName()<<endl;
        return;
    }
    b.setCopies(b.getCopies()-1);
    c.wallet -= b.getPrice();
    c.purchasedBooks.push_back(Book("Purchased_"+b.getName(), b.getAuthor(),1,b.getPrice()));
    cout<<c.wallet<<" left after buying "<<b.getName()<<endl;
}

int main(){
    vector<BookStall> stalls;
    for(int i=1;i<=5;i++){
        stalls.push_back(BookStall("Book_Stall_"+to_string(i),"Address_"+to_string(i),"Contact_"+to_string(i)));
    }

    Customer c1("Customer","123456789","Dhaka","017XXXXXXXX",1500);

    c1.visitBookStall(stalls[0]);
    purchase(c1, stalls[0].getBookList()[0]);

    c1.visitBookStall(stalls[1]);
    purchase(c1, stalls[1].getBookList()[3]);

    c1.visitBookStall(stalls[2]);
    purchase(c1, stalls[2].getBookList()[5]);

    c1.showPersonalInfo();

    return 0;
}
