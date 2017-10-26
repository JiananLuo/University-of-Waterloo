package SudokuCSP;

public class Main {
	static long startTime;

	public static void main(String argv[]) {
		// for timer
		startTime = System.currentTimeMillis();
		// construct the Sudoku board
		SudokuBoard board = new SudokuBoard(argv[1]);
		// start fill the board with version
		board.startVersion(argv[0]);
	}
}
