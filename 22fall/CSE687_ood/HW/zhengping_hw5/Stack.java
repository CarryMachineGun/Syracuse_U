package syr.edu.hw5;


public class Stack implements IStack{
    public Object[] elem;

    public int top = -1;

    public int MAX_SIZE = 50;

    public Stack() {
        this.elem = new Object[MAX_SIZE];
    }

    public Stack(int size) {
        if (size <= 0) {
            System.err.println("wrong size!!! using default");
        } else {
            MAX_SIZE = size;
        }
        elem = new Object[MAX_SIZE];
    }

    @Override
    public void clear() {
        top = -1;
        elem = new Object[MAX_SIZE];
    }

    @Override
    public boolean isEmpty() {
        return top == -1;
    }

    @Override
    public int length() {
        return top + 1;
    }

    @Override
    public Object peek() {
        if (top == -1) {
            return null;
        } else {
            return elem[top];
        }
    }

    @Override
    public void push(Object o) {
        if (top + 1 == MAX_SIZE) {
            System.err.println("stack is full!");
            return;
        }
        this.elem[++top] = o;
    }

    @Override
    public Object pop() {
        if(isEmpty()){
            System.err.println("stack has no element!");
            return null;
        }
        return elem[top--];
    }
}
