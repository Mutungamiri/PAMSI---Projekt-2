#pragma once
#include <iostream>
#include <fstream>

using namespace std;
// struktura przechowujaca element listy ///
struct Element_listy {
	Element_listy * nastepny;
	int wezel;
	int waga;
};

// clasa Graf 
// przechwoujaca graf i algorytmy
//

class Graf
{
public:
	Graf(int wielkosc = 1); 
	~Graf();
	int dodaj_element(int i, int j, int wartosc);
	void wyswietl();
	void wyswietl_liste();
	void BellmanaForda_Lista();
	bool BF_L(int start);
	void BellmanaForda();
	bool BF(int start);
	void startowy(int start) { this->start = start; }
private:
	long long * sumadrogi;                 
	int * odwiedzone;                         
	Element_listy *element;  // wskaznik na element listy na nim tworzymy nowe elementy
	Element_listy **ListaGrafu; // wskaznik na wskaznik na nim tworzymy liste grafu
	int **MacierzGrafu; // Macierz grafu 
	int ilosc_wierz; 
	int ilosc_krawedzi;
	int start;
};




