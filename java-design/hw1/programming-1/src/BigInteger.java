
class BigInteger implements EasyInteger {
    // TODO define user specified fields
    // Warning 1: For Open and Close Principle, non-private fields are illegal.
    // Warning 2: References, arrays contain High-precision Numbers are illegal.
    //          For extension, all non-primitive or non-Number types are illegal.
    // Example for 1: public int len;(error) -> private int len;(correct)
    // Example for 2: java.math.BigInteger $233;(error) -> Number $233;(error) -> Object $233;(error)
    // Example for 2(extension): java.util.Vector $233;(error)
    // Example(primitive type): int[] num, nn[];(correct)
    // Example(primitive boxed in Number object): Integer[] num, nn[];(correct)

    private int[] intArr;    //reversed. e.g. 12345 stored as 54321
    private int intLen;      //length of intArr

    /**
     * This constructor convert String to BigInteger.
     *
     * @param s the input String, only contains character 0-9
     */
    BigInteger(final String s) {
        // TODO implements this constructor
        intLen = s.length();
        intArr = new int[intLen];
        for (int i = 0; i < intLen; i++) {
            intArr[i] = Character.getNumericValue(s.charAt(intLen - 1 - i));
        }
    }

    BigInteger(final int[] arr, final int len) {
        intArr = arr.clone();
        intLen = len;
    }

    /**
     * Calculate the value of (this + val).
     * This method don't change input arguments.
     *
     * @param val The value to add to this
     * @return a new Integer whose value is (this + val)
     */
    @Override
    public EasyInteger add(final EasyInteger val) {
        final BigInteger v = (BigInteger) val;
        BigInteger result = null;
        // TODO let result <- this + v
        int maxLen = Math.max(intLen, v.intLen);
        int[] resArr = new int[6000];
        for (int i = 0; i < maxLen; i++) {
            resArr[i] += intArr[i] + v.intArr[i];
            if (resArr[i] > 9) {
                resArr[i + 1]++;
                resArr[i] -= 10;
            }

        }
        int resLen = ((resArr[maxLen] == 0 )? maxLen : (maxLen + 1));
        result = new BigInteger(resArr, resLen);
        return result;
    }

    /**
     * Convert this to String.
     *
     * @return the String representation of this
     */
    @Override
    public String toString() {
        final StringBuilder s = new StringBuilder();
        // TODO use s.append(...) to build the string
        for (int i = intLen - 1; i >= 0; i--) {
            s.append(intArr[i]);
        }
        return s.toString();
    }

    // TODO define user specified methods

}
