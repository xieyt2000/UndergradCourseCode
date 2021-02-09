package rational;


import java.util.Arrays;

public class Rational   //made sure that denominator > 0
{
    //made public according to homework requirements
    public int numerator = 0;
    public int denominator = 0;

    private int gcd(int[] twoInt)   //euclidean algorithm to cal greatest common divider
    {
        //base
        if (twoInt[0] == twoInt[1])
        {
            return twoInt[0];
        }
        Arrays.sort(twoInt);
        twoInt[1] -= twoInt[0];
        return gcd(twoInt);
    }

    private void reduce()
    {
        int[] arr = {Math.abs(numerator), Math.abs(denominator)};
        int gcdNum = gcd(arr);
        numerator /= gcdNum;
        denominator /= gcdNum;
        if (denominator < 0)
        {
            denominator = -denominator;
            numerator = -numerator;
        }
    }

    private void convert(Rational rat) //convert to like quantities for arithmetic operation
    {
        int tmpde = denominator;
        denominator *= rat.denominator;
        numerator *= rat.denominator;
        rat.denominator *= tmpde;
        rat.numerator *= tmpde;
    }


    public Rational(int nu, int de)
    {
        numerator = nu;
        denominator = de;
        reduce();
    }


    public void add(Rational addrat)
    {
        convert(addrat);
        numerator += addrat.numerator;
        reduce();
    }

    public void sub(Rational subrat)
    {
        convert(subrat);
        numerator -= subrat.numerator;
        reduce();
    }

    public void mul(Rational mulrat)
    {
        numerator *= mulrat.numerator;
        denominator *= mulrat.denominator;
        reduce();
    }

    public void div(Rational divrat)
    {
        numerator *= divrat.denominator;
        denominator *= divrat.numerator;
        reduce();
    }

    public void printReal()
    {
        System.out.println(1.0 * numerator / denominator);
    }

    public void printRational()
    {
        reduce();
        String output = numerator +
                (denominator == 1 ? "" : ("/" + denominator));
        System.out.println(output);
    }
}
