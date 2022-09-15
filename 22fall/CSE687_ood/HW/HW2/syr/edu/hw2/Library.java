package syr.edu.hw2;

import java.util.ArrayList;
import java.util.List;

public class Library {
    // private ArrayList<String> fieldname;
    private ArrayList<Book> fieldname;

    Library() {
        fieldname = new ArrayList<>();
    }

    // public void init(String[] books) {
    //     for (String book : books) {
    //         fieldname.add(book);
    //     }

    //     return;
    // }
    public void add(Book book){
        fieldname.add(book);

        return;
    }

    // public String search(String str) {
    //     for (String book : fieldname) {
    //         // System.out.println(book);
    //         if (book.contains(str))
    //             return book;
    //     }

    //     return "No Such Book!";
    // }

    public List<Book> search(Book target_book) {
        List<Book> ret = new ArrayList<>();

        for (Book book : fieldname) {
            // System.out.println(book);
            if (book == target_book)
                ret.add(book);
        }

        return ret;
    }

}
