enum BookType{
    HARDCOVER,
    PAPERBACK,
    EBOOK,
    ANY;
}
public class Book {
    private String author;
    private String title;
    private String publisher;
    private String isbn;
    private int yearPublished;

    public BookType booktype;

    public Book(String a, String t, String p, String i, int y, BookType bt) {
        this.author = a;
        this.title = t;
        this.publisher = p;
        this.isbn = i;
        this.yearPublished = y;
        this.booktype = bt;
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
    public BookType getType(){
        return booktype;
    }

    @Override
    public boolean equals(Object o) {
        if(this == o) return true;
        if (o==null ||o.getClass() != this.getClass()) return false;

        Book book_o = (Book) o;

        return (book_o.getAuthor()== this.getAuthor() &&
                book_o.getTitle() == this.getTitle() &&
                book_o.getPublisher() == this.getPublisher() &&
                book_o.getIsbn() == this.getIsbn() &&
                book_o.getYearPublished() == this.getYearPublished()&&
                book_o.getType() == this.getType());
    }

    @Override
    public int hashCode(){
        int result = 3;
        result = 17* result + author.hashCode();
        result = 17* result + title.hashCode();
        result = 17* result + publisher.hashCode();
        result = 17* result + isbn.hashCode();
        result = 17* result + yearPublished;
        result = 17* result + booktype.hashCode();
        return result;
    }

    @Override
    public String toString() {
        return getTitle()+"@"+Integer.toHexString(hashCode());
    }

    public static void main(String[] args) {

    }
}
