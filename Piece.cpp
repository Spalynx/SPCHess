#include <iostream>
#include <functional>
#include <cmath>
#include "Piece.hpp"

void Piece::initialize(char type, bool white){
	if (type == '-'){
		makeBlankPiece();
		return;
	}

	//Else - isn't blank.
	piece_type = type;
	is_white = white;	//white privilege!
	moved = false;


	movement_behavior = &pawnMove;
	/*switch (type){
		case ('P'):
			movement_behavior = pawnMove;
			passant = false;
			break;
		case('R'):
			movement_behavior = rookMove;
			break;
		case('B'):
			movement_behavior = bishMove;
			break;
		case('Q'):
			movement_behavior = quenMove;
			break;
		case('N'):
			movement_behavior = nihtMove;
			break;
		case('K'):
			movement_behavior = kingMove;
			break;
	}*/
}
Piece::Piece(char type, bool white){
	initialize(type,white);
}
Piece::Piece(char type, char side){
	if(side == 'W' || side == 'w')
		initialize(type, true);
	else if (side == 'B' || side == 'b')
		initialize(type, false);
	else 	throw "Wrong side name specified! It's w or b!";
}


void Piece::itMoved()
{	moved = true;		}
bool Piece::getMoved() const
{	return moved;		}


void Piece::setType(char type){
	if( type == '-')
		makeBlankPiece();
	else piece_type = type;
}
char Piece::getType() const
{	return piece_type;	}


void Piece::switchSides()
{	(is_white) ? is_white = false : is_white = true;	}
bool Piece::getSide() const
{	return is_white;	}
char Piece::getSideChar() const{
	if (is_white)
		return 'w';
	else return 'b';
}

void Piece::makeBlankPiece(){
	piece_type 			= '-';
	is_white 			= NULL;
	moved 				= NULL;
	movement_behavior 	= emptyMove;
}


bool Piece::canMove(int piece_row, int piece_column, int to_row, int to_column){
	//Checks to see if the item is within 0-7 bounds.	
	auto within_bounds = [&](int coord){
		if ( coord > 0 && coord  <= 7)
			return true;
		else return false;
	};
	//Application of the lambda, Checks if all params are within bounds.
	if (!within_bounds(piece_row) && !within_bounds(piece_column) 
		&& !within_bounds(to_row) && !within_bounds(to_column))
			return false;

	//If it's within bounds then the coords
	return (movement_behavior)(piece_row, piece_column, to_row, to_column);
	}

bool Piece::pawnMove(int piece_r, int piece_c, int to_r, int to_c){
	//Sadly, until turn based piece rules are checked,
	//pawns are only checked to move 1 at a time.

	std::cout << "4"; system("pause");
	if( abs(piece_r - to_r) > 0 && abs(piece_r - to_r) <= 1 )
		return true;
	else return false;
	//TODO: Starter 2 mvmt, en passe, etc.
}
bool Piece::rookMove(int piece_r, int piece_c, int to_r, int to_c){
	//If there is no mvmt in y xor x, then mvmt is horiz/vert.
	 if ( 	piece_r - to_r == 0 
	 		|| piece_c - to_c == 0		)
		 return true;
	 else return false;
}
bool Piece::nihtMove(int piece_r, int piece_c, int to_r, int to_c){

	//Checks if one side is 3 long, and the other is 1 long.
	if ( 	(abs(piece_r - to_r) == 2 		|| abs(to_r - piece_r) == 2)
			&& (abs(piece_c - to_c) == 1 	|| abs(to_c - piece_c) == 1) 	)
		return true;

	else return false;
}
bool Piece::bishMove(int piece_r, int piece_c, int to_r, int to_c){

	//Checks if slope is 1 (diagonal).
	if ( abs(piece_r - to_r) == abs(piece_c - to_c) )
		return true;

	else return false;
}
bool Piece::quenMove(int piece_r, int piece_c, int to_r, int to_c){

	//If the slope of mvmt is 1, or there is no change in x or y.
	if ( 	(abs(piece_r-to_r) == abs(piece_c-to_c)) 
			|| (piece_r-to_r == 0) || (piece_c-to_c == 0) )
		return true;

	else return false;
}
bool Piece::kingMove(int piece_r, int piece_c, int to_r, int to_c){

	//If only a 1 block movement is made.
	if ( abs(piece_r-to_r) <= 1 && abs(piece_c-to_c) <= 1)
	       return true;

	else return false;		
	//TODO: Castling.
}
bool Piece::emptyMove(int piece_r, int piece_c, int to_r, int to_c){
		return false;
}