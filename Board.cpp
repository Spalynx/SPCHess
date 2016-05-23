#include <iostream>

#include "Board.hpp"
#include <cmath>

Board::Board(){
	//filling with empty chars 
	for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLUMNS; j++)
				board[i][j] = '-';
	
	//Fills the starting pieces.
	startBoard();
}
void Board::startBoard(){
	//Places pawns on the board.
	for(int i = 0; i < 8; i++){
		board[1][i] = board[COLUMNS-2][i] = 'P';
	}

	//Placing others on the board.
	char gomers []= {'R','K','B','Q','U','B','K','R'};
	
	//The top is placed as is, the bottom is placed backwards.
	for(int i = 0; i < COLUMNS; i++){ //TODO: Place in center.
		board[0][i] 		= gomers[i];
		board[ROWS-1][i]	= gomers[COLUMNS-(i+1)];
	}

}

//Should be two parts, Letter and Num: B5.
int Board::getColumn(std::string coords){
	int width; std::string letter_width;

	//Gets the letter value of the given width.
	if( coords[0] >= 64 ){
		letter_width = coords[0];
	} else if( coords[1] >= 64){
		letter_width = coords[1];
	}

	//Subtracts ascii values to get their 1-8 values
	if(letter_width[0] >= 97)
		width = (int)letter_width[0]-97;
	else if (letter_width[0] > 65)
		width = (int)letter_width[0]-65;
	else return -1; //returns a nasty if not ascii char

	//Depreciated.
	/*switch (letter_width[0]){
		case 'A': case 'a':	width = 0; break;
		case 'B': case 'b':	width = 1; break;
		case 'C': case 'c':	width = 2; break;
		case 'D': case 'd':	width = 3; break;
		case 'E': case 'e':	width = 4; break;
		case 'F': case 'f':	width = 5; break;
		case 'G': case 'g':	width = 6; break;
		case 'H': case 'h':	width = 7; break;
	} */

	return width;  
}

bool Board::move(std::string to, std::string move){
	std::string piece;

	//f_c: first column | m_r: move row
	int f_c, f_r, m_c, m_r; 

	//Gets the column of the <to> value, and converts to int.
	f_c = getColumn(to);
	if (to[0] >= 64)
		f_r = to[1]-'0';
	else
		f_r = to[0]-'0';

	//Gets the column of the <from> value, and converts to int.
	m_c = getColumn(move);
	if (move[0] >= 64)
		m_r = move[1]-'0';
	else
		m_r = move[0]-'0';

	//Grabs the references of the piece and where it's going, and
	//	places the piece in the new place.
	f_r--; m_r--;
	
	/* Checks to see if the given move is correct. */

	if( board[f_r][f_c] == '-' ) //If it's blank, return false.
		return false;
	else if( canMove(f_r, f_c, m_r, m_c) ){ //Correct case.
		//Fills <from> with value of <to> and empties <to>
		board[m_r][m_c] = board[f_r][f_c];
		board[f_r][f_c] = '-';	
		
		return true;
	}
	else	return false; //Everything else is invalid.
}

bool Board::canMove(int fr, int fc, int mr, int mc){
	//Checks to see if the item is within 0-7 bounds.
	auto within_bounds = [&](int coord){
		if ( coord > 0 && coord  <= 7)
			return true;
		else return false;
	};	

	/** THIS FUNCTION NEEDS A BUNCH OF WORK.
	 * TODO: Implement black/white side based movement.
	 * TODO: Implement en passe.
	 * TODO: Implement castling.
	 * TODO: Excluding knight, check for unwanted collisions.	
	 */

	//Application of the lambda, Checks if all params are within bounds.
	if (!within_bounds(fr) && !within_bounds(fc) 
		&& !within_bounds(mr) && !within_bounds(mc))
		return false;

	//----------Pawns----------------
	if(board[fr][fc] == 'P'){
		//Sadly, until turn based piece rules are checked,
		//pawns are only checked to move 1 at a time.
		if( abs(fr-mr) > 0 && abs(fr-mr) <= 1 )
			return true;
		else return false;
		//TODO: Starter 2 mvmt, en passe, etc.
	}
	//----------Bishop---------------
	else if(board[fr][fc] == 'B'){
		//Checks if slope is 1 (diagonal).
		if ( abs(fr - mr) == abs(fc - mc) )
			return true;
		else return false;
	}
	//----------Knight---------------
	else if(board[fr][fc] == 'K'){
		//Checks if one side is 3 long, and the other is 1 long.
		if ( (abs(fr - mr) == 2 || abs(mr - fr) == 2)
			&& (abs(fc - mc) == 1 || abs(mc - fc) == 1) )
			return true;
		else return false;
	}
	//------------Rook---------------
	else if(board[fr][fc] == 'R'){
		//If there is no mvmt in y xor x, then mvmt is horiz/vert.
		 if ( fr - mr == 0 || fc - mc == 0)
			 return true;
		 else return false;
	}
	//------------Queen--------------
	else if(board[fr][fc] == 'Q'){
		//If the slope of mvmt is 1, or there is no change in x or y.
		if ( (abs(fr-mr) == abs(fc-mc)) || (fr-mr == 0) || (fc-mc == 0) )
			return true;
		else return false;
	}
	//-------------King--------------
	else if(board[fr][fc] == 'U'){
		//If only a 1 block movement is made.
		if ( abs(fr-mr) <= 1 && abs(fc-mc) <= 1)
		       return true;
 		else return false;		
		//TODO: Castling.
	}
	else	return false;

	return false; //Don't want any unpermitted cases to make it through.
}

std::string Board::padded(char fmt){
	int padded_amount = 6; //Spaces around char.
	std::string fin = "";

	//Places spaces around a given char.
	for(int i = 1; i < padded_amount; i++){
		if (i == padded_amount/2)
			fin += fmt;
		else fin += " ";
	}
	//Adds a '|' after the padded string.
	return fin + "|";
}
