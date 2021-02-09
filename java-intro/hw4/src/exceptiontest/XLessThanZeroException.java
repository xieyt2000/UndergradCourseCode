package exceptiontest;

public class XLessThanZeroException extends Exception {
    double y;

    XLessThanZeroException(double input) {
        y = input;
    }

    String getInfo() {
        return y + " is too small";
    }
}
