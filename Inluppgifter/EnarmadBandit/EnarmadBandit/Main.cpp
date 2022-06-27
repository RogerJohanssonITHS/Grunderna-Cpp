#include <iostream>;
#include <ctime>; // f�r random 
#include <locale.h>; // f�r svenska tecken i terminalen 

using namespace std;



// funktion som genererar ett slumptal d�r 1 <= slumptalet <= 3
int generateRandomNumber() {
	int currentNumber = rand() % 3 + 1;
	return currentNumber;
}

// funktion som returnerar ett tecken f�r spelf�ltet. 1 = A, 2 = X och 3 = O.
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

// bygg upp ett 3 x 3 - f�lt med slumpm�ssigt generade symboler A, X, O.
void generatePlayField(char playField[3][3]) {
	// loopa �ver raderna
	for (int i = 0; i < 3; i++)
	{
		// loopa �ver kolumnerna
		for (int j = 0; j < 3; j++)
		{
			playField[i][j] = charPlayField();
		}
	}
	return;
}

// funktion som kontrollerar att startinsatsen �r giltig
bool validateBet(int bet) {
	if (bet == 100 || bet == 300 || bet == 500)
	{
		return true;
	}
	else return false;
}




void printPlayField(char playField[3][3]) {
	// loopa �ver raderna
	for (int i = 0; i < 3; i++)
	{
		// loopa �ver kolumnerna
		for (int j = 0; j < 3; j++)
		{
			cout << playField[i][j];
		}
		cout << endl;
	}
	return;
}

int main() {
	char playField[3][3]{}; // f�lt som h�ller den enarmade banditens spelf�lt

	// fr� f�r slumptalsgenerering
	srand(time(0));

	// svenska tecken f�r utskrift 
	setlocale(LC_ALL, "sv_SE");

	// skapa spelarens saldo

	// fr�ga efter insats

	// skapa spelf�ltet
	generatePlayField(playField);

	// skriv ut spelf�ltet
	printPlayField(playField);

	int wins = 0; // variabel som h�ller antal vinnande kombinationer
	// r�kna vinnande rader
	for (int i = 0; i < 3; i++)
	{
		if (playField[i][0] == playField[i][1] && playField[i][1] == playField[i][2])
		{
			wins++;
		}
	}

	// r�kna vinnande kolumner
	for (int j = 0; j < 3; j++)
	{
		if (playField[0][j] == playField[1][j] && playField[1][j] == playField[2][j])
		{
			wins++;
		}
	}

	// r�kna vinnande diagonaler
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