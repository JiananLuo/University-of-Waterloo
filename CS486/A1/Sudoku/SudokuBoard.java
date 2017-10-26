package SudokuCSP;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SudokuBoard {
	private List<Cell> board;
	static int totalStep = 0;

	/**
	 * constructor for SudokuBoard
	 * @param fileName the input file to construct the class
	 */
	public SudokuBoard(String fileName) {
		// construct board via input file
		board = new ArrayList<Cell>();
		try {
			Scanner scanner = new Scanner(new File(fileName));
			for (int col = 0; col < 9; col++) {
				for (int row = 0; row < 9; row++) {
					this.board.add(new Cell((col * 9 + row), scanner.nextInt()));
				}
			}
		} catch (Exception e) {
			// something goes wrong when read in
			System.out.println("Bad input file: " + fileName);
			e.printStackTrace();
			System.exit(1);
		}

		// initialize possible values for all cell
		for (Cell cell : board) {
			removePossibleValForFriendCells(cell.getIndex());
		}
	}

	/**
	 * Remove possible value for friend cell
	 * @param cellIndex index for the cell
	 */
	private void removePossibleValForFriendCells(int cellIndex) {
		int val = board.get(cellIndex).getVal();
		for (int friendCellIndex : board.get(cellIndex).getFriendCellIndexes()) {
			board.get(friendCellIndex).removePossibleVal(val);
		}
	}

	/**
	 * Main loop for Version A : Standard backtracking search
	 */
	private void versionALoop() {
		// find first unfilled cell
		Cell firstEmptyCell = findFirstEmptyCell();
		// try all possible values
		for (int possibleValue : firstEmptyCell.getPossibleCellValues()) {
			firstEmptyCell.setVal(possibleValue);
			// check if the value will crush the board
			if (!isGoodBoard(firstEmptyCell)) {
				// if still possible values left for this cell, try them
				continue;
			} else {
				// when a possible value won't break the board, try to fill the rest of the board
				versionALoop();
			}
		}
		// if all possible value not good, set it back to 0, and try other possible values
		firstEmptyCell.setVal(0);
	}

	/**
	 * Version B : Standard backtracking search + forward checking
	 */
	private void versionBLoop() {
		// find first unfilled cell
		Cell firstEmptyCell = findFirstEmptyCell();
		// try all possible values
		for (int possibleValue : firstEmptyCell.getPossibleCellValues()) {
			firstEmptyCell.setVal(possibleValue);
			// after set value, recalculate all possible values
			for (int friendCellIndex = 0; friendCellIndex < 81; friendCellIndex++) {
				board.get(friendCellIndex).reStoreAllPossibleVal();
			}
			for (Cell cell : board) {
				removePossibleValForFriendCells(cell.getIndex());
			}
			// when a possible value won't break the board, try to fill the rest of the board
			versionBLoop();
		}
		// if fail restore original friend cell possible values
		firstEmptyCell.setVal(0);
	}

	/**
	 * Version C : Standard backtracking search + forward checking + heuristics
	 */
	private void versionCLoop() {
		// find first unfilled cell
		Cell firstEmptyCell = findFirstEmptyCellWithLeastPossibleValue();
		// try all possible values
		for (int possibleValue : firstEmptyCell.getPossibleCellValues()) {
			firstEmptyCell.setVal(possibleValue);
			// after set value, recalculate all possible values
			for (int friendCellIndex = 0; friendCellIndex < 81; friendCellIndex++) {
				board.get(friendCellIndex).reStoreAllPossibleVal();
			}
			for (Cell cell : board) {
				removePossibleValForFriendCells(cell.getIndex());
			}
			// when a possible value won't break the board, try to fill the rest of the board
			versionCLoop();
		}
		// if fail restore original friend cell possible values
		firstEmptyCell.setVal(0);
	}

	/**
	 * find first unfilled cell && if board filled and no errors, should be good
	 * @return the first unfilled cell
	 */
	private Cell findFirstEmptyCell() {
		// find first unfilled cell
		Cell firstEmptyCell = null;
		for (Cell cell : board) {
			if (cell.getVal() == 0) {
				firstEmptyCell = cell;
			}
		}
		// if board filled and no errors, should be good
		if (firstEmptyCell == null) {
			boardComplete();
		}
		return firstEmptyCell;
	}

	/**
	 * find first unfilled cell with least # of possible value. If board filled and no errors, should be good.
	 * @return first unfilled cell with least # of possible value
	 */
	private Cell findFirstEmptyCellWithLeastPossibleValue() {
		// find first unfilled cell
		int h = Integer.MAX_VALUE;
		Cell firstEmptyCell = null;
		for (Cell cell : board) {
			if (cell.getVal() == 0) {
				if (cell.getPossibleCellValues().size() == 1) {
					firstEmptyCell = cell;
					break;
				} else if (cell.getPossibleCellValues().size() < h) {
					h = cell.getPossibleCellValues().size();
					firstEmptyCell = cell;
				}
			}
		}
		// if board filled and no errors, should be good
		if (firstEmptyCell == null) {
			boardComplete();
		}
		return firstEmptyCell;
	}

	/**
	 * When fill a empty cell, check if it will crush the board
	 * @param currentCell the cell being filled
	 * @return a boolean value to indicate the board state
	 */
	public boolean isGoodBoard(Cell currentCell) {
		int cellValue = currentCell.getVal();
		List<Integer> friendCells = currentCell.getFriendCellIndexes();
		for (int friendCell : friendCells) {
			if (board.get(friendCell).getVal() == cellValue) {
				return false;
			}
		}
		return true;
	}

	/**
	 * When board is complete, print board and message
	 */
	private void boardComplete() {
		this.printBoard();
		System.out.println("Total step: " + this.totalStep);
		long endTime = System.currentTimeMillis();
		long totalTime = endTime - Main.startTime;
		System.out.println("Run time: " + totalTime + "ms");
		System.exit(0);
	}

	/**
	 * Run program with given version
	 * @param version the para version 'A' || 'B' || 'C'
	 */
	public void startVersion(String version) {
		if (version.equals("A")) {
			versionALoop();
		} else if (version.equals("B")) {
			versionBLoop();
		} else if (version.equals("C")) {
			versionCLoop();
		} else {
			System.out.println(version);
			System.out.println("Error, Incorrect version!");
			System.exit(1);
		}
		System.out.println("Total step: " + this.totalStep);
		System.out.println("Unsolvable!");
	}

	/**
	 * Print the Sudoku board
	 */
	public void printBoard() {
		int counter = 0;
		for (Cell cell : board) {
			System.out.print(cell.getVal() + " ");
			counter++;
			if (counter % 9 == 0) {
				System.out.println();
			}
		}
	}
}
