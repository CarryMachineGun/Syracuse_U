package syr.edu.hw5;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;


public class Rational {
    private int numer;
    private int denom;
    private int g;
    
    private static Rational[] Cache = new Rational[100];
    public Rational(int n, int d) {
        if (d == 0) {
            throw new IllegalArgumentException("Denominator can't be 0!");

        }
        g = gcd(n, d);
        numer = n/g;
        denom = d/g;
    }

    public Rational(int n) {
        this(n, 1);
    }

    private int gcd(int n, int d) {
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

    public static Rational getInstance(int n,int d){
        for(int i = 0; i < Cache.length; i++){
            if(Cache[i] == null){
                Cache[i] = new Rational(n,d);
                return Cache[i];
            }else if(Cache[i].numer == n && Cache[i].denom == d){
                return Cache[i];
            }
        }
        return null;
    }

    public static Rational getInstance(int n){
        for(int i = 0; i < Cache.length; ++i){
            if(Cache[i] == null){
                Cache[i] = new Rational(n);
                return Cache[i];
            }
        }
        return null;
    }

    public static void main(String[] args) {
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