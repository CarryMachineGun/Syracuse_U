
import java.util.ArrayList;
import java.util.List;

public class Library {
    private List<Book> catalog;
    public Library() {
        catalog = new ArrayList<>();
    }
    public void add(Book b) {
        catalog.add(b);
    }
    public List<Book> search(Book lookFor) {
        List<Book> results = new ArrayList<>();
        for (Book curr: catalog) {
            if (lookFor.getAuthor() != null) {
                if (!lookFor.getAuthor().equals(curr.getAuthor())) {
                    continue;
                }
            }
            if (lookFor.getTitle() != null) {

                if (!lookFor.getTitle().equals(curr.getTitle())) {
                    continue;
                }
            }
            if (lookFor.getPublisher() != null) {
                if (!lookFor.getPublisher().equals(curr.getPublisher())) {
                    continue;
                }
            }
            if (lookFor.getIsbn() != null) {
                if (!lookFor.getIsbn().equals(curr.getIsbn())) {
                    continue;
                }
            }
            if (lookFor.getYearPublished() != -1) {
                if (lookFor.getYearPublished() != curr.getYearPublished()) {
                    continue;
                }
            }
            if (lookFor.getType() != BookType.ANY) {
                if (lookFor.getType() != curr.getType()) {
                    continue;
                }
            }
            results.add(curr);
        }
        return results;
    }

    public static void main(String[] args) {
        Library lib = new Library();
        lib.add(new Book("Holden Karau", "Learning Spark", "O'Reilly", "9781449358624", 2015, BookType.HARDCOVER));
        Book b2 = new Book("Norman Matloff", "The Art of R Programming", "No Starch Press", "9781593273842", 2011, BookType.PAPERBACK);
        Book b3 = new Book("Alan A. A. Donovan", "The Go Programming Language", "Addison Wesley", "9780134190440", 2016, BookType.EBOOK);

        //List<Book> results = lib.search(new Book(null, null,"Learning Spark", null, -1, BookType.ANY));
        /*the reason why the given search cannot find the corresponding book
        is that it put the "Learning Spark"value at the publisher position.
        The input parameters should match the sequence in the constructor!
         */
        List<Book> results = lib.search(new Book(null,"Learning Spark", null, null, -1, BookType.ANY));
        for (Book b: results) {
            System.out.println(b.toString());
        }

    }
}
