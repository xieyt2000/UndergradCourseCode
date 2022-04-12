package submit;

class TestFaintness {
    /**
     * In this method all variables are faint because the final value is never used.
     * Sample out is at src/test/Faintness.out
     */
    void test1() {
        int x = 2;
        int y = x + 2;
        int z = x + y;
        return;
    }

    /**
     * Write your test cases here. Create as many methods as you want.
     * Run the test from root dir using
     * ./run.sh flow.Flow submit.MySolver submit.Faintness submit.TestFaintness
     */
    // example from readme to avoid optimization of return
    int test2(int t) {
        int x = t; // x not faint
        int y = x + 2; // y faint
        int z = x + y; // z faint
        return x;  // x not faint
    }

    void f_empty(int t) {
    }

    // test other cases
    void test3(int t) {
        int x = t;
        int y = -x;  // y faint; x not faint since we don't handle unary operation
        int z = t;
        f_empty(z);  // z not faint since we don't handle invoke
        int a = t;
        int[] b = new int[a]; // b faint; a not faint since we don't handle newarray
    }

}
