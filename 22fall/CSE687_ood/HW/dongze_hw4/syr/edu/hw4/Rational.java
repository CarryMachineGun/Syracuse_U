package syr.edu.hw4;

/* Adapted from Programming in Scala, Odersky */

public class Rational {
    private int numer;
    private int denom;
    private int g;
    public Rational(int n, int d) {
        int gcd = gcd(n,d);
        this.numer = n/gcd;
        this.denom = d/gcd;
        this.g = gcd;
    }

    public Rational(int n) {
        this.numer = n;
        this.denom = 1;
        this.g = 1;
    }

    public static int gcd(int a, int b){
        if(b==0) return a;
        else return gcd(b, a%b);
    }

    @Override
    public String toString() {
        String n = String.valueOf(this.numer);
        String d = String.valueOf(this.denom);
        return n +'/'+ d;
    }

    public Rational add(Rational that) {
        Rational result = new Rational((this.numer * that.denom) + (that.numer * this.denom),
                this.denom * that.denom);
        return result;
    }

    public Rational add(int that) {
        Rational result = new Rational((this.denom * that)+this.numer,this.denom);
        return result;
    }

    public boolean lessThan(Rational that) {
        if(this.numer*that.denom < that.numer*this.denom) return true;
        else return false;
    }

    public boolean lessThan(int that) {
        if(this.numer < that*this.denom) return true;
        else return false;
    }

    public Rational max(Rational that) {
        if(this.numer*that.denom > that.numer*this.denom) return this;
        else return that;
    }

    public Rational max(int that) {
        if(this.numer > that*this.denom) return this;
        else {
            Rational result = new Rational(that);
            return result;
        }
    }

    public static void main(String[] args) {
        Rational half = new Rational(1, 2);
        Rational third = new Rational(1, 3);
        System.out.println(half.max(third)); // returns half; prints "1/2"
        System.out.println(third.max(half)); // returns half; prints "1/2"
        Rational result = half.add(third);
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

