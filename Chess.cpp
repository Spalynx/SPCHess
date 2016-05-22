#include <iostream>
#include <array>
#include <iomanip>
#include <stdlib.h>

class Board {
public:
	const static int ROWS = 8, COLUMNS = 8;

	Board(){
		//filling with empty chars 
		for (int i = 0; i < ROWS; i++)
  			for (int j = 0; j < COLUMNS; j++)
    				board[i][j] = '-';
    	
    	//Fills the starting pieces.
		startBoard();
	}
	void startBoard(){
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
	int getColumn(std::string coords){
		int width; std::string letter_width;

		if( coords[0] >= 64 ){
			letter_width = coords[0];
		} else if( coords[1] >= 64){
			letter_width = coords[1];
		}

		switch (letter_width[0]){
			case 'A': case 'a':	width = 0; break;
			case 'B': case 'b':	width = 1; break;
			case 'C': case 'c':	width = 2; break;
			case 'D': case 'd':	width = 3; break;
			case 'E': case 'e':	width = 4; break;
			case 'F': case 'f':	width = 5; break;
			case 'G': case 'g':	width = 6; break;
			case 'H': case 'h':	width = 7; break;
		}
		
		return width;  
	}

	bool move(std::string to, std::string move){
		std::string piece;
		//f_c = first column, m_c = move column
		int f_c, f_r, m_c, m_r; 
	
		f_c = getColumn(to);
		if (to[0] >= 64)
			f_r = to[1]-'0';
		else
			f_r = to[0]-'0';

		m_c = getColumn(move);
		if (move[0] >= 64)
			m_r = move[1]-'0';
		else
			m_r = move[0]-'0';
	
		//Grabs the references of the piece and where it's going, and
		//	places the piece in the new place.
		//gohere = piece;
		f_r--; m_r--;

		board[m_r][m_c] = board[f_r][f_c];
		board[f_r][f_c] = '-';	
		
		return true;
	}

	std::string static padded(char fmt){
		int padded_amount = 6;
		std::string fin = "";

		for(int i = 1; i < padded_amount; i++){
			if (i == padded_amount/2)
				fin += fmt;
			else fin += " ";
		}
		return fin + "|";
	}
	friend std::ostream& operator<<(std::ostream& out, const Board& bd){
		auto draw_border = [&](){
			for(int i = 0; i <= 47; i++)
				out << '=';
			out << std::endl;
		};
		out << std::setiosflags(std::ios::right);

		draw_border(); //TOP

		//Goes line per line outputting the board pieces.
		for (int i = 0; i < bd.ROWS; i++){
			out << i+1 << std::setw(5) << '|'; //LEFT

  			for (int j = 0; j < bd.COLUMNS-1; j++){
 				//Prints the items
    				out << padded(bd.board[i][j]);
    			}
    			out << std::endl; //RIGHT
		
    		}
    		draw_border(); //BOTTOM

		//Output the bottom row of coords.
		out << padded('+')  << padded('A') << padded('B') << padded('C')
			<< padded('D') << padded('F') << padded('G') 
			<< padded('H');
		return out;
	}
private:
	char board [ROWS][COLUMNS];

};


void run_game(){
	Board chess;
	std::string inputfrom = "", inputto = "";
	bool whiteturn = true;

	std::cout << "SPCH v1. No rule definitions or en passant." << std::endl
			<< "Move Syntax example: a1 b2 or <movefrom>_<moveto>." 
			<< "\n\t\'Q\' to exit." << std::endl;
	system("pause");
	while (inputfrom != "q" && inputfrom != "Q" ){
		system("cls");
		std::cout << chess;
		
		if(whiteturn){
			std::cout << "\nW > ";
			whiteturn = false;
		}
		else {
			std::cout << "\nB > ";
			whiteturn = true;
		}
		

		std::cin >> inputfrom; 
		if (inputfrom != "q" && inputfrom != "Q"){
			std::cout << "theta";
			std::cin >> inputto;

			//For now, just counting on the fact that it's "ab?cd".
			chess.move(inputfrom, inputto);
		}			
	}
	std::cout << chess;
	std::cout << "\nGood game, here is the board." << std::endl;
}
int main(){
	run_game();
	return 0;
}
