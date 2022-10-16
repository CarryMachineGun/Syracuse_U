package syr.edu.hw5;

import java.util.*;
// import java.util.List;

public class MyStack<E> implements Stack<E> {
    private List<E> data = new ArrayList<>();

    public void push(E e) {
        data.add(e);

        return;
    }

    public E peek() {
        if(data.isEmpty()){
            throw new EmptyStackException();
        }
        E top = data.get(data.size() - 1);

        return top;
    }

    public E pop() {
        if(data.isEmpty()){
            throw new EmptyStackException();
        }
        E top = data.get(data.size() - 1);
        data.remove(data.size() - 1);

        return top;
    }

    public int size() {
        return data.size();
    }

    public List<E> getData() {
        return data;
    }

    public static void main(String[] args) {
        MyStack<Integer> st = new MyStack<Integer>();

        st.push(1);
        st.push(2);
        st.push(3);

        System.out.println(st.getData());
        System.out.println(st.pop());
        System.out.println(st.peek());
        System.out.println(st.size());
        System.out.println(st.getData());

        return;
    }
}
