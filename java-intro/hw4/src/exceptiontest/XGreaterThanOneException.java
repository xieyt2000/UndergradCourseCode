package exceptiontest;

public class XGreaterThanOneException extends Exception {
    String getInfo() {
        return "Too large";
    }
}
