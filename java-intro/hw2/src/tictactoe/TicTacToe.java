package tictactoe;

public class TicTacToe
{
    // 1 for player1, 2 for player2, 0 for empty/not finished
    private int[][] board;  //index starts from 0, row first. consistent with the input

    public TicTacToe()
    {
        board = new int[3][3];  //to avoid board misuse, only allocates 3*3.
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = 0;
            }
        }
    }

    private int checkRow()
    {
        for (int i = 0; i < 3; i++)
        {
            // wrong wrong wrong if + && board[][] != 0
            if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
            {
                return board[i][0];
            }
        }
        return 0;
    }

    private int checkColumn()
    {
        for (int i = 0; i < 3; i++)
        {
            if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
            {
                return board[0][i];
            }
        }
        return 0;
    }

    private int checkDiag()
    {
        if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
        {
            return board[0][0];
        }
        if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
        {
            return board[0][2];
        }
        return 0;
    }

    private int getResult()
    {
        int[] checkRes = {checkRow(), checkColumn(), checkDiag()};
        for (int i = 0; i < 3; i++)
        {
            if (checkRes[i] != 0)
            {
                return checkRes[i];
            }
        }
        return 0;
    }


    int place(int player, int row, int column)
    {
        if (board[row][column] != 0)
        {
            return 3;
        }
        board[row][column] = player;
        return getResult();
    }
}


