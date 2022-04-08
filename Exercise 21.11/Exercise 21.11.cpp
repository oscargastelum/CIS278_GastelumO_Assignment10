/*************************************************************************
*
* Program : Module 10/ Excercise 21.11/ Hangman Game
*
* Created : 04/04/2022
*
* Programmer : Oscar Gastelum
*
*
* ************************************************************************
*  Program description/ purpose : Hang man game. User has to guess the 
* hidden word. User has 7 attempts. Each failed attempt to guess the word
* displays a new body part on the hang man. Once the user reaches 7 failed 
* attempts, the player loses the game. Lastly, the user can choose to play
* again if they wish to do so, else GOOD_BYE.
*
*-------------------------- Change History -------------------------------
* Programmer :
* Date :
* Description of change :
*
*************************************************************************/




using namespace std; // Eliminates the need to repeat the std:: prefix.
#include <string> // To use the string data type
#include <iostream> // inherits all members from parent classes istream & ostream, perform both input and output operations.
#include <vector>

#include <iomanip>
#include <algorithm>
#include <sstream>


//CONSTANTS 
const string HIDDEN_WORD{ "Turtle" };
const char CIPHER_CHAR{ 'X' };
const int MAX_GUESS{ 7 };


string hideText(const string, const char&);
string getGuess();

string getString(const string);
string stringToLower(string&);
bool getYorN(string);

void displayHeader();
void displayGuessTheWord(const string&);
void displayMan(unsigned int&);
void displayGameResult(bool&);
bool playHangMan(string&);






//main. Returns int type 
int main() {

		//display program header 
		displayHeader();

	do{
	
		//display the word to be guessed by user
		displayGuessTheWord(HIDDEN_WORD);
		
		//assing the hardcoded word as the key (can use text file later)
		string key{ HIDDEN_WORD };
	
		//play the game and determine if the player won or lost 
		bool playerGame{ playHangMan(key) };
	
		//display game results 
		displayGameResult(playerGame);
		
	
	} while (getYorN("\n  Would you like to play again? (Yes/No)"));

	cout << left << setw(2) << "" <<  "GOOD_BYE!" << endl;

}//end main




/// <summary>
/// display the game results after playing a game.
/// </summary>
/// <param name="gameResult"></param> true if won, else false
void displayGameResult(bool& gameResult) {

	if (gameResult) {
		cout << "\n" << left << setw(2) << "" << "Congratulations!!! You guessed my word." << endl;
	}
	else {
		cout << "\n" << left << setw(2) << "" << "Loser. You didn't guess my word." << endl;
	}

}




/// <summary>
/// play a game of hang man, try to find the hidden word before your chances are up.
/// </summary>
/// <param name="key"></param> The word to guess.
/// <returns></returns> true if you won the game else false.
bool playHangMan(string& key) {
	//Initialzie / Declare	
	string userGuess;
	unsigned int attempts{ 0 };

	//do while less than guess limit and not equal to key
	do {
		//get guess 
		userGuess = getGuess();

		//add the # of attempts
		++attempts;

		if (userGuess != key) {
			//display hang man
			displayMan(attempts);
		}

	} while ((userGuess != key) && (attempts < MAX_GUESS));


	//if the user guesses the word
	if (userGuess == key) {
		return true;
	}

	//else return false; lost
	return false;

}
/// <summary>
/// Get string from user using getstring memeber function
/// </summary>
/// <param name="msg"></param> the msg to display to the user
/// <returns></returns> string enter by the user
string getString(const string msg) {

	string answer;

	cout << left << setw(-40) << msg << " : " << endl;

	try {
		//ignore will flush out the buffer in between using cin 
		cin.ignore();
		//get line of input from user
		getline(cin, answer);
		cout << endl;
	}
	catch (exception e) {
		cout << "Error reading input from user. Ending program.";
		exit(EXIT_FAILURE);
	}

	return answer;
}





//-----------------------------------------------------------------------------
// C++ IR - Oscar Gastelum 04/03/2022
//-----------------------------------------------------------------------------




/// <summary>
/// conver all of a string to lower case characters
/// </summary>
/// <param name="str"></param> the string to convert to lower case 
/// <returns></returns> string in all lowercase if applicable 
string stringToLower(string& str) {
	string upperStr = "";

	for (char c : str) {
		upperStr += tolower(c);
	}
	return upperStr;
}




/// <summary>
/// Get a yes or no answer as input. Display a msg to the user.
/// </summary>
/// <param name="msg"></param> msg to display to the user.
/// <returns></returns> boolean with true for yes else false.
bool getYorN(string msg) {

	string answer = getString(msg);


	while ((stringToLower(answer) != "y")
		&& (stringToLower(answer) != "yes")
		&& (stringToLower(answer) != "n")
		&& (stringToLower(answer) != "no")) {

		//remove white spaces



		//cout << "\"" << answer << "\"" << endl;

		if (answer  == "") {
			cout << "Error: Missing y/n input." << endl;
		}
		else {
			if (   (stringToLower(answer) != "y")
				&& (stringToLower(answer) != "yes")
				&& (stringToLower(answer) != "n")
				&& (stringToLower(answer) != "no")) {
				cout << "Error: Unexpected input. (y/n) only" << endl;
			}
		}
		answer = getString(msg);
	}

	if ((stringToLower(answer) == "y") || (stringToLower(answer) == "yes") ){
		return true;
	}
	else {
		return false;
	}

}
//-----------------------------------------------------------------------------




/// <summary>
/// Display hang man, depending on the number of attempts made so far and the hang mans
/// </summary>
/// <param name="attempts"></param>
/// <param name="hManStatus"></param>
void displayMan(unsigned int& attempts) {
	//index to the body part at wich the man is currently at.
	static unsigned int hManStatus{ 0 };


	//array of body parts for the hang man to display per incorrect answer.
	string manParts[MAX_GUESS] = { "O", "/", "|", "\\", "|", "/", "\\" };
	//create the hang man string
	ostringstream outputString; // create ostring object 
	string hM1{ "	 O		\n" };
	string hM2{ "	/|\\	\n" };
	string hM3{ "	 |		\n" };
	string hM4{ "	/ \\	\n" };
	outputString << hM1 << hM2 << hM3 << hM4;
	string manString = outputString.str();

	//set the position to the last place of the body part displayed.
	hManStatus = manString.substr(hManStatus, string::npos).find(manParts[attempts - 1]) + hManStatus;

	//display the hang man, corresponding to the number of incorrect answers so far

	cout << "\n" << left << setw(2) << "" << "----------------" << endl;
	cout << left << setw(4) << "" << attempts << "/" << MAX_GUESS <<  " ATTEMPTS " << endl;
	cout << left << setw(2) << "" << "----------------" << endl;
	cout << manString.substr(0, hManStatus+1);
	cout << "\n" << left << setw(2) << "" << "----------------" << endl;

}




/// <summary>
/// Display program header with program information.
/// </summary>
void displayHeader() {

	cout << endl;
	cout << left << setw(2) << "" << " -------- HANG MAN -------- \n\n" << endl;
	cout << left << setw(2) << "" << " ---- RULES ---- " << endl;
	cout << " - You have to guess the word I'm thinking of." << endl;
	cout << " - You have 7 chances to guess my word." << endl;
	cout << " - If you guess the word before your seven chances, you WIN!\n\n" << endl;

}




/// <summary>
/// Display to the user to guess the hidden word.
/// </summary>
/// <param name="wordToGuess"></param>
void displayGuessTheWord(const string& wordToGuess) {
	cout << left << setw(2) << "" << "Guess the word : " << hideText(wordToGuess, CIPHER_CHAR) << endl;
}




/// <summary>
/// Will get the users word guess.
/// </summary>
/// <returns></returns>string : the users word guess
string getGuess() {
	string guess;
	cout << endl;
	cout << left << setw(2) << "" << "Enter your guess:\n  ?";
	cin >> guess;
	return guess;
}




/// <summary>
/// Will hide a text, replacing the characters and spaces with the 
/// char specified. 
/// </summary>
/// <param name="text"></param> the word to hide
/// <param name="c"></param> the char to replace each char in the 
/// text with. 
/// <returns></returns> a string with the same length as the word but 
/// with the characters replaced to the char specifed. 
string hideText(const string text, const char& c) {
	string s(text.size(), c);
	return s;

}