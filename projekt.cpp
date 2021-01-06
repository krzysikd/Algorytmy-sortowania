#include <iostream>
#include <fstream>
using namespace std;

const int n = 20; // Liczebnoœæ zbioru.

void wynik(int* tab, int n);

void merge(int* tab, int l, int s, int p)
{
    //lewa i prawa strona
	int lewa = s - l + 1;
	int prawa = p - s;

	//Tablice pomocnicze
	int* tabL = new int[lewa];
	int* tabP = new int[prawa];

	// Kopiujemy liczby do tablic pomocniczych
	for (int i = 0; i < lewa; i++)
    {
        tabL[i] = tab[l + i];
    }

	for (int j = 0; j < prawa; j++)
    {
        tabP[j] = tab[s + 1 + j];
    }


	int indexL = 0;
	int indexP = 0;
	int curr;

	//Z³aczamy tablice prawa i lewa
	for (curr = l; indexL < lewa && indexP < prawa; curr++)
	{
		if (tabL[indexL] <= tabP[indexP])
        {
            tab[curr] = tabL[indexL++];
        }
		else
        {
            tab[curr] = tabP[indexP++];
        }

	}

	//Jezeli w tablicy lewej jest jakis element, przekopiuj go
	while (indexL < lewa)
    {
        tab[curr++] = tabL[indexL++];
    }


	//Jezeli w tablicy lewej jest jakis element, przekopiuj go
	while (indexP < prawa)
    {
        tab[curr++] = tabP[indexP++];
    }


	delete[] tabL;
	delete[] tabP;
}

//Funkcja sortujaca przez scalanie
void mergeSort(int* tab, int l, int p) {
	if (p > l) {
		int s = (l + p) / 2;
		mergeSort(tab, l, s);
		mergeSort(tab, s + 1, p);
		merge(tab, l, s, p);
	}
}

void heapify(int tab[], int n, int i)
{
    int kopc = i; // Inicjowanie korzenia
    int l = 2 * i + 1; // lewo = 2*i + 1
    int p = 2 * i + 2; // prawo = 2*i + 2


    if (l < n && tab[l] > tab[kopc])     // Jezeli element jest wiekszy od korzenia
       {
            kopc = l;
       }



    if (p < n && tab[p] > tab[kopc])     // Jezeli obecny element wiekszy niz poprzedni
       {
           kopc = p;
       }



    if (kopc != i) // Jezeli najwiekszy element nie jest obecny to zamien
    {
        swap(tab[i], tab[kopc]);
        heapify(tab, n, kopc);
    }
}

//Funkcja sortujaca przez kopcowanie
void heapSort(int tab[], int n)
{
    // Budowanie kopca
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(tab, n, i);
    }


    // Jeden po drugim wyci¹gaj¹ element z kopca
    for (int i = n - 1; i > 0; i--)
        {
        // zmiana elementu tab[0] na element obecny tab[i]
            swap(tab[0], tab[i]);
            heapify(tab, i, 0);
        }
}

int main()
{
	int tab[n] = {};
    int tmp = 0; //zmienna pomocnicza

 	ifstream liczby("liczby.txt"); // otwarcie pliku tekstowego z ktorego pobierzemy liczby

	/*Wyswietl blad jezeli nie ma liczb w pliku tekstowym */
    if (!liczby)
    {
        cout << "Nie mozna otworzyc pliku";
        getchar();
    }
	/* wczytanie liczb z pliku tekstowego do tablicy */
    while (!liczby.eof())
       liczby >> tab[tmp++];

    liczby.close(); // zamkniecie pliku tekstowego

 	cout << "Tablica przed posortowaniem: " << endl;

 	/* Wypisz ciag liczb, powtarzaj od 0 do tmp (tmp=10)*/
    for (int i=0; i<tmp; i++)
        cout << tab[i] << ", "; //wyswietl obecny element tab
		cout << endl;

//wybieramy ktora metoda chcemy posortowac tablice
	int wybor;
	cout << "Wpisz cyfre! "<< endl;
	cout << "1 - sortowanie przez scalanie " << endl;
	cout << "2 - sortowanie przez kopcowanie" << endl;
    cin >> wybor;
	switch( wybor )
	{
 		case 1:
 		cout << "Wybrales sortowanie przez scalanie!" << endl;
		mergeSort(tab, 0, n-1);

    	break;

		case 2:
    	cout << "Wybrales sortowanie przez kopcowanie!" << endl;
    	heapSort(tab, n);
   		break;
	}

	cout << endl << "Oto tablica po sortowaniu:" << endl;

	wynik(tab, n);

	system("pause");
	return 0;

}

//funkcja, ktora wyswietla i zapisuje wynik do pliku
void wynik(int* tab, int n)
{
	ofstream zapis("wynik.txt"); //otwarcie pliku tekstowego do ktorego zapiszemy wynik
	zapis << "Oto tablica po sortowaniu:" << endl;
	for (int i = 0; i < n; i++)
    {
		cout << tab[i] << ", ";
		zapis << tab[i] << ", ";
	}
	cout << endl;
	zapis.close(); //zamkniecie pliku tekstowego
}

