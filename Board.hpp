#include <iostream>
#include <iomanip>
#include "Piece.hpp"

#ifndef BOARD_HPP
#define BOARD_HPP

/** @brief This class is an emulation of a chess board and pieces.
		Admittedly, all chess pieces are controlled by this class, so the scheme hardly fits. The board 
		holds the ability to move pieces, and contains the movement rules of each piece.
 *	@author Spalynx
 *	@since v.1.0.0-5.17.16
		Last Edit: 1.2.2
 */
class Board {
public:
	const static int ROWS = 8, COLUMNS = 8; /*!< The bounds of the board 2d array. */

	/** \brief Fills the board with '-' characters, and then calls startBoard() 
	 *		for filling of actual pieces.
	 *	@see startBoard()
	 */
	Board();

	/**	\brief Builds and initializes the board, fills with standard ascii
	 *		characters.
	 */
	void startBoard();

	/** \brief Recieves coords of a piece and returns what column it's on.
	 *		In effect, it converts A-H to 1-8.
	 *
	 *	@param coords Contains the coords of a piece.
	 *	@return Returns what column the piece is on. 
	 */
	int getColumn(std::string coords);

	/** \brief Moves a piece on a board from one place to the other.
	 *		As of v1 this moves items with impunity, chess rules be damned!
	 *	@param to The coordinate piece that will be moved.
	 *	@param move The coordinate that piece will be moved to.
	 *	@return If the movement is valid or not.
	 *	@see canMove()
	 */
	bool move(std::string to, std::string move);

	/** \brief Pads a character so as to streamline output in the ostream operator.
	 *	@param fmt the char to surround with padding.
	 *	@return Padded character.
	 */
	std::string static padded(char fmt);

	/** \brief Outputs the overall board with all the pieces and grid.
	 */
	friend std::ostream& operator<<(std::ostream& out, const Board& bd) {
		//Lambda function to draw top and bottom borders.
		auto draw_border = [&](){
			for(int i = 0; i <= 47; i++)
				out << '=';
			out << std::endl;
		};
		out << std::setiosflags(std::ios::right);	//right justifies texxt

		draw_border(); //TOP border

		//Goes line per line outputting the board pieces.
		for (int i = 0; i < bd.ROWS; i++){
			out << (i+1) << std::setw(5) << '|'; //LEFTmost border.

  			for (int j = 0; j < bd.COLUMNS-1; j++){ //Iterates COLUMNS times
 				//Prints the items
    			out << ""<< padded( bd.board[i][j].getType() );
    		} out << std::endl;
    	}
    	draw_border(); //BOTTOM border

		//Output the bottom row of coords.
		out << padded('+');
		for(int i = 65; i < 65+7; i++){
			out << padded(i);
		}
		return out;
	}

private:
	Piece board [ROWS][COLUMNS]; 	/*!< The underlying board container, a 2d array, 8x8 size. */
};
#endif
