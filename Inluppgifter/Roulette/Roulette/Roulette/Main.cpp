#include <iostream>;
#include <ctime>; // f�r random
#include <locale.h>; // f�r svenska tecken i terminalen

using namespace std;

// startsaldo f�r spelaren i kr
int saldo = 1000;
int selection = 1; //variabel f�r att spara spelarens val
int bet = 0; //variabel f�r att spara insatsen
bool okToProceed = false; //variabel f�r att kontrollera om insatsen �r ok (storlek, saldo)
bool correctChoice = false; //variabel f�r att kontrollera om spelaren gjort ett korrekt val (1-36/r�tt, svart)
bool correctPlaystyleChoice = false; //variabel f�r att kontrollera om spelaren gjort ett korrekt val (1-36/r�tt, svart) 
int playerPlaystyleChoice = 2; //variabel f�r att spara spelarens val av spels�tt
int playerColor = 2; //variabel f�r att spara spelarens val av f�rg 0 = svart. 1 = r�tt. 2 �r default.
int playerNumber = 0; //variabel f�r att spara spelarens val av nummer 1-36.
int currentNumber = 0; //variabel f�r att spara resultatet av senaste roulettsnurren
int currentColor = 0; //variabel f�r att spara f�rg p� senaste roulettsnurren 0 = svart. 1 = r�tt.
string currentColorString = ""; //variabel f�r att kunna presentera resultatet f�r spelaren

//funktion som returnerar ett slumptal d�r 1 <= slumptalel <= 36
int drawNumber() {
	srand(time(0));
	return rand() % 36 + 1;
}

//funktion som returnerar true om spelaren har tillr�ckligt med pengar p� saldot f�r den t�nkta insatsen; annars false
bool checkBet(int bet) {
	if (bet == 100 || bet == 300 || bet == 500 && saldo >= bet) {
		//dra av insatsen fr�n saldot
		saldo -= bet;
		return true;
	}
	if (bet != 100 && bet != 300 && bet != 500) {
		cout << "Du m�ste satsa 100, 300 eller 500 kr!" << endl;
		return false;
	}
	if (saldo < bet) {
		cout << "Du kan inte satsa s� mycket pengar. Du har bara " << saldo << " kr kvar." << endl;
		return false;
	}
}

int main() {
	// svenska tecken f�r utskrift
	setlocale(LC_ALL, "sv_SE");

	//forts�tt spelet tills pengarna tar slut eller om spelaren vill avbryta i n�sta steg
	while (saldo >= 0) {
		// l�t spelaren v�lja om den vill forts�tta spela
		cout << "Vill du forts�tta spela? (0 f�r avbryt)" << " Du har " << saldo << " kr kvar.";
		cin >> selection;
		if (selection == 0) {
			return 0;
		}

		if (saldo < 100) {
			cout << "F�r lite pengar kvar f�r en insats";
			return 0;
		}

		// l�t spelaren v�lja insats
		while (!okToProceed) {
			cout << "Hur mycket vill du satsa? (100, 300 eller 500)? ";
			cin >> bet;

			// kontrollera insatsen
			okToProceed = checkBet(bet);

		}

		// l�t spelaren v�lja nummer 1-36 eller f�rg r�tt/svart
		// h�ll p� till correctChoice �r true
		while (!correctChoice) {
			while (!correctPlaystyleChoice) {
				cout << "Vill du spela p� nummer (0) eller f�rg (1)? ";
				cin >> playerPlaystyleChoice;
				// du m�ste v�lja 0 eller 1
				if (playerPlaystyleChoice == 0 or playerPlaystyleChoice == 1) {
					correctPlaystyleChoice = true;
				}
				else cout << "Du m�ste v�lja 0 eller 1!" << endl;
			}
			// beroende p� playerPlaystyleChoice s� skall anv�ndaren mata in ett nummer eller en f�rg
			if (playerPlaystyleChoice) {
				cout << "V�lj en f�rg(r�tt (1)/ svart (0))? ";
				cin >> playerColor;
				if (playerColor == 0 or playerColor == 1) {
					correctChoice = true;
				}
				else cout << "Du m�ste v�lja r�tt eller svart!" << endl;
			}
			else {
				cout << "V�lj ett nummer(1 - 36)? ";
				cin >> playerNumber;
				if (playerNumber >= 1 and playerNumber <= 36) {
					correctChoice = true;
				}
				else cout << "Du m�ste v�lja ett tal 1 till 36!" << endl;
			}
		}
		//dra ett slumptal
		currentNumber = drawNumber();
		//best�m f�rg p� slumptalet. Om slumptalet modulo 2 = 0 s� �r talet svart. Om slumptalet modulo 2 = 1 s� �r talet r�tt.
		currentColor = currentNumber % 2;

		//skriv ut r�tt nummer och f�rg
		if (currentColor == 1) {
			currentColorString = "r�d";
		}
		else currentColorString = "svart";
		cout << "Det blev nummer " << currentNumber << " som �r " << currentColorString << endl;
		//kontrollera om spelaren vunnit och
		//betala ut ev. vinst. Korrekt siffra ger 10 ggr insatsen. Korrekt f�rg ger 2 ggr insatsen.
		if (currentNumber == playerNumber) {
			saldo += bet * 10;
			cout << "Grattis till vinsten!" << endl;
		}

		if (currentColor == playerColor) {
			saldo += bet * 2;
			cout << "Grattis till vinsten!" << endl;
		}

		if (currentColor != playerColor and currentNumber != playerNumber) {
			cout << "Tyv�rr ingen vinst!" << endl;
		}

		// �terst�ll v�rden f�r flaggor och spelarval
		bet = 0; //variabel f�r att spara insatsen
		okToProceed = false; //variabel f�r att kontrollera om insatsen �r ok (storlek, saldo)
		correctChoice = false; //variabel f�r att kontrollera om spelaren gjort ett korrekt val (1-36/r�tt, svart)
		correctPlaystyleChoice = false; //variabel f�r att kontrollera om spelaren gjort ett korrekt val (1-36/r�tt, svart) 
		playerPlaystyleChoice = 2; //variabel f�r att spara spelarens val av spels�tt
		playerColor = 2; //variabel f�r att spara spelarens val av f�rg 0 = svart. 1 = r�tt. 2 �r default.
		playerNumber = 0; //variabel f�r att spara spelarens val av nummer 1-36.
		currentNumber = 0; //variabel f�r att spara resultatet av senaste roulettsnurren
		currentColor = 0; //variabel f�r att spara f�rg p� senaste roulettsnurren 0 = svart. 1 = r�tt.

	}
	return 0;
}


