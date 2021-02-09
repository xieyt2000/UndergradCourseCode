package shape;

import java.util.Arrays;

public class Shapes
{
    protected Shape[] shapeList;

    //uses clone though not specified in hw so that member doesn't change with the argument.
    public Shapes(Shape[] s)
    {
        shapeList = s.clone();
    }

    public String toString()
    {
        return Arrays.toString(shapeList);
    }


    public double getArea()
    {
        double ret = 0.0;
        for (Shape shape : shapeList)
        {
            ret += shape.getArea();
        }
        return ret;
    }

    public double getFilledArea()
    {
        double ret = 0.0;
        for (Shape shape : shapeList)
        {
            if(shape.isFilled())
                ret += shape.getArea();
        }
        return ret;
    }
}
