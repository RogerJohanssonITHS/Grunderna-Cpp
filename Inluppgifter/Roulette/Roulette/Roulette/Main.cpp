#include <iostream>;
#include <ctime>; // för random
#include <locale.h>; // för svenska tecken i terminalen

using namespace std;

// startsaldo för spelaren i kr
int saldo = 1000;
int selection = 1; //variabel för att spara spelarens val
int bet = 0; //variabel för att spara insatsen
bool okToProceed = false; //variabel för att kontrollera om insatsen är ok (storlek, saldo)
bool correctChoice = false; //variabel för att kontrollera om spelaren gjort ett korrekt val (1-36/rött, svart)
bool correctPlaystyleChoice = false; //variabel för att kontrollera om spelaren gjort ett korrekt val (1-36/rött, svart) 
int playerPlaystyleChoice = 2; //variabel för att spara spelarens val av spelsätt
int playerColor = 2; //variabel för att spara spelarens val av färg 0 = svart. 1 = rött. 2 är default.
int playerNumber = 0; //variabel för att spara spelarens val av nummer 1-36.
int currentNumber = 0; //variabel för att spara resultatet av senaste roulettsnurren
int currentColor = 0; //variabel för att spara färg på senaste roulettsnurren 0 = svart. 1 = rött.
string currentColorString = ""; //variabel för att kunna presentera resultatet för spelaren

//funktion som returnerar ett slumptal där 1 <= slumptalel <= 36
int drawNumber() {
	srand(time(0));
	return rand() % 36 + 1;
}

//funktion som returnerar true om spelaren har tillräckligt med pengar på saldot för den tänkta insatsen; annars false
bool checkBet(int bet) {
	if (bet == 100 || bet == 300 || bet == 500 && saldo >= bet) {
		//dra av insatsen från saldot
		saldo -= bet;
		return true;
	}
	if (bet != 100 && bet != 300 && bet != 500) {
		cout << "Du måste satsa 100, 300 eller 500 kr!" << endl;
		return false;
	}
	if (saldo < bet) {
		cout << "Du kan inte satsa så mycket pengar. Du har bara " << saldo << " kr kvar." << endl;
		return false;
	}
}

int main() {
	// svenska tecken för utskrift
	setlocale(LC_ALL, "sv_SE");

	//fortsätt spelet tills pengarna tar slut eller om spelaren vill avbryta i nästa steg
	while (saldo >= 0) {
		// låt spelaren välja om den vill fortsätta spela
		cout << "Vill du fortsätta spela? (0 för avbryt)" << " Du har " << saldo << " kr kvar.";
		cin >> selection;
		if (selection == 0) {
			return 0;
		}

		if (saldo < 100) {
			cout << "För lite pengar kvar för en insats";
			return 0;
		}

		// låt spelaren välja insats
		while (!okToProceed) {
			cout << "Hur mycket vill du satsa? (100, 300 eller 500)? ";
			cin >> bet;

			// kontrollera insatsen
			okToProceed = checkBet(bet);

		}

		// låt spelaren välja nummer 1-36 eller färg rött/svart
		// håll på till correctChoice är true
		while (!correctChoice) {
			while (!correctPlaystyleChoice) {
				cout << "Vill du spela på nummer (0) eller färg (1)? ";
				cin >> playerPlaystyleChoice;
				// du måste välja 0 eller 1
				if (playerPlaystyleChoice == 0 or playerPlaystyleChoice == 1) {
					correctPlaystyleChoice = true;
				}
				else cout << "Du måste välja 0 eller 1!" << endl;
			}
			// beroende på playerPlaystyleChoice så skall användaren mata in ett nummer eller en färg
			if (playerPlaystyleChoice) {
				cout << "Välj en färg(rött (1)/ svart (0))? ";
				cin >> playerColor;
				if (playerColor == 0 or playerColor == 1) {
					correctChoice = true;
				}
				else cout << "Du måste välja rött eller svart!" << endl;
			}
			else {
				cout << "Välj ett nummer(1 - 36)? ";
				cin >> playerNumber;
				if (playerNumber >= 1 and playerNumber <= 36) {
					correctChoice = true;
				}
				else cout << "Du måste välja ett tal 1 till 36!" << endl;
			}
		}
		//dra ett slumptal
		currentNumber = drawNumber();
		//bestäm färg på slumptalet. Om slumptalet modulo 2 = 0 så är talet svart. Om slumptalet modulo 2 = 1 så är talet rött.
		currentColor = currentNumber % 2;

		//skriv ut rätt nummer och färg
		if (currentColor == 1) {
			currentColorString = "röd";
		}
		else currentColorString = "svart";
		cout << "Det blev nummer " << currentNumber << " som är " << currentColorString << endl;
		//kontrollera om spelaren vunnit och
		//betala ut ev. vinst. Korrekt siffra ger 10 ggr insatsen. Korrekt färg ger 2 ggr insatsen.
		if (currentNumber == playerNumber) {
			saldo += bet * 10;
			cout << "Grattis till vinsten!" << endl;
		}

		if (currentColor == playerColor) {
			saldo += bet * 2;
			cout << "Grattis till vinsten!" << endl;
		}

		if (currentColor != playerColor and currentNumber != playerNumber) {
			cout << "Tyvärr ingen vinst!" << endl;
		}

		// återställ värden för flaggor och spelarval
		bet = 0; //variabel för att spara insatsen
		okToProceed = false; //variabel för att kontrollera om insatsen är ok (storlek, saldo)
		correctChoice = false; //variabel för att kontrollera om spelaren gjort ett korrekt val (1-36/rött, svart)
		correctPlaystyleChoice = false; //variabel för att kontrollera om spelaren gjort ett korrekt val (1-36/rött, svart) 
		playerPlaystyleChoice = 2; //variabel för att spara spelarens val av spelsätt
		playerColor = 2; //variabel för att spara spelarens val av färg 0 = svart. 1 = rött. 2 är default.
		playerNumber = 0; //variabel för att spara spelarens val av nummer 1-36.
		currentNumber = 0; //variabel för att spara resultatet av senaste roulettsnurren
		currentColor = 0; //variabel för att spara färg på senaste roulettsnurren 0 = svart. 1 = rött.

	}
	return 0;
}


