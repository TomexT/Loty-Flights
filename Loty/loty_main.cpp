#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include "loty.h"
using namespace std;

int main(int argc, char ** argv)
{
	setlocale(LC_ALL, "Polish");
	Parametr parametry;
	/*if (!sprParam(argc, argv, parametry))
	{
		pomoc();
		return 0;
	}*/
	string nazwa = "przyklad2.txt";//argv[2];		//zmienna przyjmuj¹ca nazwê pliku z parametrów podanych w konsoli
	wsk_Lot wsk_glowa = wczytanie(nazwa);	//zmienna jest inicjalizowana jako lista utworzona przez funkcje "wczytanie" i sluzy ona do wczytywania listy w kolejnych funkcjach
	if (wsk_glowa != nullptr)
	{
		sortowanieListy(wsk_glowa);
		sortowanieNr(wsk_glowa);
		doPlikow(wsk_glowa);
	}
	return 0;
}