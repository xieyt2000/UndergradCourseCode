package shape;

public abstract class Shape
{
    protected String color;

    public Shape(String c)
    {
        color = c;
    }

    public Shape()
    {
        this("");
    }

    public String getColor()
    {
        return color;
    }

    public void setColor(String c)
    {
        color = c;
    }

    public boolean isFilled()
    {
        return !color.equals("");
    }

    public abstract double getArea();

    public abstract double getPerimeter();

    public abstract String toString();

    protected String getOutColor()  //space and parentheses included
    {
        return " (" + (isFilled() ? color : "#") + ")";
    }
}
