// Direkt_start.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
int main()
{
    int dag_antal, dagspris, tot_pris;
    const int skatt = 10;
    double kurs;
    cout << "Ange antal dagar och pris per dag: ";
    cin >> dag_antal >> dagspris;
    cout << "Växlingskurs? ";
    cin >> kurs;
    tot_pris = skatt + dag_antal * dagspris;
    cout << "Totalt pri: " << tot_pris << " euro"
        << " (" << tot_pris * kurs << " kr)" << endl;
}
