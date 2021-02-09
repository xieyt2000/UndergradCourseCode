import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner systemIn = new Scanner(System.in);
        final int N = systemIn.nextInt();
        Integer[] mem = new Integer[N];
        while (systemIn.hasNext()) {
            String command = systemIn.next();
            try {
                switch (command) {
                    case "=": {
                        int a = systemIn.nextInt(), b = systemIn.nextInt(), num = systemIn.nextInt();
                        for (int i = a; i < b; i++) {
                            mem[i] = num;
                        }
                        break;
                    }
                    case "+": {
                        int a = systemIn.nextInt(), b = systemIn.nextInt(), c = systemIn.nextInt();
                        int oa = mem[a], ob = mem[b];
                        mem[c] = oa + ob;
                        break;
                    }
                    case "-": {
                        int a = systemIn.nextInt(), b = systemIn.nextInt(), c = systemIn.nextInt();
                        int oa = mem[a], ob = mem[b];
                        mem[c] = oa - ob;
                        break;
                    }
                    case "*": {
                        int a = systemIn.nextInt(), b = systemIn.nextInt(), c = systemIn.nextInt();
                        int oa = mem[a], ob = mem[b];
                        mem[c] = oa * ob;
                        break;
                    }
                    case "/": {
                        int a = systemIn.nextInt(), b = systemIn.nextInt(), c = systemIn.nextInt();
                        int oa = mem[a], ob = mem[b];
                        mem[c] = oa / ob;
                        break;
                    }
                    case "?": {
                        int a = systemIn.nextInt();
                        System.out.println(mem[a] == null ? "null" : mem[a]);
                    }
                }
            } catch (NullPointerException e) {
                System.out.println("Null Number");
            } catch (ArithmeticException e) {
                System.out.println("Divided By Zero");
            } catch (ArrayIndexOutOfBoundsException e) {
                System.out.println("Illegal Address");
            }
        }
    }
}
