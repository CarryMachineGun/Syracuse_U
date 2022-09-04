package syr.edu.hw1;

import java.util.ArrayList;

public class Library {
    private ArrayList<String> fieldname;

    Library() {
        fieldname = new ArrayList<>();
    }

    public void init(String[] books) {
        for (String book : books) {
            fieldname.add(book);
        }

        return;
    }

    public String search(String str) {
        for (String book : fieldname) {
            // System.out.println(book);
            if (book.contains(str))
                return book;
        }

        return "No Such Book!";
    }
}
