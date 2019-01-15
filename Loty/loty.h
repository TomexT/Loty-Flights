#ifndef LOTY_H
#define LOTY_H

#include <string>
using namespace std;

struct Parametr		//struktura 
{
	string filein;
	bool czy_wczytano = false;
};

struct Lot		//struktura umo¿liwiaj¹ca zapis konkretnych danych z poszczególnych rezerwacji zawartych w pliku wejœciowym
{
	string symbol;		//zmienna, do której jest wczytywany symbol lotu
	string lotnisko;		//zmienna, do której jest wczytywane lotnisko startowe
	string data;		//zmienna, do której jest wczytywana data lotu
	string nazwisko;		//zmienna, do której jest wczytywane nazwisko pasa¿era
	string nr;		//zmienna, do której jest wczytywany numer miejsca
	Lot* nast;		//zmienna przechowuj¹ca wskaŸnik na nastêpn¹ sturkturê typu "Lot", umo¿liwiaj¹ca tworzenie listy
};

typedef Lot* wsk_Lot;		//typ bêd¹cy wskaŸnikiem na strukturê typu "Lot"

bool sprParam(int argc, char *argv[], Parametr &parametry);
void pomoc();
void usunBialeZnaki(string &str);
wsk_Lot wczytanie(string nazwa);
void sortowanieListy(wsk_Lot &wsk_glowa);
void sortowanieNr(wsk_Lot &wsk_glowa);
void doPlikow(wsk_Lot wsk_glowa);

#endif