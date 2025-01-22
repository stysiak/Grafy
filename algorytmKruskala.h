#pragma once
#include "header.h"

void Kruskal(string plik)
{
    fstream odczyt;
    odczyt.open(plik, ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }

    int n, m, v1, v2;
    odczyt >> n >> m; // odczytujemy liczbę wierzchołków i krawędzi

    // Tworzenie dynamicznej macierzy sąsiedztwa
    int** tab = new int* [n];
    for (int i = 0; i < n; ++i)
    {
        tab[i] = new int[n];
        for (int j = 0; j < n; ++j)
        {
            tab[i][j] = 0; // Inicjalizacja macierzy zerami
        }
    }
    int* tabWagi = new int[m]; //tablica z wagamia danej krawedzi
    for (int i = 0; i < m; i++)
    {
        odczyt >> tabWagi[i];
    }
    int* tabKrawedzie = new int[2 * m];
    for (int i = 0; i < (2 * m); i++)
    {
        odczyt >> tabKrawedzie[i];
    }
    // Odczyt krawędzi i aktualizacja macierzy sąsiedztwa
    int j = 0;
    for (int i = 0; i < m; i++)
    {
        v1 = tabKrawedzie[j];  
        v2 = tabKrawedzie[j + 1];
        tab[v1-1][v2-1] = tabWagi[i];
        tab[v2-1][v1-1] = tabWagi[i];
        j = j + 2;
        
    }
    int k = 0;
    //wyswietlanie listy krawedzi z wagami
    cout << "Ilosc wierzcholkow: " << n << ", ilosc krawedzi: " << m << endl;
    for (int i = 0; i < m; ++i)
    {
        cout << "Krawedzie: " << tabKrawedzie[k] << ", " << tabKrawedzie[k + 1] << "; Waga: " << tabWagi[i] << endl;
        k = k + 2;
    }

    // Wyświetlanie macierzy sąsiedztwa
    cout << "Macierz sasiedztwa dla danych z pliku graf.txt:" << endl;
    cout << setw(3) << " ";
    for (int i = 0; i < n; ++i)
    {
        cout << setw(3) << (i + 1);
    }
    cout << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << setw(3) << (i + 1);
        for (int j = 0; j < n; ++j)
        {
            cout << setw(3) << tab[i][j];
        }
        cout << endl;
    }

    //sortowanie ze wzgledu na wagi
    for (int i = 0; i < m; ++i)
    {
        for (int z = 0; z < m - i - 1; ++z)
        {
            if (tabWagi[z] > tabWagi[z + 1])
            {
                // Zamień wagi
                swap(tabWagi[z], tabWagi[z + 1]);

                // Zamień odpowiadające pary wierzchołków
                swap(tabKrawedzie[2 * z], tabKrawedzie[2 * z + 2]);
                swap(tabKrawedzie[2 * z + 1], tabKrawedzie[2 * z + 3]);
            }
        }
    }

    //wyswietlanie listy krawedzi z wagami (wagi git, krawedzie nie)
    cout << "Po sortowaniu wagami: " << endl;
    for (int i = 0; i < m; ++i)
    {
        cout << "Krawedzie: " << tabKrawedzie[2 * i] << ", " << tabKrawedzie[2 * i + 1] << "; Waga: " << tabWagi[i] << endl;
    }
    
    // Zwolnienie pamięci
    for (int i = 0; i < n; ++i)
    {
        delete[] tab[i];
    }
    delete[] tab;
    delete[] tabWagi;
    delete[] tabKrawedzie;

    odczyt.close();
}