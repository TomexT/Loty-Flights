#include <iostream>
#include <fstream>
#include <string>
#include "loty.h"
using namespace std;

bool sprParam(int argc, char *argv[], Parametr &parametry)		//funkcja sprawdzaj�ca, kt�re parametry zosta�y wpisane w konsoli
{
	string przelacznik;		//zmienna, do kt�rej jest zapisywany prze��cznik podany w konsoli
	if (argc == 2)
	{
		przelacznik = argv[1];
		if (przelacznik == "-h")
			return false;
	}
	for (int i = 0; i < argc - 1; i++)
	{
		przelacznik = argv[i];
		if (przelacznik == "-i")
		{
			parametry.filein = argv[i + 1];
			return true;
		}
	}
	//if (parametry.czy_wczytano)
	//	return true;
	//else
		return false;
}

void pomoc()	//funkcja wy�wietlaj�ca pomoc
{
	cout << "Aby wczyta� plik wej�ciowy u�yj prze��cznika \"-i\".\nNast�pnie po spacji wpisz w cudzys�owie nazw� pliku wej�ciowego (np. \"przyklad.txt\")." << endl;
}

void usunBialeZnaki(string &str)
{
	// i points to next postion to be filled in 
	// output string/ j points to next character 
	// in the original string 
	int i = 0, j = -1;

	// flag that sets to true is space is found 
	bool spacja = false;

	// Handles leading spaces 
	while (++j < str.length() && str[j] == ' ');

	// read all characters of original string 
	while (j < str.length())
	{
		if (str[j] == '\t')
			str.erase(j, 1);
		// if current characters is non-space 
		else if (str[j] != ' ')
		{
			// copy current character at index i 
			// and increment both i and j 
			str[i++] = str[j++];

			// set space flag to false when any 
			// non-space character is found 
			spacja = false;
		}
		// if current character is a space 
		else if (str[j++] == ' ')
		{
			// If space is encountered for the first 
			// time after a word, put one space in the 
			// output and set space flag to true 
			if (!spacja)
			{
				str[i++] = ' ';
				spacja = true;
			}
		}
	}
	str.erase(str.begin() + i, str.end());
}

wsk_Lot wczytanie(string nazwa)		//funkcja wczytuj�ca dane z pliku wej�ciowegoo do listy
{
	ifstream filein(nazwa);		//zmienna, do kt�rej zostanie wczytany plik wej�ciowy
	wsk_Lot wsk_glowa = nullptr;	//zmienna, b�d�ca wska�nikiem na pierwszy element listy, do kt�rej zostan� wczytane dane z pliku wej�ciowego
	int dl = 0;		//zmienna, do kt�rej zostanie wpisana d�ugo�� pliku, by sprawdzi� czy nie jest on pusty
	if (!filein)
	{
		cout << "Plik wej�ciowy \"" << nazwa << "\" nie zosta� znaleziony!" << endl << "Upewnij si�, �e ��dany plik wej�ciowy znajduje si� w folderze z tym programem." << endl;
		return wsk_glowa;
	}
	filein.seekg(0, filein.end);
	dl = filein.tellg();
	filein.seekg(0, filein.beg);
	if (dl == 0)
	{
		cout << "Plik wej�ciowy \"" << nazwa << "\" jest pusty!" << endl;
		return wsk_glowa;
	}
	Lot linia;		//struktura typu "Lot", do kt�rej zostan� wczytane dane z kolejnych linii pliku
	wsk_Lot wsk_nowa = nullptr, wsk_ogon = nullptr;		//wsk_nowa - zmienna, do kt�rej zostan� wczytane kolejne dane ze struktury "linia", wsk_ogon - zmienna, b�d�ca wska�nikiem na ostatni element listy, do kt�rej zostan� wczytane dane z pliku wej�ciowego
	bool czyPoprawnyNr;		//zmienna pomocnicza, s�u��ca do zapami�tywania czy nr by� poprawnie zapisany w pliku (czy wyst�puj� w nim tylko cyfry)
	int ile = 1;		//zmienna, do kt�rej b�dzie zapisana liczba pasa�er�w, ma wykorzystanie przy wypisywaniu komunikatu o b��dzie w danych wej�ciowych (u�atwia zlokalizowanie go w pliku)
	string str;
	int i;
	while (!filein.eof())
	{
		czyPoprawnyNr = true;
		do
		{
			getline(filein, str);
		} 
		while (str.length() == 0);
		usunBialeZnaki(str);
		i = 0;
		linia.symbol = "";
		linia.lotnisko = "";
		linia.data = "";
		linia.nazwisko = "";
		linia.nr = "";
		while (i < str.length() && str[i] != ' ')
		{
			linia.symbol += str[i];
			i++;
		}
		i++;
		while (i < str.length() && str[i] != ' ')
		{
			linia.lotnisko += str[i];
			i++;
		}
		i++;
		while (i < str.length() && str[i] != ' ')
		{
			linia.data += str[i];
			i++;
		}
		i++;
		while (i < str.length() && str[i] != ' ')
		{
			linia.nazwisko += str[i];
			i++;
		}
		i++;
		while (i < str.length() && str[i] != ' ')
		{
			linia.nr += str[i];
			i++;
		}
		if (linia.symbol.length() == 0 || linia.lotnisko.length() == 0 || linia.data.length() == 0 || linia.nazwisko.length() == 0 || linia.nr.length() == 0)
		{
			cout << "W pliku wej�ciowym \"" << nazwa << "\" w linni " << ile << " brakuje danych!" << endl << "Dane z tej linii nie zosta�y wpisane do pliku wyj�ciowego." << endl;
		}
		else
		{
			for (int i = 0; i < linia.nr.length(); i++)
				if ((char)linia.nr[i] < 48 || (char)linia.nr[i] > 57)
				{
					czyPoprawnyNr = false;
					cout << "W pliku wej�ciowym w linii " << ile << ", u pasa�era o nazwisku \"" << linia.nazwisko << "\", znajduje si� b��d w zapisie nr miejsca." << endl << "Pasa�er ten nie zosta� wpisany na list� lotu \"" << linia.symbol << "\"." << endl;
					break;
				}
			if (czyPoprawnyNr)
			{
				wsk_nowa = new Lot;
				wsk_nowa->symbol = linia.symbol;
				wsk_nowa->lotnisko = linia.lotnisko;
				wsk_nowa->data = linia.data;
				wsk_nowa->nazwisko = linia.nazwisko;
				wsk_nowa->nr = linia.nr;
				wsk_nowa->nast = nullptr;
				if (wsk_glowa == nullptr)
					wsk_glowa = wsk_ogon = wsk_nowa;
				else
				{
					wsk_ogon->nast = wsk_nowa;
					wsk_ogon = wsk_nowa;
				}
			}
		}
	}
	filein.close();
	return wsk_glowa;
}

void sortowanieListy(wsk_Lot &wsk_glowa)	//funkcja sortuj�ca list� wed�ug symboli lot�w
{
	wsk_Lot i, j;		//zmienne pomocnicze b�d�ce wska�nikami na stuktur� typu "Lot", s�u�� do przej�cia przez list�
	for (i = wsk_glowa; i != nullptr; i = i->nast)
	{
		for (j = i->nast; j != nullptr; j = j->nast)
		{
			if (i->symbol < j->symbol)
			{
				swap(i->symbol, j->symbol);
				swap(i->lotnisko, j->lotnisko);
				swap(i->data, j->data);
				swap(i->nazwisko, j->nazwisko);
				swap(i->nr, j->nr);
			}
		}
	}
}

void sortowanieNr(wsk_Lot &wsk_glowa)	//funkcja sortuj�ca list� wed�ug nr miejsc, wykonuje zamian� tylko gdy elementy listy maj� taki sam symbol
{
	wsk_Lot i, j;		//zmienne bedace wskaznikami na stukture typu "Lot", s�u�� do przej�cia przez list�
	int nr1, nr2;		//zmienne, do kt�rych s� zapisywane numery miejsc po konerwsji string na int (s� one potrzebne ze wzgl�du na niejednolity zapis nr miejsc w pliku wej�ciowym)
	string s;		//zmienna pomocniczna, do kt�rej wczytywana jest zawarto�� z listy, umo�liwia ona wykonanie konerwsji string na int
	for (i = wsk_glowa; i != nullptr; i = i->nast)
	{
		if (i->nr[0] == '0')
		{
			s = i->nr;
			s.erase(0, 1);
			nr1 = stoi(s);
		}
		else
			nr1 = stoi(i->nr);
		for (j = i->nast; j != nullptr; j = j->nast)
		{
			if (j->nr[0] == '0')
			{
				s = j->nr;
				s.erase(0, 1);
				nr2 = stoi(s);
			}
			else
				nr2 = stoi(j->nr);
			if ((i->symbol == j->symbol) && nr1 > nr2)
			{
				swap(i->symbol, j->symbol);
				swap(i->lotnisko, j->lotnisko);
				swap(i->data, j->data);
				swap(i->nazwisko, j->nazwisko);
				swap(i->nr, j->nr);
			}
		}
		if (i->nr.length() == 1)
			i->nr = " " + i->nr;
	}
}

void doPlikow(wsk_Lot wsk_glowa)	//funkcja tworz�ca i uzupe�niaj�ca pliki z list pasa�erow dla ka�dego lotu
{
	int ile = 0;
	ofstream fileout;
	string symbol = wsk_glowa->symbol;
	fileout.open(symbol + ".txt");
	fileout << "symbol lotu: " << symbol << endl
		<< "lotnisko:    " << wsk_glowa->lotnisko << endl
		<< "data lotu:   " << wsk_glowa->data << endl
		<< endl << "lista pasazerow:" << endl;
	for (wsk_glowa; wsk_glowa != nullptr; wsk_glowa = wsk_glowa->nast)
	{
		if (wsk_glowa->symbol != symbol)
		{
			fileout << endl << "liczba rezerwacji: " << ile;
			ile = 0;
			fileout.close();
			symbol = wsk_glowa->symbol;
			fileout.open(symbol + ".txt");
			fileout << right << "symbol lotu: " << symbol << endl
				<< "lotnisko:    " << wsk_glowa->lotnisko << endl
				<< "data lotu:   " << wsk_glowa->data << endl
				<< endl << "lista pasazerow:" << endl;
		}
		fileout << wsk_glowa->nr << " " << wsk_glowa->nazwisko << endl;
		ile++;
	}
	fileout << endl << "liczba rezerwacji: " << ile;
	fileout.close();
}