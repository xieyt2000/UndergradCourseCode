package complex;

public class Complex
{
    //made public according to homework requirements
    public double realPart = 0;
    public double imaginaryPart = 0;

    Complex(double r, double i)
    {
        realPart = r;
        imaginaryPart = i;
    }

    void add(Complex adNum)
    {
        realPart += adNum.realPart;
        imaginaryPart += adNum.imaginaryPart;
    }

    void sub(Complex subNum)
    {
        realPart -= subNum.realPart;
        imaginaryPart -= subNum.imaginaryPart;
    }

    void print()
    {
        String output = realPart +
                (imaginaryPart < 0 ? "" : "+") +
                imaginaryPart + "i";
        System.out.println(output);
    }
}
