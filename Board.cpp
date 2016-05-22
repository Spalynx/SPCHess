#include <iostream>

#include "Board.hpp"


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

	//Fills <from> with value of <to> and empties <to>
	board[m_r][m_c] = board[f_r][f_c];
	board[f_r][f_c] = '-';	
	
	return true;
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