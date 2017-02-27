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
int someOfAKind(int dice[],int kind);

////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	int dice[6]{1,1,1,1,1,1};
	int reRollDie[6]{ 1,0,0,0,0,1, };

	int upperScore[9]{0,0,0,0,0,0,0,0,0};		//this is the array containing the upper score
	int lowerScore[11]{0,0,0,0,0,0,0,0,0,0,0};	//this is the array containing the lower score
	//This string contains the valid choices, and the value of it.
	string choice[]{ "1","2","3","4","5","6"," "," "," ","7","8", "9","10","11","12","13","14"};
	// make a random seed
	srand(time(NULL));

//	printScore(upperScore, lowerScore, choice);

	randomizer(dice);

//	randomizeSome(dice, reRollDie);

	printDice(dice);

	
	int test = someOfAKind(dice,3);
		//checkScore(dice, 1);
	cout << test;


	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////




void randomizeSome(int *dice, int *reRollDie)
{
	// Check the reroll array. 1 means reroll, 0 means keep!
	for (int i = 0; i < 6; i++)
	{
		if(reRollDie[i] == 1)
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
		cout << i+1 << "  " << flush;
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
		"... TOTAL of lower section: ",
		"... TOTAL of upper section: ",
		".............. GRAND TOTAL: " };

	// Printing the upper scores to the screen
	for (int i = 0; i < 9; i++)
	{
		cout << choice[i] << " ." << upperScoreStr[i] << upperScore[i] << endl;
	}
	// Printing the lower scores to the screen
	for (int i = 0; i < 11; i++)
	{
		//if choice is only one digit, then print one more '-'
		if((choice[i + 9]) == "X" || choice[i + 9] == "7" || choice[i + 9] == "8" || choice[i + 9] == "9" || choice[i + 9] == " ")
			cout << choice[i + 9] << " " << lowerScoreStr[i] << lowerScore[i] << endl;
		else
		cout << choice[i+9] << "" << lowerScoreStr[i] << lowerScore[i] << endl;
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
int someOfAKind(int dice[],int kind)
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
	if (one >= kind)
		return one + (kind * 10);
	else if (two >= kind)
		return two +( kind*10);
	else if (three >= kind)
		return three + (kind * 10);
	else if (four >= kind)
		return four + (kind * 10);
	else if (five >= kind)
		return five + (kind * 10);
	else if (six >= kind)
		return six + (kind * 10);

	return 0;
}
