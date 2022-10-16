package syr.edu.hw5;

import java.util.List;

public interface Stack<E> {
    public void push(E e);
    public E pop();
    public E peek();
    public int size();
    // getData returns an unmodifiable list of the stack's contents.
    // See java.util.Collections
    public List<E> getData();
}

// 0 VINs found



// View Showroom
// 0 VINs identified


// Send Feedback