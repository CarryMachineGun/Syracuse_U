package edu.syr.hw5;

import java.util.EmptyStackException;
import java.util.LinkedList;
import java.util.List;


public class MyStack<E> implements Stack<E>{

    private LinkedList<E> l1 = new LinkedList<E>();

    public MyStack(){}

    @Override
    public void push(E e) {
        l1.addFirst(e);
    }

    @Override
    public E pop() {
        if(isEmpty()){
            throw new EmptyStackException();
        }
        return l1.removeFirst();
    }
    public boolean isEmpty(){
        return l1.isEmpty();
    }

    @Override
    public E peek() {
        if(isEmpty()){
            throw new EmptyStackException();
        }
        return l1.peekFirst();
    }

    @Override
    public int size() {
        return l1.size();
    }

    @Override
    public List<E> getData() {
        return l1;
    }

    public static void main(String[] args) {
        MyStack<Integer> st1 = new MyStack<Integer>();
        st1.push(1);
        st1.push(22);
        st1.push(45);
        st1.pop();
        System.out.println(st1.peek());
        System.out.println(st1.size());
        System.out.println(st1.getData());
    }
}
