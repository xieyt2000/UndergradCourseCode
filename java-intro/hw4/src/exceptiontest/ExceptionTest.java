package exceptiontest;

public class ExceptionTest {
    public int getFirstValidInt() {
        while (true) {
            try {
                return Test.readInt();
            } catch (Exception ignored) {
            }
        }
    }

    public double getX(double y)
            throws XLessThanZeroException, XGreaterThanOneException {
        double x = Math.log(y);
        if (x < 0) throw new XLessThanZeroException(y);
        if (x > 1) throw new XGreaterThanOneException();
        return x;
    }

    double solve(double y) {
        try {
            return Test.solve2(y);
        } catch (XLessThanZeroException e) {
            return -1;
        } catch (XGreaterThanOneException e) {
            return -2;
        }
    }
}
