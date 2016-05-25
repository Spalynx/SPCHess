#include <iostream>
#include "Board.hpp"
#include "Piece.hpp"

Board::Board(){
	//filling with empty chars 
	for (int i = 0; i < ROWS; i++)
			for (int j = 0; j < COLUMNS; j++)
				board[i][j].initialize('-', true); //WORK ON SIDING
	
	//Fills the starting pieces.
	startBoard();
}
void Board::startBoard(){
	//Places pawns on the board.
	for(int i = 0; i < 8; i++){
		board[1][i] 		.setType('P');
		board[COLUMNS-2][i] .setType('P');
	}

	//Placing others on the board.
	char gomers []= {'R','K','B','Q','U','B','K','R'};
	
	//The top is placed as is, the bottom is placed backwards.
	for(int i = 0; i < COLUMNS; i++){ //TODO: Place in center.
		board[0][i] 		.setType(	gomers[i]				);
		board[ROWS-1][i]	.setType(	gomers[COLUMNS-(i+1)]	);
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


	return width;  
}

bool Board::move(std::string to, std::string move){
	std::string piece;

	//piece_c: first column | to_r: move row
	int piece_c, piece_r, to_c, to_r; 

	//Gets the column of the <to> value, and converts to int.
	piece_c = getColumn(to);
	if (to[0] >= 64)
		piece_r = to[1]-'0';
	else
		piece_r = to[0]-'0';

	//Gets the column of the <from> value, and converts to int.
	to_c = getColumn(move);
	if (move[0] >= 64)
		to_r = move[1]-'0';
	else
		to_r = move[0]-'0';

	//Grabs the references of the piece and where it's going, and
	//	places the piece in the new place.
	piece_r--; to_r--;
	
	//-------------- Coords found, checking validity -------------------

	/* Checks to see if the given move is correct. */
	if( board[piece_r][piece_c] == '-' ) //If it's blank, return false.
		return false;
	else if( board[piece_r][piece_c].canMove(piece_r, piece_c, to_r, to_c) ){ //Correct case.
		//Fills <from> with value of <to> and empties <to>

	std::cout << "1"; system("pause");
		board[to_r][to_c] = board[piece_r][piece_c];
	std::cout << "2"; system("pause");
		board[to_r][to_c] .itMoved();
	std::cout << "3"; system("pause");
		board[piece_r][piece_c].setType('-');	
		
		return true;
	}
	return false; //Everything else is invalid.
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
