package syr.edu.hw4;
// import javax.swing.text.TabSet;

/* Adapted from Programming in Scala, Odersky */

public class Rational {
    private int numer;
    private int denom;
    private int g;

    private int calculateGCD(int n, int d){
        if(d == 0) 
            return n;
        else 
            return calculateGCD(d, n % d);
    }

    public Rational(int n, int d) {
        g = calculateGCD(n, d);
        numer = n / g;
        denom = d / g;

        return;
    }

    public Rational(int n) {
        g = 1;
        numer = n;
        denom = 1;
        /* implement this */ }

    @Override
    public String toString() {
        return (numer) + "/" + (denom);
        /* implement this */ }

    public Rational add(Rational that) {
        return new Rational((numer * that.denom + that.numer * denom), denom * that.denom);
        /* implement this */ }

    public Rational add(int that) {
        Rational that_rational = new Rational(that);

        return this.add(that_rational);
        /* implement this */ }

    public boolean lessThan(Rational that) {
        return numer * that.denom < that.numer * denom ? true : false;
        /* implement this */ }

    public boolean lessThan(int that) {
        Rational that_rational = new Rational(that);

        return this.lessThan(that_rational);
        /* implement this */ }

    public Rational max(Rational that) {
        return numer * that.denom < that.numer * denom ? that : this;
        /* implement this */ }

    public Rational max(int that) {
        Rational that_rational = new Rational(that);

        return this.max(that_rational);
        /* implement this */ }

    public static void main(String[] args) {
        Rational half = new Rational(1, 2);
        Rational third = new Rational(1, 3);
        System.out.println(half.max(third)); // returns half; prints "1/2"
        System.out.println(third.max(half)); // returns half; prints "1/2"
        Rational result = half.add(third);
        // System.out.println(result);
        Rational fiveSixths = new Rational(5, 6);
        System.out.println("are they the same object? " + (result == fiveSixths));
        System.out.println(fiveSixths.lessThan(result)); // false
        System.out.println(result.lessThan(fiveSixths)); // false
        Rational one = new Rational(1);
        Rational oneAndHalf = one.add(half);
        System.out.println(oneAndHalf); // prints "3/2";
        Rational fifteenOverTen = new Rational(15, 10);
        System.out.println(fifteenOverTen); // prints "3/2"
    }
}
