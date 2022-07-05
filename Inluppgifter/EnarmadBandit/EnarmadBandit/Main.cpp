#include <iostream>;
#include <ctime>; // f�r random 
#include <locale.h>; // f�r svenska tecken i terminalen 
#include <map>; // f�r dictionary

using namespace std;

// deklaration f�r funktion som genererar ett slumptal d�r 1 <= slumptalet <= 3
int generateRandomNumber();

// deklaration f�r funktion som returnerar ett tecken f�r spelf�ltet. 1 = A, 2 = X och 3 = O
char charPlayField();

// deklaration f�r funktion som bygger upp ett 3 x 3 - f�lt med slumpm�ssigt generade symboler A, X, O
void generatePlayField(char playField[3][3]);

// deklaration f�r funktion som kontrollerar att startinsatsen �r giltig
bool validateBet(int bet);

// deklaration f�r funktion som skriver ut spelf�ltet i konsollen
void printPlayField(char playField[3][3]);

// deklaration f�r funktion som returnerar antal vinnande kombinationer f�r ett spelf�lt
int countWinningCombinations(char playField[3][3]);

// deklaration f�r funktion som kontrollerar att spelaren s�tter in ett till�tet belopp (100, 300 eller 500 kr)
// och returnerar det
int depositPlayerAccount();

// deklaration f�r funktion som kontrollerar att spelaren satsar ett till�tet belopp (hela kronor och tillr�ckligt med pengar p� kontot)
// och returnerar beloppet
int getPlayerBet(int playerAccount);

// deklaration f�r funktion som presenterar resultatet av spelomg�ngen och betalar ut eventuell vinst.
// returnerar ett uppdaterad v�rde p� spelarens konto
int presentResult(int bet, int wins, int playerAccount);

int main() {
	// f�lt som h�ller den enarmade banditens spelf�lt
	char playField[3][3]{}; 

	// fr� f�r slumptalsgenerering
	srand(time(0));

	// svenska tecken f�r utskrift 
	setlocale(LC_ALL, "sv_SE");


	// v�lkomstmeddelande
	cout << "V�lkommen till den Enarmade Banditen!" << endl;
	// fr�ga efter ins�ttning och spara i spelarens konto
	// (flera insatser per spelomg�ng till�ts inte)
	int playerAccount = depositPlayerAccount();

	// h�r b�rjar spelloopen
	while (true) {
		// variabel f�r att spara spelarens val om att forts�tta eller avbryta
		int playerChoice;

		// fr�ga efter insats
		int bet = getPlayerBet(playerAccount);
		playerAccount -= bet;

		// skapa spelf�ltet
		generatePlayField(playField);

		// skriv ut spelf�ltet
		printPlayField(playField);

		// r�kna antal vinnande kombinationer
		int wins = countWinningCombinations(playField);

		// presentera resultatet och betala ut eventuell vinst
		playerAccount = presentResult(bet, wins, playerAccount);

		// fr�ga om spelaren vill forts�tta spela
		cout << "Vill du forts�tta eller avbryta spelet? (0 f�r att avbryta; alla andra tal forts�tter)" << endl;
		cin >> playerChoice;
		if (!playerChoice) {
			cout << "Tack f�r att du spelade!" << endl;
			return 0;
		}

		// om pengarna �r slut kan spelaren v�lja att s�tta in mer pengar eller avsluta spelomg�ngen
		if (playerAccount == 0)
		{
			cout << "Pengarna slut!" << endl;
			cout << "Vill du s�tta in mer pengar eller avbryta spelet? (0 f�r att avbryta; alla andra tal forts�tter)" << endl;
			cin >> playerChoice;
			if (!playerChoice) {
				cout << "Tack f�r att du spelade!" << endl;
				return 0;
			}
			// s�tt in mer pengar
			playerAccount = depositPlayerAccount();
		}
	}
	return 0;
}
	// funktion som genererar ett slumptal d�r 1 <= slumptalet <= 3
	int generateRandomNumber() {
		int currentNumber = rand() % 3 + 1;
		return currentNumber;
	}

	// funktion som returnerar ett tecken f�r spelf�ltet. 1 = A, 2 = X och 3 = O
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

	// funktion som bygger upp ett 3 x 3 - f�lt med slumpm�ssigt generade symboler A, X, O
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

	// funktion som skriver ut spelf�ltet i konsollen
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

	// funktion som returnerar antal vinnande kombinationer f�r ett spelf�lt
	int countWinningCombinations(char playField[3][3]) {
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

		return wins;
	}

	// funktion som kontrollerar att spelaren s�tter in ett till�tet belopp (100, 300 eller 500 kr)
	// och returnerar det
	int depositPlayerAccount() {
		int playerAccountToTest; //variabel som sparar spelarens inmatade insatsv�rde

		while (true) {
			cout << "Hur mycket vill du s�tta in? (100, 300 eller 500 kr)? ";
			cin >> playerAccountToTest;

			if (playerAccountToTest == 100 || playerAccountToTest == 300 || playerAccountToTest == 500) {

				break;
			}
			cout << "Du m�ste s�tta in 100, 300 eller 500 kr!" << endl;
		}
		return playerAccountToTest;
	}

	// funktion som kontrollerar att spelaren satsar ett till�tet belopp (hela kronor och tillr�ckligt med pengar p� kontot)
	// och returnerar beloppet
	int getPlayerBet(int playerAccount) {
		int playerBetToTest; //variabel som sparar spelarens inmatade insatsv�rde

		while (true) {
			cout << "Hur mycket vill du satsa? (hela kr)?  Du har " << playerAccount << " kr kvar. ";
			cin >> playerBetToTest;

			if (playerBetToTest <= playerAccount) {

				break;

			}
			cout << "Du kan inte satsa s� mycket!" << endl;
		}
		return playerBetToTest;
	}

	// funktion som presenterar resultatet av spelomg�ngen och betalar ut eventuell vinst.
	// returnerar ett uppdaterad v�rde p� spelarens konto
	int presentResult(int bet, int wins, int playerAccount) {
		// dictionary f�r att sl� upp oddset f�r ett visst antal rader {antal vinnande rader, odds}
		map<int, int> odds = { {1, 2},
								{2, 3},
								{3, 4},
								{4, 5},
								{5, 7}
		};

		if (wins == 0) {
			cout << "Tyv�rr ingen vinst" << endl;
			cout << "Du har nu " << playerAccount << " kr p� ditt konto." << endl;
		}
		else if (wins > 5) {
			cout << "Hela f�ltet!" << endl;
			cout << "Du vann " << bet * 10 << " kr!" << endl;
			playerAccount += bet * 10;
			cout << "Du har nu " << playerAccount << " kr p� ditt konto." << endl;
		}
		else {
			cout << "Grattis! Antal vinnande rader: " << wins << ". Du vann " << bet * odds[wins] << " kr!" << endl;
			playerAccount += bet * odds[wins];
			cout << "Du har nu " << playerAccount << " kr p� ditt konto." << endl;
		}
		return playerAccount;
	}
