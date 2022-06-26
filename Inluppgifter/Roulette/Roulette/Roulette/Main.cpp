#include <iostream>;
#include <ctime>; // f�r random
#include <locale.h>; // f�r svenska tecken i terminalen

using namespace std;

// variabelinitieringar
int saldo = 1000; // startsaldo f�r spelaren i kr
int selectionContinue = 1; // variabel f�r att spara spelarens val.
int bet = 0; // variabel f�r att spara insatsen
bool okToProceed = false; // variabel f�r att kontrollera om insatsen �r ok (storlek, saldo)
bool correctChoice = false; // variabel f�r att kontrollera om spelaren gjort ett korrekt val (1-36/r�d, svart)
bool correctPlaystyleChoice = false; // variabel f�r att kontrollera om spelaren gjort ett korrekt val (1-36/r�d, svart) 
int playerPlaystyleChoice = 2; // variabel f�r att spara spelarens val av spels�tt
int playerColor = 2; // variabel f�r att spara spelarens val av f�rg 0 = svart. 1 = r�d. 2 �r default.
int playerNumber = 0; // variabel f�r att spara spelarens val av nummer 1-36.
int currentNumber = 0; // variabel f�r att spara resultatet av senaste roulettsnurren
int currentColor = 0; // variabel f�r att spara f�rg p� senaste roulettsnurren 0 = svart. 1 = r�d.
string currentColorString = ""; // variabel f�r att kunna presentera resultatet f�r spelaren


int main() {
	// svenska tecken f�r utskrift
	setlocale(LC_ALL, "sv_SE");

	// forts�tt spelet tills pengarna tar slut eller om spelaren vill avbryta i n�sta steg
	while (true) {

		// l�t spelaren v�lja om den vill forts�tta spela
		cout << "Vill du forts�tta spela? (0 f�r avbryt)" << " Du har " << saldo << " kr kvar.";
		cin >> selectionContinue;
		if (selectionContinue == 0) {
			return 0;
		}

		// l�t spelaren v�lja insats
		while (!okToProceed) {
			cout << "Hur mycket vill du satsa? (100, 300 eller 500 kr)? ";
			cin >> bet;

			// kontrollera insatsens storlek och mot saldot
			if (bet != 100 && bet != 300 && bet != 500) {
				cout << "Du m�ste satsa 100, 300 eller 500 kr!" << endl;
			}
			else if(saldo < bet) {
				cout << "Du kan inte satsa s� mycket pengar. Du har bara " << saldo << " kr kvar." << endl;
			}
			if ((bet == 100 || bet == 300 || bet == 500) && saldo >= bet) {
				//dra av insatsen fr�n saldot och presentera saldot efter insats
				saldo -= bet;
				cout << "Insatsen �r betald. Du har " << saldo << " kr kvar." << endl;
				okToProceed = true;
			}
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
				cout << "V�lj en f�rg(svart (0)/ r�d (1))? ";
				cin >> playerColor;
				if (playerColor == 0 or playerColor == 1) {
					correctChoice = true;
				}
				else cout << "Du m�ste v�lja svart eller r�d!" << endl;
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
		// dra ett slumptal d�r 1 <= slumptalet <= 36
		srand(time(0));
		currentNumber = rand() % 36 + 1;
		// best�m f�rg p� slumptalet. Om slumptalet modulo 2 = 0 s� �r talet svart. Om slumptalet modulo 2 = 1 s� �r talet r�tt.
		currentColor = currentNumber % 2;

		// skriv ut r�tt nummer och f�rg
		if (currentColor == 1) {
			currentColorString = "r�d";
		}
		else currentColorString = "svart";
		cout << "Det blev nummer " << currentNumber << " som �r " << currentColorString << endl;

		// kontrollera om spelaren vunnit och
		// betala ut ev. vinst. Korrekt siffra ger 10 ggr insatsen. Korrekt f�rg ger 2 ggr insatsen.
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

		// kontrollera saldot mot minsta insats
		if (saldo < 100)
		{
			cout << "F�r lite pengar kvar f�r en insats!";
			return 0;
		}

		// �terst�ll v�rden f�r flaggor och spelarval
		okToProceed = false; // variabel f�r att kontrollera om insatsen �r ok (storlek, saldo)
		correctChoice = false; // variabel f�r att kontrollera om spelaren gjort ett korrekt val (1-36/r�tt, svart)
		correctPlaystyleChoice = false; // variabel f�r att kontrollera om spelaren gjort ett korrekt val (1-36/r�d, svart) 
		playerPlaystyleChoice = 2; // variabel f�r att spara spelarens val av spels�tt
		playerColor = 2; // variabel f�r att spara spelarens val av f�rg 0 = svart. 1 = r�d. 2 �r default.
	}
}