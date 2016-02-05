#ifndef __CELL_H__
#define __CELL_H__

class Cell
{
	protected:
		std::string line[5];
	public:
		/*
		 * The TextDisplay calls notifyPlayer to update the state
		 * of player
		 */
		void notifyPlayer(char piece, char active);
		/*
		 * The Controller calls notifyBuilding to update the state
		 * of a Building
		 */
		void notifyBuilding(int level);
		/*
		* Get the line of a specific cell
		*/
		std::string getLine(int lineNum);
};

#endif
