package shape;

public class Square extends Rectangle
{
    protected double side;    //not necessary but required in hw

    public Square(double s, String c)
    {
        super(s, s, c);
        side = s;
    }

    public Square(double s)
    {
        this(s, "");
    }

    public Square()
    {
        this(0);
    }

    @Override
    public String toString()
    {
        return "Square" + getOutColor();
    }

    public void setSide(double s)
    {
        side = width = height = s;
    }

    public double getSide()
    {
        return side;
    }
}
