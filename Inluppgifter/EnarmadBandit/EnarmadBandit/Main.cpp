#include <iostream>;
#include <ctime>; // för random 
#include <locale.h>; // för svenska tecken i terminalen 
#include <map>; // för dictionary

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



// funktion som skriver ut spelfältet i konsollen
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

// funktion som returnerar antal vinnande kombinationer för ett spelfält
int countWinningCombinations(char playField[3][3]) {
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

	return wins;
}

// funktion som kontrollerar att spelaren sätter in ett tillåtet belopp (100, 300 eller 500 kr)
// och returnerar det
int depositPlayerAccount() {
	int playerAccountToTest; //variabel som sparar spelarens inmatade insatsvärde

	while (true) {
		cout << "Hur mycket vill du sätta in? (100, 300 eller 500 kr)? ";
		cin >> playerAccountToTest;

		if (playerAccountToTest == 100 || playerAccountToTest == 300 || playerAccountToTest == 500) {

			break;
		}
		cout << "Du måste sätta in 100, 300 eller 500 kr!" << endl;
	}
	return playerAccountToTest;
}

// funktion som kontrollerar att spelaren satsar ett tillåtet belopp (hela kronor och tillräckligt med pengar på kontot)
// och returnerar beloppet
int getPlayerBet(int playerAccount) {
	int playerBetToTest; //variabel som sparar spelarens inmatade insatsvärde

	while (true) {
		cout << "Hur mycket vill du satsa? (hela kr)?  Du har " << playerAccount << " kr kvar.";
		cin >> playerBetToTest;

		if (playerBetToTest <= playerAccount) {

			break;
			
		}
		cout << "Du kan inte satsa så mycket!" << endl;
	}
	return playerBetToTest;
}


int main() {
	char playField[3][3]{}; // fält som håller den enarmade banditens spelfält

	// dictionary för att slå upp oddset för ett visst antal rader
	map<int, int> odds = {  {1, 2},
							{2, 3},
							{3, 4},
							{4, 5},
							{5, 7}
						 };

	// frö för slumptalsgenerering
	srand(time(0));

	// svenska tecken för utskrift 
	setlocale(LC_ALL, "sv_SE");

	// skapa spelarens saldo
	//int playerAccount = 0;

	// fråga efter insättning och spara i spelarens konto
	// (flera insatser per spelomgång tillåts? Kanske inte...)
	int playerAccount = depositPlayerAccount();

	// här börjar spelloopen
	while (true) {
		// fråga efter insats
		int bet = getPlayerBet(playerAccount);
		playerAccount -= bet;

		// skapa spelfältet
		generatePlayField(playField);

		// skriv ut spelfältet
		printPlayField(playField);

		// räkna antal vinnande kombinationer
		int wins = countWinningCombinations(playField);

		// presentera resultatet och betala ut eventuell vinst
		if (wins == 0) {
			cout << "Tyvärr ingen vinst" << endl;
		}
		else if (wins > 5) {
			cout << "Hela fältet!" << endl;
			cout << "Du vann " << bet * 10 << " kr!" << endl;
			playerAccount += bet * 10;
		}
		else {
			cout << "Grattis! Antal vinnande rader: " << wins << ". Du vann " << bet * odds[wins] << " kr!" << endl;
			playerAccount += bet * odds[wins];
		}
		// om pengarna är slut avbryts spelomgången
		if (playerAccount == 0)
		{
			cout << "Pengarna slut!";
			return 0;
		}
	}
	return 0;
}