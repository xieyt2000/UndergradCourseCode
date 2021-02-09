package shape;

public class Circle extends Shape
{
    protected double radius;

    public Circle(double r, String c)
    {
        super(c);
        radius = r;
    }

    public Circle(double r)
    {
        this(r, "");
    }

    public Circle()
    {
        this(0);
    }

    @Override
    public double getArea()
    {
        return Math.PI * radius * radius;
    }

    @Override
    public double getPerimeter()
    {
        return Math.PI * 2 * radius;
    }

    @Override
    public String toString()
    {
        return "Circle" + getOutColor();
    }

    public void setRadius(double r)
    {
        radius = r;
    }

    public double getRadius()
    {
        return radius;
    }
}
