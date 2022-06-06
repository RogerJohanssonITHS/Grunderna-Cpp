#include <iostream>;
#include <ctime>; // f�r random
#include <locale.h>; // f�r svenska tecken i terminalen

using namespace std;

// startsaldo f�r spelaren i kr
int saldo = 1000;
int selection = 1; //variabel f�r att spara spelarens val
int bet = 0; //variabel f�r att spara insatsen
bool okToProceed = false; //variabel f�r att kontrollera om insatsen �r ok (storlek, saldo)

//funktion som returnerar ett slumptal d�e 1 <= slumptalel <= 36
int drawNumber() {
	srand(time(0));
	return rand() % 36 + 1;
}

//funktion som returnerar true om spelaren har tillr�ckligt med pengar p� saldot f�r den t�nkta insatsen; annars false
bool checkBet(int bet) {
	if (bet == 100 || bet == 300 || bet == 500 && saldo >= bet) {
		return true;
	}
	if (bet != 100 && bet != 300 && bet != 500) {
		cout << "Du m�ste satsa 100, 300 eller 500 kr! \n";
		return false;
	}
	if (saldo < bet) {
		cout << "Du kan inte satsa s� mycket pengar. Du har bara " << saldo << " kr kvar. \n";
			return false;
	}
}

int main() {
	// svenska tecken f�r utskrift
	setlocale(LC_ALL, "sv_SE");

	// l�t spelaren v�lja om den vill forts�tta spela
	cout << "Vill du forts�tta spela? (0 f�r avbryt)" << " Du har " << saldo << " kr kvar.";
	cin >> selection;
	if (selection == 0){
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

	// v�lj nummer 1-36 eller f�rg r�tt/svart

	return 0;
}


