package syr.edu.hw5;

public class StackTest {
    public static void main(String[] args) {
        Stack s = new Stack(5);
        s.push("1");
        s.push("2");
        s.push("3");
        s.push("4");
        s.push("5");

        System.out.println("length is " + s.length());
        System.out.println("peek result is " + s.peek());
        System.out.println("isEmpty " + s.isEmpty());


        Object pop = s.pop();
        System.out.println("pop result is " + pop);
        System.out.println("after pop length is " + s.length());


        s.clear();
        System.out.println("after clear length is " + s.length());
        System.out.println("isEmpty " + s.isEmpty());
    }
}
