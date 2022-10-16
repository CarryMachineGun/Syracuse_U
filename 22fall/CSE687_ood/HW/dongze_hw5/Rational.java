package edu.syr.hw5;

public class Rational {
    private int numer;
    private int denom;
    private int g;

    private Rational(int n, int d) {
        g = gcd(n, d);
        numer = n/g;
        denom = d/g;
    }
    private Rational(int n){
        this(n,1);
    }
    private Rational(){}

    private static Rational[] cache = new Rational[20];

    public static Rational getInstance(int n, int d){
        int g2 = gcd(n,d);
        int n2 = n/g2;
        int d2 = d/g2;
        for(int i = 0;i<cache.length;i++){
            if(cache[i]==null){
                cache[i] = new Rational(n,d);
                return cache[i];
            }else if(cache[i].numer==n2 && cache[i].denom==d2){
                return cache[i];
            }
        }

        return new Rational();
    }
    public static Rational getInstance(int n){
        for(int i = 0;i<cache.length;i++){
            if(cache[i]==null){
                cache[i] = new Rational(n);
                return cache[i];
            }
        }

        return new Rational();
    }
    
    private static int gcd(int n, int d) {
        return d==0 ? n : gcd(d, n%d);
    }

    @Override
    public String toString() {
        return denom==1 ? numer +"" : numer + "/" + denom;
    }

    public Rational add(Rational that) {
        return getInstance(numer * that.denom + denom * that.numer, denom * that.denom);
    }

    public Rational add(int that) {
        return add(getInstance(that));
    }

    public boolean lessThan(Rational that) {
        return this.numer * that.denom < that.numer * this.denom;
    }

    public boolean lessThan(int that) {
        return lessThan(getInstance(that));
    }

    public Rational max(Rational that) {
        return this.lessThan(that) ? that : this;
    }

    public Rational max(int that) {
        return max(getInstance(that));
    }

    public static void main(String[] args) {
        Rational half = getInstance(1, 2);
        Rational third = getInstance(1, 3);
        System.out.println(half.max(third)); // returns half; prints "1/2"
        System.out.println(third.max(half)); // returns half; prints "1/2"
        Rational result = half.add(third);
        Rational fiveSixths = getInstance(5, 6);
        System.out.println("are they the same object? " + (result == fiveSixths));
        System.out.println(fiveSixths.lessThan(result)); // false
        System.out.println(result.lessThan(fiveSixths)); // false
        Rational one = getInstance(1);
        Rational oneAndHalf = one.add(half);
        System.out.println(oneAndHalf); // prints "3/2";
        Rational fifteenOverTen = getInstance(15, 10);
        System.out.println(fifteenOverTen); // prints "3/2"
    }
}
