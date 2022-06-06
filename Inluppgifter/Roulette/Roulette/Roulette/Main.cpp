#include <iostream>;
#include <ctime>; // för random
#include <locale.h>; // för svenska tecken i terminalen

using namespace std;

// startsaldo för spelaren i kr
int saldo = 1000;
int selection = 1; //variabel för att spara spelarens val
int bet = 0; //variabel för att spara insatsen
bool okToProceed = false; //variabel för att kontrollera om insatsen är ok (storlek, saldo)

//funktion som returnerar ett slumptal däe 1 <= slumptalel <= 36
int drawNumber() {
	srand(time(0));
	return rand() % 36 + 1;
}

//funktion som returnerar true om spelaren har tillräckligt med pengar på saldot för den tänkta insatsen; annars false
bool checkBet(int bet) {
	if (bet == 100 || bet == 300 || bet == 500 && saldo >= bet) {
		return true;
	}
	if (bet != 100 && bet != 300 && bet != 500) {
		cout << "Du måste satsa 100, 300 eller 500 kr! \n";
		return false;
	}
	if (saldo < bet) {
		cout << "Du kan inte satsa så mycket pengar. Du har bara " << saldo << " kr kvar. \n";
			return false;
	}
}

int main() {
	// svenska tecken för utskrift
	setlocale(LC_ALL, "sv_SE");

	// låt spelaren välja om den vill fortsätta spela
	cout << "Vill du fortsätta spela? (0 för avbryt)" << " Du har " << saldo << " kr kvar.";
	cin >> selection;
	if (selection == 0){
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

	// välj nummer 1-36 eller färg rött/svart

	return 0;
}


