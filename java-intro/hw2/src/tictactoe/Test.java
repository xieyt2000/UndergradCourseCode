package tictactoe;

public class Test {
    public static void main(String[] args) {
//		TicTacToe game = new TicTacToe();
//
//		System.out.println( (game.place(1, 1, 1) == 0) ? "Correct! No player won." : "Wrong!");
//		/*		...
//		 *		.1.
//		 *		...
//		 */
//
//		System.out.println( (game.place(2, 1, 1) == 3) ? "Correct! The position (1,1) was occupied." : "Wrong!");
//		System.out.println( (game.place(2, 0, 1) == 0) ? "Correct! No player won." : "Wrong!");
//		/*		.2.
//		 *		.1.
//		 *		...
//		 */
//
//		System.out.println( (game.place(1, 0, 0) == 0) ? "Correct! No player won." : "Wrong!");
//		/*		12.
//		 *		.1.
//		 *		...
//		 */
//
//		System.out.println( (game.place(2, 1, 0) == 0) ? "Correct! No player won." : "Wrong!");
//		/*		12.
//		 *		21.
//		 *		...
//		 */
//
//		System.out.println( (game.place(1, 0, 2) == 0) ? "Correct! No player won." : "Wrong!");
//		/*		121
//		 *		21.
//		 *		...
//		 */
//
//		System.out.println( (game.place(2, 2, 1) == 0) ? "Correct! No player won." : "Wrong!");
//		/*		121
//		 *		21.
//		 *		.2.
//		 */
//
//		System.out.println( (game.place(1, 0, 1) == 3) ? "Correct! The position (0,1) was occupied." : "Wrong!");
//		System.out.println( (game.place(1, 2, 2) == 1) ? "Correct! Player 1 won." : "Wrong!");
//		/*		121
//		 *		21.
//		 *		.21
//		 */

        // error case
        int score = 0;
        TicTacToe game0 = new TicTacToe();
        game0.place(1, 1, 0);
        game0.place(1, 1, 1);
        if (game0.place(1, 1, 2) != 1) {
            score -= 2;
            System.out.println("error #3-3");
        }
    }
}
