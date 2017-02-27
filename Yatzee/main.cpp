#include <iostream>
#include <string>
#include <ctime>

using namespace std;

//Print the whole score table.
void printScore(int upperScore[], int lowerScore[], string choice[]);
//randomize all the dice
void randomizer(int *dice);
// print all the dice
void printDice(int *dice);
// Randomize one or more die, according to reRollDie array
void randomizeSome(int *dice, int *reRollDie);
// check how many dice have the correct value
int checkPips(int *dice, int p);
// Check if the score is valid, according to the choice. Then return the score
int checkScore(int dice[], int choice);
// Check and see if 3 or 4 of a kind, return type ex 46 = 4 of a kind of sixes
int someOfAKind(int dice[], int kind);

int menu1();

void rerollMenu(int *dice);

void checkReroll(int dices, int *reRollChoice);

void saveTheScore(int *dice, int myChoice, string *choice);

////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	int dice[6]{ 1,1,1,1,1,1 };
	int reRollDie[6]{ 1,0,0,0,0,1, };
	const int MAX_NO_OF_THROWS = 3;
	const int MAX_NO_OF_ROUNDS = 13;
	int nRounds = 1;
	int nThrows = 1;

	int upperScore[9]{ 0,0,0,0,0,0,0,0,0 };		//this is the array containing the upper score
	int lowerScore[11]{ 0,0,0,0,0,0,0,0,0,0,0 };	//this is the array containing the lower score
	//This string contains the valid choices, and the value of it.
	string choice[]{ "1","2","3","4","5","6",".",".",".","7","8", "9","10","11","12","13","14", ".", ".", "." };
	// make a random seed
	srand((unsigned int)time(NULL));
	// randomice the first dice
	randomizer(dice);

	


	int input = 3;
	while (input != 5)
	{

		cout << "Welcome to Yahtzee!!    Round: " << nRounds << "/13.    Rolls: " << nThrows << "/3" << endl;
		//Keep the score board printed
		printScore(upperScore, lowerScore, choice);
		//Keep the dice printed
		printDice(dice);

		// if all throws are used up, force player to choose save or scrap score
		if (nThrows >= 3)
		{
			cout << "-------------------------------------------------------------------------------------" << endl;
			cout << "You have no rolls left! Either save your score, or scrap a score option... or quit!!!" << endl;
			cout << "-------------------------------------------------------------------------------------" << endl;
		}

		// show the input manu, and wait for a reply
		input = menu1();


		int  myChoice = 0;
		switch (input)
		{
		case 1:	//Reroll all
			if (nThrows >= 3) //check so not all throws are used up.
				break;
			else
			{
				nThrows++;
				randomizer(dice);
				break;
			}
		case 2:	//Reroll some of the dice
			if (nThrows >= 3) //check so not all throws are used up.
				break;
			else
			{
				nThrows++;
				rerollMenu(dice);
			}
			break;
		case 3:	// save the score
			
			cout << "To what score do you wish to save your score to? " << flush;
			while (myChoice != 1 || myChoice != 2 || myChoice != 3 || myChoice != 4 || myChoice != 5 || myChoice !=6 || myChoice != 7 || myChoice != 8 || myChoice != 9 || myChoice != 10 || myChoice != 11 || myChoice != 12 || myChoice != 13 || myChoice != 14)
			{
				cout << "Wrong choice, enter a valid choice: " << flush;
				cin >> myChoice;
			}
			saveTheScore(dice, myChoice, choice);
			break;
		case 4:	// Scrap a score field
			break;
		case 5:	// Quit
			break;
		}

		


		//Clear the screen between each display
		//system("cls");
	}


	//	int test = someOfAKind(dice,4);
			//checkScore(dice, 1);
	//	cout << test;


	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////

int menu1()
{	
	int input = 0;
	cout << "1: Reroll all.    2: Reroll some.    3: Save corrent score.    4: Scrap a score field.    5: Quit." << endl;
	cout << "Please make your choice: " << flush;
	// only take numbers
	while (!(cin >> input)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	}
	cout << "You enterd: " << input << endl;
	return input;
}
////////////////////////////////////////////////////////////////////////////////////////

void rerollMenu(int *dice)
{
	int input = 0;
	//this array will contain the dice to reroll
	int reRollChoice[6]{0,0,0,0,0,0};

	cout << "Please choose up to 6 dice to reroll" << endl;
	cout << "example '135'. Dice to reroll: " << flush;
	// only take numbers
	while (!(cin >> input)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input.  Try again: ";
	}

	//check that the number contains only dice
	checkReroll(input, reRollChoice);
	//Reroll only the dices that are chosen for a reroll
	randomizeSome(dice, reRollChoice);

	cout << "You enterd: " << input << endl;
}
////////////////////////////////////////////////////////////////////////////////////////

void checkReroll(int dices, int *reRollChoice)
{
	int factor = 100000;

	for (int i = 0; i < 6; i++)
	{
		// Going throug the dices till there are none left
		if (dices >= factor)
		{
			// divide out the die and then remove the value from dices
			int die = dices / factor; 
			dices = dices - die * factor;
			//if die is bigger then 1, make it zero
			if (die > 6)
				reRollChoice[die - 1] = 0;
			else
				// stor 1 in the correct place in the array,
				// this also removes dupicates.
				reRollChoice[die-1] = 1;

			//cout << "reRollChoice = " << reRollChoice[i] << ". Factor = " << factor << ". Dices = " << dices << ". die = " << die << endl;
		}
		//move one step down through the dices
		factor = factor / 10;
	}

}
////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////

void randomizeSome(int *dice, int *reRollDie)
{
	// Check the reroll array. 1 means reroll, 0 means keep!
	for (int i = 0; i < 6; i++)
	{
		if (reRollDie[i] == 1)
			dice[i] = rand() % 6;
	}
}
////////////////////////////////////////////////////////////////////////////////////////
void randomizer(int *dice)
{	//randomize all the dice
	for (int i = 0; i < 6; i++)
	{
		dice[i] = rand() % 6;
	}
}
////////////////////////////////////////////////////////////////////////////////////////
void printDice(int *dice)
{
	//print out the dice number
	cout << endl;
	cout << "Dice No:   " << flush;
	for (int i = 0; i < 6; i++)
		cout << i + 1 << "  " << flush;
	cout << endl;
	// Print out the actuall dice
	cout << "You throw: " << flush;
	for (int i = 0; i < 6; i++)
		cout << dice[i] << "  " << flush;
	cout << endl;
}
////////////////////////////////////////////////////////////////////////////////////////
void printScore(int upperScore[], int lowerScore[], string choice[])
{

	// This is the strings containing the score names
	const string upperScoreStr[]{
		".................. Aces: ",
		".................. Twos: ",
		"................ Threes: ",
		"................. Fours: ",
		"................. Fives: ",
		"................. Sixes: ",
		"..........  Total Score: ",
		"..........  Bonus Score: ",
		"................. TOTAL: " };
	const string lowerScoreStr[]{
		"............ 3 of a kind: ",
		"............ 4 of a kind: ",
		"........ Full House, 25p: ",
		"....... Sm. Straigh, 30p: ",
		"...... Lg. Straight, 40p: ",
		"........... YAHTZEE, 60p: ",
		"................. Chance: ",
		".......... YAHTZEE BONUS: ",
		". TOTAL of lower section: ",
		". TOTAL of upper section: ",
		"............ GRAND TOTAL: " };

	// Printing the upper scores to the screen
	for (int i = 0; i < 9; i++)
	{
		if (i > 5 && i < 9)
			cout << ".";
		cout << choice[i] << "." << upperScoreStr[i] << upperScore[i] << endl;
	}
	// Printing the lower scores to the screen
	for (int i = 0; i < 11; i++)
	{
		//if choice is only one digit, then print one more '-'
		if ((choice[i + 9]) == "X" || choice[i + 9] == "7" || choice[i + 9] == "8" || choice[i + 9] == "9" || choice[i + 9] == ".")
			cout << choice[i + 9] << "." << lowerScoreStr[i] << lowerScore[i] << endl;
		else
			cout << choice[i + 9] << "" << lowerScoreStr[i] << lowerScore[i] << endl;
	}
}
////////////////////////////////////////////////////////////////////////////////////////
// check how many dice have the correct value
int checkPips(int *dice, int p)
{
	int amount = 0;
	for (int i = 0; i < 6; i++)
		if (dice[i] == p)
			amount++;
	return amount;
}/*
////////////////////////////////////////////////////////////////////////////////////////
// Check if the score is valid, according to the choice. Then return the score
int checkScore(int dice[], int choice)
{
	int score = 0;
	switch (choice)
	{	//upper selection
	case 1:
		score = checkPips(dice, 1);
		if (score > 0)
			return score;
		else
			return -1;
		break;
	case 2:
		score = checkPips(dice, 2);
		if (score > 0)
			return score;
		else
			return -1;
		break;
	case 3:
		score = checkPips(dice, 3);
		if (score > 0)
			return score;
		else
			return -1;
		break;
	case 4:
		score = checkPips(dice, 4);
		if (score > 0)
			return score;
		else
			return -1;
		break;
	case 5:
		score = checkPips(dice, 5);
		if (score > 0)
			return score;
		else
			return -1;
		break;
	case 6:
		score = checkPips(dice, 6);
		if (score > 0)
			return score;
		else
			return -1;
		break;
		// end of upper selection
	case 7: //3 of a kind
		int temp = 0;
		return 0;
		break;
	case 8: //4 of a kind
		return 0;
		break;
	case 9:
		return 0;
		break;
	case 10:
		return 0;
		break;
	case 11:
		return 0;
		break;
	case 12:
		return 0;
		break;
	case 13:
		return 0;
		break;
	case 14:
		return 0;
		break;

	}
}
*/
////////////////////////////////////////////////////////////////////////////////////////
// Check and see if 3 or 4 of a kind, return type ex 46 = 4 of a kind of sixes
int someOfAKind(int dice[], int kind)
{
	int one = 0;
	int two = 0;
	int three = 0;
	int four = 0;
	int five = 0;
	int six = 0;
	//count all occuring numbers
	for (int i = 0; i < 6; i++)
	{
		switch (dice[i])
		{
		case 1:
			one++;
			break;
		case 2:
			two++;
			break;
		case 3:
			three++;
			break;
		case 4:
			four++;
			break;
		case 5:
			five++;
			break;
		case 6:
			six++;
			break;
		}
	}
	//if any number is more then the kind, return that number
	if (one == kind)
		return one * 10 + 1;
	else if (two == kind)
		return two * 10 + 2;
	else if (three == kind)
		return three * 10 + 3;
	else if (four == kind)
		return four * 10 + 4;
	else if (five == kind)
		return five * 10 + 5;
	else if (six == kind)
		return six * 10 + 6;

	return 0;
}

void saveTheScore(int *dice, int myChoice, string *choice)
{
	bool found = false;
	string myChoiceStr = to_string(myChoice);
	//first check if the choise is valid
	for (int i = 0; i < 14; i++)
	{
		if (choice[i] == myChoiceStr)
		{
			found = true;
		}
	}

	if(found)
		cout << "Found!" << endl;
	else
		cout << "NOT found!" << endl;
		
}

