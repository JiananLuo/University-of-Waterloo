package SudokuCSP;

import java.util.ArrayList;
import java.util.List;

public class Cell {
	private int index;
	private int val;
	private List<Integer> totalPossibleCellValues;
	private List<Integer> possibleCellValues;
	private List<Integer> friendCellIndexes;

	/**
	 * constructor for Cell
	 * @param index the index for the cell
	 * @param val the value for the cell
	 */
	public Cell(int index, int val) {
		this.index = index;
		this.val = val;
		initAllPossibleVals();
		initAllFriends();
	}

	/**
	 * initialize all friend cell index for this cell
	 */
	private void initAllFriends() {
		// create list for all other cell indexes related to this cell
		friendCellIndexes = new ArrayList<Integer>();
		int indexX = this.index % 9;
		int indexY = this.index / 9;
		// add horizontal friends
		for (int i = 0; i < 9; i++) {
			friendCellIndexes.add(indexY * 9 + i);
		}
		// remove itself
		friendCellIndexes.remove(indexX);
		// add vertical friends
		for (int i = 0; i < 9; i++) {
			friendCellIndexes.add(i * 9 + indexX);
		}
		// remove itself
		friendCellIndexes.remove(8 + indexY);
		int blockXStart = indexX / 3 * 3;
		int blockYStart = indexY / 3 * 3;
		// add block friends
		for (int j = blockYStart; j < blockYStart + 3; j++) {
			for (int i = blockXStart; i < blockXStart + 3; i++) {
				int friendIndex = j * 9 + i;
				if (!friendCellIndexes.contains(friendIndex)) {
					friendCellIndexes.add(friendIndex);
				}
			}
		}
		// remove itself
		friendCellIndexes.remove((Integer) this.index);
	}

	/**
	 * initialize all possible value for this cell
	 */
	private void initAllPossibleVals() {
		// create list of all possible values for this cell
		totalPossibleCellValues = new ArrayList<Integer>();
		possibleCellValues = new ArrayList<Integer>();
		// only add value to this list if its 0 (not filled yet)
		if (this.val == 0) {
			for (int i = 1; i < 10; i++) {
				totalPossibleCellValues.add(i);
				possibleCellValues.add(i);
			}
		}
	}

	/**
	 * get the cell index
	 * @return cell index
	 */
	public int getIndex() {
		return this.index;
	}

	/**
	 * get the cell value
	 * @returnthe cell value
	 */
	public int getVal() {
		return this.val;
	}

	/**
	 * get all cell index related to the current cell
	 * @return all cell index related to the current cell
	 */
	public List<Integer> getFriendCellIndexes() {
		return this.friendCellIndexes;
	}

	/**
	 * get all possible values for the current cell
	 * @return all possible values for the current cell
	 */
	public List<Integer> getPossibleCellValues() {
		return this.possibleCellValues;
	}

	/**
	 * set the cell value to the provided value
	 * @param val the value will overwrite this cell
	 */
	public void setVal(int val) {
		this.val = val;
		SudokuBoard.totalStep++;
		if(SudokuBoard.totalStep == 10000) {
			System.out.println("Give up! 10000 Steps.");
			System.exit(0);
		}
	}

	/**
	 * remove value from possibleCellValues
	 * @param val the value will be removed from possibleCellValues
	 */
	public void removePossibleVal(int val) {
		this.possibleCellValues.remove((Integer) val);
	}

	/**
	 * restore all possible values
	 */
	public void reStoreAllPossibleVal() {
		if (this.totalPossibleCellValues.size() != 0) {
			this.possibleCellValues = new ArrayList<Integer>();
			for (int possibleValue : totalPossibleCellValues) {
				this.possibleCellValues.add(possibleValue);
			}
		}
	}
}
