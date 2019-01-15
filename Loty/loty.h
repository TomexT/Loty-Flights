#ifndef LOTY_H
#define LOTY_H

#include <string>
using namespace std;

struct Parametr		//struktura 
{
	string filein;
	bool czy_wczytano = false;
};

struct Lot		//struktura umo�liwiaj�ca zapis konkretnych danych z poszczeg�lnych rezerwacji zawartych w pliku wej�ciowym
{
	string symbol;		//zmienna, do kt�rej jest wczytywany symbol lotu
	string lotnisko;		//zmienna, do kt�rej jest wczytywane lotnisko startowe
	string data;		//zmienna, do kt�rej jest wczytywana data lotu
	string nazwisko;		//zmienna, do kt�rej jest wczytywane nazwisko pasa�era
	string nr;		//zmienna, do kt�rej jest wczytywany numer miejsca
	Lot* nast;		//zmienna przechowuj�ca wska�nik na nast�pn� sturktur� typu "Lot", umo�liwiaj�ca tworzenie listy
};

typedef Lot* wsk_Lot;		//typ b�d�cy wska�nikiem na struktur� typu "Lot"

bool sprParam(int argc, char *argv[], Parametr &parametry);
void pomoc();
void usunBialeZnaki(string &str);
wsk_Lot wczytanie(string nazwa);
void sortowanieListy(wsk_Lot &wsk_glowa);
void sortowanieNr(wsk_Lot &wsk_glowa);
void doPlikow(wsk_Lot wsk_glowa);

#endif