#include <iostream>
#include "Board.hpp"

/** @brief This is the actual game system of the program. This might become it's own class
		or struct, but for now, it's just a small wrapper for the board class.
 *	@author Spalynx
 *	@version v.1.0.0
 */
void run_game();

//------Entry point - Main-------
int main(){
	run_game();
	return 0;
}



//------------------------------



void run_game(){
	system("cls");
	Board chess;
	std::string inputfrom = "", inputto = "";
	bool whiteturn = true;

	//Some basic starting information, The rest is shown in the 'h' option.
	std::cout << "\n\n\n\tSPCH v1.\n\t\t No rule definitions or en passant." << std::endl
			<< "\t\t\tMove Syntax example: a1 b2 or <movefrom>_<moveto>." 
			<< "\n\t\t\'h\' for help, \'Q\' to exit.\n\n\n" << std::endl;
	
	system("pause");
	while (inputfrom != "q" && inputfrom != "Q" ){
		system("cls");
		std::cout << chess;	//outputting the board
		
		//Outputs whose turn it is.
		if(whiteturn){
			std::cout << "\nW > ";
			whiteturn = false;
		}
		else {
			std::cout << "\nB > ";
			whiteturn = true;
		}//This can be used for switches later on.
		

		std::cin >> inputfrom; //Getting first word of std input.
		if (inputfrom != "q" && inputfrom != "Q"){
			/** Here contained are the options for standard input options entered.
				These options can be accessed at any time, and usually don't end the turn. */

			if (inputfrom == "h"){	//Help menu
				std::cout << std::endl << "Standard input is <from> <to>." << std::endl
					<< "\th\t\tCommand info dialog." << std::endl
					<< "\tm\t\tOperator movements." << std::endl
					<< "\t?\t\tFollowed with <from>. Shows the movement options of the piece." << std::endl 
					<< "\tsave\t\t Saves the game for later loading." << std::endl
					<< "\tload\t\t Loads the game previously saved." 
					<< std::endl;

				keepturn:
					system("pause");
					(whiteturn) ? whiteturn=false : whiteturn=true;
			}
			else if (inputfrom == "m"){	//Admin commands.
				std::cout << "OPERATOR MOVEMENT" << std::endl;
				goto keepturn;
			}
			else if (inputfrom == "?"){	//Movement options for a queried piece.
				std::cout << "MVMT options" << std::endl;
				goto keepturn;
			}

			//If none of these options are inputted, then the standard is movement.
			else {
				std::cin >> inputto; //Asks for where the piece is moved to.

				//For now, just counting on the fact that it's "ab?cd".
				chess.move(inputfrom, inputto);
			}
		}			
	}
	//GAME OVER, voluntarily I hope.
	system("cls");
	std::cout << chess;
	std::cout << "\nGood game, here is the board." << std::endl;
	//TODO: Display the winner's name/set up a way to win/lose.
}
