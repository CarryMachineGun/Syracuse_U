package syr.edu.hw5;

public interface IStack {
    void clear();

    boolean isEmpty();

    int length();

    Object peek();

    void push(Object o);

    Object pop();
}
