package hugeinteger;

import java.math.BigInteger;

public class HugeInteger
{
    BigInteger integer;

    HugeInteger(String intstr)
    {
        integer = new BigInteger(intstr);
    }

    void input(String intstr)
    {
        integer = new BigInteger(intstr);
    }

    void output()
    {
        System.out.println(integer.toString());
    }

    void add(HugeInteger adInt)
    {
        integer = integer.add(adInt.integer);
    }


    public boolean isEqualTo(HugeInteger cmpint)
    {
        return integer.equals(cmpint.integer);
    }

    public boolean isNotEqualTo(HugeInteger cmpint)
    {
        return !integer.equals(cmpint.integer);
    }

    public boolean isGreaterThan(HugeInteger cmpint)
    {
        return (integer.compareTo(cmpint.integer) == 1);
    }

    public boolean isGreaterThanOrEqualTo(HugeInteger cmpint)
    {
        return (integer.compareTo(cmpint.integer) != -1);
    }

    public boolean isLessThan(HugeInteger cmpint)
    {
        return (integer.compareTo(cmpint.integer) == -1);
    }

    public boolean isLessThanOrEqualTo(HugeInteger cmpint)
    {
        return (integer.compareTo(cmpint.integer) != 1);
    }
}
