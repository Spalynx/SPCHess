#include <iostream>
#include <functional>

#ifndef PIECE_HPP
#define PIECE_HPP

/*	TODO: Implement a decaying sort of behavior when the other player finishes their next turn.
 *		Maybe overload canMove with the pieces' reference?
 *	TODO: King checkmate properties. That's gonna be really difficult.
 *
 */


/** @brief The Piece class performs the functions of an over all wrapper for all
 *		standard chess pieces (Fairy chess maybe?). To summarize as succintly as possibly, it's really
 *		just a character wrapper with extra variables and helper functions.
 	This class doesn't inherit, or contain any pointers of the board array, because so far, the only
 		gain would be having an in-class collision detector. Though, it doesn't fit the intended theme
 		for the board class, it seems ludicrous for each piece to have control of the board.
 *	@author Spalynx
 *	@since v.1.2.1-5.24.16
 		Last Edit: 1.2.1
 *
 */
class Piece {
public:
	static const bool verbose_ostream_output = false; /*!< Only used for verbose output in ostream operator.*/

	/** \brief The constructor fills all of the private variables of the function. If '-' is filled, all
	 *		of the variables will be emptied.
	 *	@param type 	The name or type that is displayed. 'P' for pawn, as an example.
	 *	@param white 	Whether or not the piee is on the white side #whiteprivilege.
	 *	@see 	makeBlankPiece()
	 */
	Piece(char type, bool white);
	/**	\brief	Mostly for readability, allows the user to enter 'w' or 'b' instead of t/f for side.
	 *	@see Piece(char,bool)
	 */
	Piece(char type, char side);
	void initialize(char type, bool white);
	Piece() {
		makeBlankPiece();
	}
	~Piece(){
		delete &movement_behavior;
	}
	/** \brief Copies by value the contents of the Piece, and sets moved to true.
	 */
	Piece& operator= (Piece& p){
		//do the thing!
		passant				= p.passant;
		is_white			= p.is_white;
		piece_type			= p.piece_type;
		movement_behavior	= p.movement_behavior;

		return p;
	}
	bool operator== (char t){
		return (piece_type == t) ?  true : false;
	}

	/** \brief OH GOD WHO TOUCHED IT?! This function always turns has_moved to true, therefore has_moved can
	 *		only be false until this function is called.
	 */
	void itMoved();
	/** \brief Returns the value of whether the piece has ever been moved before.
	 *	@return If the piece has been moved or not.
	 */
	bool getMoved() const;


	/* \brief An accessor for the piece type. "-" empties all vars in the piece.
	*	@param type The tag that the piece is changed to.
	*	@see makeBlankPiece()
	*/

	void setType(char type);
	/* Returns the character tag of the piece. */
	char getType() const;


	/* Flips the sides of the piece. */
	void switchSides();
	/*	Returns the boolean value of the piece that answers the question, is_white?
	 *	(True for white, Falce for black).
	 */
	bool getSide() const;
	/*	Same as getSide, but returns either 'w' or 'b' depending on which side.	 */
	char getSideChar() const;

	/**	\brief Makes the piece a '-' piece. This function makes is_white and moved null, and makes can move
	 *	always return false.
	 */
	void makeBlankPiece();

	/** \brief This function checks whether or not the piece can move to the given coordinates, it is passed
	 *		directly to one of the private behavior functions.
	 *	Intra-Piece collisions are handled by the board.
	 *	Please note, I wasn't sure if I wanted int coords of pieces in each object, so for now, they are
	 *		recieved as params in this function. Therefore, the program can simply just lie about coordinates,
	 *	and remain unchecked.
	 *	If this turns out to be too cumbersome, refactor here.
	 *
	 *	@param piece_row The row of this given piece. 
	 *	@param piece_column	The column of this piece.
	 *	@param to_row	The row of the intended destination.
	 *	@param to_column The column of the intended destination.
	 *
	 *	@return Whether or not the piece can move to the given destination.
	 */
	bool canMove(int piece_row, int piece_column, int to_row, int to_column);

	/** \brief A simple output operator for the piece. This function is meant to be called 64 times
	 *		per display of the board. This function also allows verbose output of the board, for
	 *		saving and reloading usage.
	 */
	friend std::ostream& operator<<(std::ostream& out, const Piece& bd) {
		if (verbose_ostream_output) //Addition of metadata planned.
			out << bd.getSideChar() << bd.getType();
		else
			out << bd.getType();

		return out;
	}

	

private:
	bool moved, 			/*!< Has the piece ever been moved before? */
			passant, 		/*!< If the move is able to be taken en passant. */
				is_white;	/*!< Which side are you on? */
	char piece_type;		/*!< The type of piece this is. [P,K,B,R,N,Q] are options. */

	bool (Piece::*movement_behavior) (int,int,int,int);	/*!< A functional object of the behavior that this piece exhibits. */


	/** \brief	Contains the properties of whether or not a pawn can move to a place or not.
	 *	TODO: Specify diagonal capturing, en passant, and 2 space starting.
	 *		Note: en passant can be implemented via checking if the to be captured piece is a pawn,
	 *			and if it's going to be in en passant.
	 *	TODO: Prohibit backwards movement based upon what side the piece is on.
	 */
	bool pawnMove(int piece_r, int piece_c, int to_r, int to_c);

	/**	\brief Specifies the behavior on if a rook can move to a specific place.
	 *	COMPLETE	*/
	bool rookMove(int piece_r, int piece_c, int to_r, int to_c);

	/**	\brief Specifies the behavior on if a knight can move to a specific place.
	 *	COMPLETE	*/
	bool nihtMove(int piece_r, int piece_c, int to_r, int to_c);

	/**	\brief Specifies the behavior on if a bishop can move to a specific place.
	 *	COMPLETE	*/
	bool bishMove(int piece_r, int piece_c, int to_r, int to_c);

	/**	\brief Specifies the behavior on if a queen can move to a specific place.
	 *	COMPLETE	*/
	bool quenMove(int piece_r, int piece_c, int to_r, int to_c);

	/**	\brief Specifies the behavior on if a king can move to a specific place.
	 *	TODO: Everything. The king needs a lot of work regarding check/checkmate.
	 */
	bool kingMove(int piece_r, int piece_c, int to_r, int to_c);

	bool emptyMove(int piece_r, int piece_c, int to_r, int to_c);
};

#endif