package syr.edu.hw3;

import java.lang.StringBuilder;
// import syr.edu.hw3.BookType;

// import syr.edu.hw3.Book;
enum BookType {
    HARDCOVER, PAPERBACK, EBOOK, ANY;

    // @Override
    // public int hashCode(){

    // } 
}

public class Book {
    private String author;
    private String title;
    private String publisher;
    private String isbn;
    private int yearPublished;
    private BookType type;

    public Book() {
        author = null;
        title = null;
        publisher = null;
        isbn = null;
        yearPublished = -1;
        type = BookType.ANY;
    }

    public Book(String a, String t, String p, String i, int y, BookType type) {
        this.author = a;
        this.title = t;
        this.publisher = p;
        this.isbn = i;
        this.yearPublished = y;
        this.type = type;
    }

    public BookType getType() {
        return type;
    }

    public String getAuthor() {
        return author;
    }

    public String getTitle() {
        return title;
    }

    public String getPublisher() {
        return publisher;
    }

    public String getIsbn() {
        return isbn;
    }

    public int getYearPublished() {
        return yearPublished;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        if (title != null)
            sb.append("Tital: ").append(title).append("\n");
        if (author != null)
            sb.append("Author: ").append(author).append("\n");
        if (publisher != null)
            sb.append("Publisher: ").append(publisher).append("\n");
        if (isbn != null)
            sb.append("Isbn: ").append(isbn).append("\n");
        if (yearPublished != -1)
            sb.append("Year of Publish: ").append(yearPublished).append("\n");
        if (type != BookType.ANY) {
            sb.append("Type: ").append(type);
        }

        return sb.toString();
    }

    @Override
    public int hashCode() {
        int hashcode = 0;

        if (title != null)
            hashcode += title.hashCode();
        if (author != null)
            hashcode += author.hashCode();
        if (publisher != null)
            hashcode += publisher.hashCode();
        if (isbn != null)
            hashcode += isbn.hashCode();
        if (yearPublished != -1)
            hashcode += yearPublished;
        if (type != BookType.ANY)
            hashcode += type.hashCode();

        return hashcode;
    }

    @Override
    public boolean equals(Object book) {
        Book another_book = (Book) book;

        if (another_book.getAuthor() != null && !author.equals(another_book.getAuthor()))
            return false;

        if (another_book.getTitle() != null && !title.equals(another_book.getTitle()))
            return false;

        if (another_book.getPublisher() != null && !publisher.equals(another_book.getPublisher()))
            return false;

        if (another_book.getIsbn() != null && !isbn.equals(another_book.getIsbn()))
            return false;

        if (yearPublished != -1 && yearPublished != another_book.getYearPublished())
            return false;

        if (type != BookType.ANY && type != another_book.type)
            return false;

        return true;
    }

    // public static void main(String[] args) {
    // Book b1 = new Book("Holden Karau", "Learning Spark", "O'Reilly",
    // "9781449358624", 2015);
    // Book b2 = new Book("Norman Matloff", "The Art of R Programming", "No Starch
    // Press", "9781593273842", 2011);
    // Book b3 = new Book("Alan A. A. Donovan", "The Go Programming Language",
    // "Addison Wesley", "9780134190440",
    // 2016);
    // }
}