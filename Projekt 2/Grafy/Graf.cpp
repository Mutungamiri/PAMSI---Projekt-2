#include "pch.h"
#include "Graf.h"

using namespace std;
/// tworzy i dodje elemnt do listy oraz macierzy
int Graf::dodaj_element(int i, int j, int wartosc)
{
	element = new Element_listy; // tworzenie nowego obielktu na wskazniku
	element->wezel = j; // dodanie wierzcholka koncowego
	element->waga = wartosc; // dodanie wagi miedzy i a j
	element->nastepny = ListaGrafu[i];  /// dodanie elementu listy jako nastepny
	ListaGrafu[i] = element; // wrzucenie elementu na liste
	return MacierzGrafu[i][j] = wartosc; // dpodanie wartosci dla indexow i, j gdzie i to wezel poczatkowa j koncowa
}


void Graf::wyswietl()
{
	for (int i = 0; i < ilosc_wierz; i++)
	{
		for (int j = 0; j < ilosc_wierz; j++)
		{
			std::cout << MacierzGrafu[i][j] << "\t";
		}
		std::cout << endl;
	}
}


Graf::Graf(int wielkosc)
{
	ilosc_wierz = wielkosc; // zapisanie ilosic wierz 
	
	// tworzenie macierzy dwu wymiarowje///
	MacierzGrafu = new int*[ilosc_wierz];  

	for (int i = 0; i < ilosc_wierz; i++)
		MacierzGrafu[i] = new int[ilosc_wierz];

	///////////////////////////////////////////////////////

	//wypenianie macierzy grafu 0 0 oiznacza brak polaczenia//
	for (int i = 0; i < ilosc_wierz; i++)
		for (int j = 0; j < ilosc_wierz; j++)
			MacierzGrafu[i][j] = 0;

	//////////////////////////////////////////////////////////////

	//tworznie listy grafu//
	ListaGrafu = new Element_listy*[ilosc_wierz];
	// wypelniaie wskaznikow listy wartoscia NULL//
	for (int i = 0; i < ilosc_wierz; i++)
		ListaGrafu[i] = NULL;



}



bool Graf::BF_L(int start)
{
	int i, x;
	Element_listy * pv; // pivot element chodzacy po lsicie

	sumadrogi[start] = 0; // suma  scierzek do wezla
	for (i = 1; i < ilosc_wierz; i++)  // iteruje tyle ile jest wierzcholkow
	{
		
		for (x = 0; x < ilosc_wierz; x++)
			for (pv = ListaGrafu[x]; pv; pv = pv->nastepny) // przesowa sie po wierzcholkach
				if (sumadrogi[pv->wezel] > sumadrogi[x] + pv->waga) // sprawdza czy suma drogi jest wieksz od sumy drogoi z wezlem obok
				{
					
					sumadrogi[pv->wezel] = sumadrogi[x] + pv->waga; // dodanie wagi do sumy
					odwiedzone[pv->wezel] = x; // dopdnie wezla do drogi
				}
		
	}
	/// sprawdzenie czy niema ujmnych scierzek
	for (x = 0; x < ilosc_wierz; x++)
		for (pv = ListaGrafu[x]; pv; pv = pv->nastepny)
			if (sumadrogi[pv->wezel] > sumadrogi[x] + pv->waga)
				return false;

	return true;
}


bool Graf::BF(int start)
{
	int i, x;
	

	sumadrogi[start] = 0;
	for (i = 1; i < ilosc_wierz; i++)
	{
		
		for (x = 0; x < ilosc_wierz; x++)
			for (int j = 0; j < ilosc_wierz; j++)
				if (sumadrogi[j] > sumadrogi[x] + MacierzGrafu[x][j] && MacierzGrafu[x][j] != 0)
				{
		
					sumadrogi[j] = sumadrogi[x] + MacierzGrafu[x][j];
					odwiedzone[j] = x;
				}

	}



	for (x = 0; x < ilosc_wierz; x++)
		for (int j = 0; j < ilosc_wierz; j++)
			if (sumadrogi[j] > sumadrogi[x] + MacierzGrafu[x][j] && MacierzGrafu[x][j] != 0) return false;

	return true;
}

void Graf::BellmanaForda_Lista() {

	int i, x, sptr, *S;
		bool czy_koniec;
		sumadrogi = new long long[ilosc_wierz];  // suma wag danej sciezki
	odwiedzone = new int[ilosc_wierz]; // tablica odwiedzin
	for (i = 0; i < ilosc_wierz; i++)
	{
		sumadrogi[i] = INT_MAX; // jako sume podajemy  nieskonczoneosc w teori w praktyce max inat
		odwiedzone[i] = -1; // -1 oznacz nie odwiedzony
	}

	czy_koniec = BF_L(start);  // wywolanie glownej funkci BF
	if (czy_koniec)
	{
		S = new int[ilosc_wierz];  // scierzka
		sptr = 0; // iterator scierzki


		ofstream plik;
		plik.open("WynikiLista.txt");   // otwarcie pliku do zapisyu
		for (i = 0; i < ilosc_wierz; i++)
		{
			plik << i << ": ";  // wierzcholek startowy
			for (x = i; x != -1; x = odwiedzone[x]) 
				S[sptr++] = x;  // zapis scierzki

			while (sptr)
				plik << S[--sptr] << " "; // wyspianie scierzki

			if (sumadrogi[i] == INT_MAX) // spradzenie czy wierz nalezal do grafu
			{
				plik << "koszt : wezel nie polaczony" << endl;
			}
			else
			{
				plik << "koszt : " << sumadrogi[i] << endl;
			}
		}

		delete[] S;
	}
	else cout << "ujemna sciezka" << endl;
}


void Graf::BellmanaForda() {

	int i, x, sptr, *S;
	bool czy_koniec;
	sumadrogi = new long long[ilosc_wierz];
	odwiedzone = new int[ilosc_wierz]; /// macierz wierz odwiedzonych
	for (i = 0; i < ilosc_wierz; i++)
	{
		sumadrogi[i] = INT_MAX;
		odwiedzone[i] = -1;  // -1 nie odwiedzony
	}
	cout << endl;
	czy_koniec = BF(start);

	if (czy_koniec)
	{
		S = new int[ilosc_wierz];
		sptr = 0;


		ofstream plik;
		plik.open("WynikiTab.txt");
		for (i = 0; i < ilosc_wierz; i++)
		{
			plik << i << ": ";
			for (x = i; x != -1; x = odwiedzone[x])
				S[sptr++] = x;

			while (sptr)
				plik << S[--sptr] << " ";

			if(sumadrogi[i] == INT_MAX)
			{
				plik << "koszt : wezel nie polaczony" << endl;
			}
			else
			{
				plik << "koszt : " << sumadrogi[i] << endl;
			}
		}

		delete[] S;
	}
	else cout << "ujemna sciezka" << endl;
}


void Graf::wyswietl_liste()
{
	Element_listy *pomocniczy; // element pomocniczy
	for (int i = 0; i < ilosc_wierz; i++)
	{
		cout << "L[" << i << "] ="; // nr wezla poczatkowego
		pomocniczy = ListaGrafu[i]; // zapisanie  elementu listy do pomocniczej
		while (pomocniczy)
		{
			cout << pomocniczy->wezel << "(" << pomocniczy->waga << ") "; // wypisaywanie wierz i wag az trafi na NULL co oznacza brak kolejnych polonczen
			pomocniczy = pomocniczy->nastepny; // przejscie do nastepnego elementu listy
		}
		cout << endl;
	}
}



Graf::~Graf()
{
	for (int i = 0; i < ilosc_wierz; i++)
		delete[] MacierzGrafu[i];
	delete[] MacierzGrafu;

	delete[] ListaGrafu;
}