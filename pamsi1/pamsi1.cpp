// pamsi1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <ctime>
using namespace std;
int *pomocnicza; //do sortowania przez scalanie
template <typename Typ>
void wyswietl(Typ tab[], int wielkosc)
{
	
		for (int j = 0; j < wielkosc; j++)
		{
			cout << tab[j] << "  ";
		}
		cout << endl << endl;
	
}

template <typename Typ>
void SortowanieWstawianie(Typ tab[], int wielkosc)
{
	int temp;
	int j;
	for (int i = 1; i < wielkosc; i++)
	{
		
		temp = tab[i];
		j = i - 1;	//element na lewo i
		while (j >= 0 && tab[j] > temp)	//porownywanie w lewo od i
		{
			tab[j + 1] = tab[j];
			--j;
		}
		tab[j + 1] = temp;	//wstawianie wartosci ktora byla porownywana, j+1 bo sie zmniejszylo i trzeba przesunac je znowu w prawo
	}
}

template <typename Typ>
void losuj(Typ tab[], int ilosc, int wielkosc)
{
	for (int i = 0; i < ilosc; i++)
	{
		for (int j = 0; j < wielkosc; j++)
		{
			tab[i][j] = rand() % 200;
		}
		
	}
}

template <typename Typ>
void StworzKopiec(Typ tab, int wielkosc, int glowny) //glowny to index elementu na gorze kopca
{
	int temp;
	int max=glowny; //indeks korzenia
	int lewy=2*glowny+1; //indeks lewej galezi
	int prawy=2*glowny+2; //indeks prawej galezi

	if (lewy<wielkosc && tab[lewy]>tab[max]) //sprawdzenie czy wartosc w lewej galezi nie jest wieksza od korzenia
		max = lewy;

	if (prawy<wielkosc && tab[prawy]>tab[max])
		max = prawy;			//wybranie nowego indeksu najwiekszej wartosci
	if (max != glowny)			//przypisanie najwiekszej wartosci do korzenia
	{
		temp = tab[glowny];
		tab[glowny] = tab[max];
		tab[max] = temp;
		StworzKopiec(tab, wielkosc, max);
	}
}
template <typename Typ>
void SortowanieKopiec(Typ tab[], int wielkosc)
{
	int temp;
	for (int i = wielkosc / 2 - 1; i >= 0; i--)		//tworzenie kopca
	{
		StworzKopiec(tab, wielkosc, i);
	}
	for (int i = wielkosc - 1; i > 0; i--)	//usuwanie najwiekszego elementu z kopca i wstawianie na koncu tablicy
	{
		temp = tab[0];
		tab[0] = tab[i]; //ostatni element tab[i]
		tab[i] = temp;
		StworzKopiec(tab, i, 0);	//i jest wielkoscia kopca po usunieciu elementu
	}
}
template <typename Typ>
void scal(Typ tab[], int poczatek, int koniec, int srodek)
{
	int i;
	int j;
	for (i = srodek + 1; i > poczatek; i--) //wpisuje od polowy do poczatku do tab pomocniczej (polowe)
	{
		pomocnicza[i - 1] = tab[i - 1];
	}

	for (j = srodek; j < koniec; j++) //wpisuje od konca do srodka tablicy (druga polowe)
	{
		pomocnicza[koniec + srodek - j] = tab[j + 1]; 
	}

	for (int k = poczatek; k <= koniec; k++) //odbudowa pierwotnej tablicy tylko posortowanej
	{
		if (pomocnicza[j] < pomocnicza[i])
			tab[k] = pomocnicza[j--];
		else
			tab[k] = pomocnicza[i++];
	}
}
template <typename Typ>
void SortowanieScalanie(Typ tab[], int poczatek, int koniec)
{
	if (poczatek >= koniec)
		return;
	int srodek = (koniec + poczatek) / 2;
	SortowanieScalanie(tab, poczatek, srodek);
	SortowanieScalanie(tab, srodek + 1, koniec);
	scal(tab, poczatek, koniec, srodek);
}
template <typename Typ>
void Quicksort(Typ tab[], int poczatek, int koniec)
{
	int i=poczatek;
	int j=koniec;
	int temp;
	int rozdzielacz = tab[(koniec + poczatek) / 2];

	if (poczatek >= koniec)	//czy tablica jest jednoelementowa
		return;
	
		
	do
	{
		while (tab[i]< rozdzielacz)
		{
			i++;
			if (i > koniec)
				break;
		}
		while (tab[j] > rozdzielacz)
		{
			j--;
			if (j < poczatek)
				break;
		}
		if (i <= j)
		{
			temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);
	
	if(poczatek<j)	//zeby nie bylo na odwrot
	Quicksort(tab, poczatek, j);
	if(koniec>i)
	Quicksort(tab, i, koniec);
	return;
}

template <typename Typ>
void Quicksortodwrotnie(Typ tab[], int poczatek, int koniec)
{
	int i = poczatek;
	int j = koniec;
	int temp;
	int rozdzielacz = tab[(koniec + poczatek) / 2];

	if (poczatek >= koniec)	//czy tablica jest jednoelementowa
		return;


	do
	{
		while (tab[i] > rozdzielacz)
		{
			i++;
			if (i > koniec)
				break;
		}
		while (tab[j] < rozdzielacz)
		{
			j--;
			if (j < poczatek)
				break;
		}
		if (i <= j)
		{
			temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	if (poczatek < j)	//zeby nie bylo na odwrot
		Quicksortodwrotnie(tab, poczatek, j);
	if (koniec > i)
		Quicksortodwrotnie(tab, i, koniec);
	return;
}

template <typename Typ>
int quicksortdointro(Typ tab[], int poczatek, int koniec)
{
	int i = poczatek;
	int j = koniec;
	int temp;
	int rozdzielacz = tab[(koniec + poczatek) / 2];

	if (poczatek >= koniec)	//czy tablica jest jednoelementowa
		return i;


	do
	{
		while (tab[i] < rozdzielacz)
		{
			i++;
			if (i > koniec)
				break;
		}
		while (tab[j] > rozdzielacz)
		{
			j--;
			if (j < poczatek)
				break;
		}
		if (i <= j)
		{
			temp = tab[i];
			tab[i] = tab[j];
			tab[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	
	return i;
}

template<typename Typ>
void Introspektywne(Typ tab[], int wielkosc, int licznik)
{
	int i;
	if (wielkosc < 16)		//sortowanie tablic mniejszych niz 16 metoda przez wstawianie (bo najbardziej optymalnie)
	{
		SortowanieWstawianie(tab, wielkosc);
			return;
	}
	if (licznik <= 0)	//jesli quicksort wykona sie za duzo razy i jego zlozonos obliczeniowa przekroczylaby zadana wartosc to sortujemy przez kopcowanie
	{					//bo kopcowanie zawsze ma zlozonosc nlogn
		SortowanieKopiec(tab, wielkosc);
			return;
	}
	i = quicksortdointro(tab, 0, wielkosc - 1);	//zwracamy czesc tablicy z quicksorta (od tego miejsca na lewo mniejsze na prawo wieksze)
	Introspektywne(tab, i, licznik-1);	//wywolanie dla lewej czesci tablicy, zmniejszamy licznik
	Introspektywne(tab + i + 1, wielkosc - i - 1, licznik - 1);	//wywolanie dla prawej czesci zmniejszajac licznik

}

template<typename Typ>
void Intro(Typ tab[], int wielkosc)
{
	int licznik = 2 * (int)log(wielkosc);	//ustalamy licznik, taka, bo przy takiej nie przekroczymy zlozonosci nlogn
	Introspektywne(tab, wielkosc, licznik);
	SortowanieWstawianie(tab, wielkosc);
}


template<typename Typ>
void sprawdzrosnaca(Typ tab[], int wielkosc, int ilosc)
{
	for (int i = 0; i < wielkosc-1; i++)
	{
		if (tab[i] > tab[i + 1])
		{
			cout <<ilosc+1<<"   "<< "nie posortowano" <<endl<< endl;
			return;
		}
		
	}
	cout <<ilosc+1<<"  "<< "posortowano" <<endl<< endl;
	return;
}
int main()
{
	clock_t start;
	double czas;
	int ilosc = 100;		//ilosc tablic
	int wielkosc = 50000;	//wielkosc pojedynczej tablicy
	
	pomocnicza = new int[wielkosc];
	int **tab = new int*[ilosc];
	for (int i = 0; i < ilosc; i++)
	{
		tab[i] = new int[wielkosc];
	}

	losuj(tab, ilosc, wielkosc);
	for (int k = 0; k < ilosc; k++)
	{
		Quicksortodwrotnie(tab[k], 0, (int)((wielkosc - 1)));	//ile procent posortowane tablice
	}
	start = clock();
	for (int i = 0; i < ilosc; i++)
	{
		//SortowanieWstawianie(tab[i], wielkosc);
		//SortowanieKopiec(tab[i], wielkosc);
		//SortowanieScalanie(tab[i], 0, wielkosc - 1);
		//Quicksort(tab[i], 0, wielkosc-1);
		Intro(tab[i], wielkosc);
		//sprawdzrosnaca(tab[i], wielkosc, i);
		//wyswietl(tab[i], wielkosc);
	}
	czas = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "czas sortowania w sekundach  " <<endl<< czas << endl;
}


// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
