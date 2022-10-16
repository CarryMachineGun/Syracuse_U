package syr.edu.hw5;

import java.nio.file.WatchEvent;
import java.util.*;

public class Rational {
    private int numer;
    private int denom;
    private int g;
    private static List<Rational> cache = new ArrayList<>();
    private Rational(int n, int d) {
        if (d == 0) {
            throw new IllegalArgumentException("Denominator can't be 0!");
        }
        g = gcd(n, d);
        numer = n/g;
        denom = d/g;
    }

    private Rational(int n) {
        this(n, 1);
    }

    private static int gcd(int n, int d) {
        return d==0 ? n : gcd(d, n%d);
    }

    @Override
    public String toString() {
        return denom==1 ? numer +"" : numer + "/" + denom;
    }

    public Rational add(Rational that) {
        return new Rational(numer * that.denom + denom * that.numer, denom * that.denom);
    }

    public Rational add(int that) {
        return add(new Rational(that));
    }

    public boolean lessThan(Rational that) {
        return this.numer * that.denom < that.numer * this.denom;
    }

    public boolean lessThan(int that) {
        return lessThan(new Rational(that));
    }

    public Rational max(Rational that) {
        return this.lessThan(that) ? that : this;
    }

    public Rational max(int that) {
        return max(new Rational(that));
    }

    public static Rational getInstance(int n, int d){
        int curr_g = gcd(n, d);
        int curr_numer = n/curr_g;
        int curr_denom = d/curr_g; 

        for(Rational obj : cache){
            if(obj.numer == curr_numer && obj.denom == curr_denom && obj.g == curr_g){
                return obj;
            }
        }
        
        Rational obj = new Rational(n, d);
        cache.add(obj);
        
        return obj;
    }


    public static Rational getInstance(int n){
        return getInstance(n, 1);
    }

    public static void main(String[] args) {
        // Rational half = new Rational(1, 2);
        // Rational third = new Rational(1, 3);
        // System.out.println(half.max(third)); // returns half; prints "1/2"
        // System.out.println(third.max(half)); // returns half; prints "1/2"
        // Rational result = half.add(third);
        // Rational fiveSixths = new Rational(5, 6);
        // System.out.println("are they the same object? " + (result == fiveSixths));
        // System.out.println(fiveSixths.lessThan(result)); // false
        // System.out.println(result.lessThan(fiveSixths)); // false
        // Rational one = new Rational(1);
        // Rational oneAndHalf = one.add(half);
        // System.out.println(oneAndHalf); // prints "3/2";
        // Rational fifteenOverTen = new Rational(15, 10);
        // System.out.println(fifteenOverTen); // prints "3/2"


        Rational half = Rational.getInstance(1, 2);
        Rational third = Rational.getInstance(1, 3);
        System.out.println(half.max(third)); // returns half; prints "1/2"
        System.out.println(third.max(half)); // returns half; prints "1/2"
        Rational result = half.add(third);
        Rational fiveSixths = Rational.getInstance(5, 6);
        System.out.println("are they the same object? " + (result == fiveSixths));
        System.out.println(fiveSixths.lessThan(result)); // false
        System.out.println(result.lessThan(fiveSixths)); // false
        Rational one = Rational.getInstance(1);
        Rational oneAndHalf = one.add(half);
        System.out.println(oneAndHalf); // prints "3/2";
        Rational fifteenOverTen = Rational.getInstance(15, 10);
        System.out.println(fifteenOverTen); // prints "3/2"
    }
}


// 0 VINs found



// View Showroom
// 0 VINs identified


// Send Feedback