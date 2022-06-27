#include <iostream>;
#include <ctime>; // för random 
#include <locale.h>; // för svenska tecken i terminalen 

using namespace std;



// funktion som genererar ett slumptal där 1 <= slumptalet <= 3
int generateRandomNumber() {
	int currentNumber = rand() % 3 + 1;
	return currentNumber;
}

// funktion som returnerar ett tecken för spelfältet. 1 = A, 2 = X och 3 = O.
char charPlayField() {
	int number = generateRandomNumber();
	if (number == 1)
	{
		return 'A';
	}
	else if (number == 2) {
		return 'X';
	}
	else return 'O';
}

// bygg upp ett 3 x 3 - fält med slumpmässigt generade symboler A, X, O.
void generatePlayField(char playField[3][3]) {
	// loopa över raderna
	for (int i = 0; i < 3; i++)
	{
		// loopa över kolumnerna
		for (int j = 0; j < 3; j++)
		{
			playField[i][j] = charPlayField();
		}
	}
	return;
}

// funktion som kontrollerar att startinsatsen är giltig
bool validateBet(int bet) {
	if (bet == 100 || bet == 300 || bet == 500)
	{
		return true;
	}
	else return false;
}




void printPlayField(char playField[3][3]) {
	// loopa över raderna
	for (int i = 0; i < 3; i++)
	{
		// loopa över kolumnerna
		for (int j = 0; j < 3; j++)
		{
			cout << playField[i][j];
		}
		cout << endl;
	}
	return;
}

int main() {
	char playField[3][3]{}; // fält som håller den enarmade banditens spelfält

	// frö för slumptalsgenerering
	srand(time(0));

	// svenska tecken för utskrift 
	setlocale(LC_ALL, "sv_SE");

	// skapa spelarens saldo

	// fråga efter insats

	// skapa spelfältet
	generatePlayField(playField);

	// skriv ut spelfältet
	printPlayField(playField);

	int wins = 0; // variabel som håller antal vinnande kombinationer
	// räkna vinnande rader
	for (int i = 0; i < 3; i++)
	{
		if (playField[i][0] == playField[i][1] && playField[i][1] == playField[i][2])
		{
			wins++;
		}
	}

	// räkna vinnande kolumner
	for (int j = 0; j < 3; j++)
	{
		if (playField[0][j] == playField[1][j] && playField[1][j] == playField[2][j])
		{
			wins++;
		}
	}

	// räkna vinnande diagonaler
	if (playField[0][0] == playField[1][1] && playField[1][1] == playField[2][2])
	{
		wins++;
	}
	if (playField[0][2] == playField[1][1] && playField[1][1] == playField[2][0])
	{
		wins++;
	}

	cout << wins;

	return 0;
}