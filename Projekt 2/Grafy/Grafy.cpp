
#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include "Graf.h"

using namespace std;

///////////////////////////////////////////
/// funkcja wczytujaca graf do macierzy i listy
Graf* Wczytaj(Graf* nowy)
{
	int ilosc_krawedzi;
	int ilosc_wierz;
	int wierz_start;
	int wierz_poccz;
	int wierz_kon;
	int waga;
	string nazwa_pliku;
	ifstream plik;
	printf("podaj nazwe pliku \n");
	cin >> nazwa_pliku;


	plik.open(nazwa_pliku); 

	if (plik.good())
	{
		plik >> ilosc_krawedzi;
		plik >> ilosc_wierz;
		plik >> wierz_start;
		nowy = new Graf(ilosc_wierz); // tworzymy nowy graf
		nowy->startowy(wierz_start); // wysylamy do grafu wierzcholek startowy
		while (!plik.eof())
		{
			plik >> wierz_poccz;
			plik >> wierz_kon;
			plik >> waga;

			nowy->dodaj_element(wierz_poccz, wierz_kon, waga); // wysylamy wartosci do klasy aby stworzyc nowy element
		}

	}
	else
	{
		printf("zla nazwa pliku \n");
	}
	plik.close();
	return nowy;

}

// funkcja generujaca grafy
void generuj()
{
	int ilosc_krawedzi;
	int ilosc_wierz;
	int wierz_start;

	string nazwa_pliku;
	ofstream plik;
	int waga;
	char gestosc;
	printf("podaj nazwe pliku \n");
	cin >> nazwa_pliku;

	plik.open(nazwa_pliku);
	cout << "podaj ilosc wierzcholkow oraz wierzcholek startowy" << endl;
	cin >> ilosc_wierz >> wierz_start;
	cout << "podaj gestosc P-100% S-75% K-50% Y - 25% " << endl;
	cin >> gestosc;
	ilosc_krawedzi = (ilosc_wierz * (ilosc_wierz - 1)) / 2; // wzor na ilosc krawedzi w grafie 
	if ('P' == gestosc)
	{
		if (plik.good())
		{
			plik << ilosc_krawedzi << " " << ilosc_wierz << " " << wierz_start << endl; 

			for (int i = 0; i < ilosc_wierz; i++)
				for (int j = i; j < ilosc_wierz; j++)
					if (i != j)
					{
						waga = rand() % 100 + 1; //losujemy wage krawedzi
						plik << i << " " << j << " " << waga << endl; //zapisujemy  krawedz z waga do pliku 
						plik << j << " " << i << " " << waga << endl; // zapis krawedzi ale w druga strone
					}
		}
		else
		{
			printf("zla nazwa pliku \n");
		
		}
	}
	else 	if ('S' == gestosc)
	{
		if (plik.good())
		{
			plik << (int)(ilosc_krawedzi * 0.75) << " " << ilosc_wierz << " " << wierz_start << endl;

			for (int i = 0; i < ilosc_wierz; i++)
				for (int j = i; j < ilosc_wierz; j++)
					if (i != j)
					{
						if (j % 4 != 0 )
						{
							waga = rand() % 100 + 1;
							plik << i << " " << j << " " << waga << endl;
							plik << j << " " << i << " " << waga << endl;
						}
					}
		}
		else
		{
			printf("zla nazwa pliku \n");
		}
	}
	else 	if ('K' == gestosc)
	{
		if (plik.good())
		{
			plik << (int)(ilosc_krawedzi / 2 )<< " " << ilosc_wierz << " " << wierz_start << endl;

			for (int i = 0; i < ilosc_wierz; i++)
				for (int j = i; j < ilosc_wierz; j++)
					if (i != j)
					{
						if (j % 2 == 0 )
						{
							waga = rand() % 100 + 1;
							plik << i << " " << j << " " << waga << endl;
							plik << j << " " << i << " " << waga << endl;
						}
					}
		}
		else
		{
			printf("zla nazwa pliku \n");
		}
	}
	else 	if ('Y' == gestosc)
	{
		if (plik.good())
		{
			plik << (int)(ilosc_krawedzi /4) << " " << ilosc_wierz << " " << wierz_start << endl;

			for (int i = 0; i < ilosc_wierz; i++)
				for (int j = i; j < ilosc_wierz; j++)
					if (i != j)
					{
						if (j % 4 == 0)
						{
							waga = rand() % 100 + 1;
							plik << i << " " << j << " " << waga << endl;
							plik << j << " " << i << " " << waga << endl;
						}
					}
		}
		else
		{
			printf("zla nazwa pliku \n");

		}

	}
	plik.close();
}

				void menu()
				{
					unsigned int opcja;
					int ilosc_wierz = 1;
					Graf* Nowy = NULL;
					while (1)
					{
						cout << "1 - wyswietl dane" << endl;
						cout << "2 - generuj" << endl;
						cout << "3 - wczytaj plik" << endl;
						cout << "4 - BellmanaForda lista" << endl;
						cout << "5 - BellmanaForda Tablica" << endl;
						cout << "0 - Aby zakonczyc" << endl;

						cout << "podaj opcje" << endl;

						cin >> opcja;

						switch (opcja)
						{
						case 0: return;
						case 1:
							if (Nowy == NULL)
								cout << "brak macierzy i listy " << endl;
							else
							{
								Nowy->wyswietl();

								cout << endl << endl;
								Nowy->wyswietl_liste();
							}

							break;
						case 2:
							generuj();
							break;
						case 3:
							Nowy = Wczytaj(Nowy);
							break;
						case 4:
						{
							Nowy->BellmanaForda_Lista();
						}
						break;
						case 5:
						{
							Nowy->BellmanaForda();
						}
						break;
						default:
							cout << "Brak takiej opcji" << endl;
							break;
						}
					}
				}

				int main()
				{
					menu();

					return 0;
				}
