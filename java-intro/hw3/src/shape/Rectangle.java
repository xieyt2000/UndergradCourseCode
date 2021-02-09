package shape;

public class Rectangle extends Shape
{
    protected double width, height;

    public Rectangle(double w, double h, String c)
    {
        super(c);
        width = w;
        height = h;
    }

    public Rectangle(double w, double h)
    {
        this(w, h, "");
    }

    public Rectangle()
    {
        this(0, 0);
    }

    @Override
    public double getArea()
    {
        return width * height;
    }

    @Override
    public double getPerimeter()
    {
        return 2 * (width + height);
    }

    @Override
    public String toString()
    {
        return "Rectangle" + getOutColor();
    }

    public void setWidth(double w)
    {
        width = w;
    }

    public void setHeight(double h)
    {
        height = h;
    }

    public double getWidth()
    {
        return width;
    }

    public double getHeight()
    {
        return height;
    }

}
