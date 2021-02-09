import java.util.Arrays;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Sudoku sudoku = new Sudoku();
        sudoku.read();
        if (sudoku.check())
            System.out.println("yes");
        else
            System.out.println("no");
    }
}

class Sudoku {
    private int n;
    private int m;
    private int[][] matrix;

    void read() {
        Scanner input = new Scanner(System.in);
        n = input.nextInt();
        m = n * n;
        matrix = new int[m][m];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                matrix[i][j] = input.nextInt();
            }
        }
    }

    boolean check() {
        boolean[] numAppear = new boolean[m + 1];
        //test sub-matrix
        for (int subId = 0; subId < m; subId++) {
            Arrays.fill(numAppear, false);
            int rowStart = subId / n * n, colStart = subId % n * n;
            for (int i = rowStart; i < rowStart + n; i++) {
                for (int j = colStart; j < colStart + n; j++) {
                    if (numAppear[matrix[i][j]])
                        return false;
                    numAppear[matrix[i][j]] = true;
                }
            }
        }
        //test row
        for (int i = 0; i < m; i++) {
            Arrays.fill(numAppear, false);
            for (int j = 0; j < m; j++) {
                if (numAppear[matrix[i][j]])
                    return false;
                numAppear[matrix[i][j]] = true;
            }
        }
        //test column
        for (int j = 0; j < m; j++) {
            Arrays.fill(numAppear, false);
            for (int i = 0; i < m; i++) {
                if (numAppear[matrix[i][j]])
                    return false;
                numAppear[matrix[i][j]] = true;
            }
        }
        return true;
    }
}