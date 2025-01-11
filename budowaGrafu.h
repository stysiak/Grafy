#pragma once
#include "header.h"
using namespace std;

//macierz sąsiedztwa
void macierzSasiedztwa()
{
    fstream odczyt;
    odczyt.open("graf.txt", ios::in);
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

//lista sasiedztwa
struct list{
    int wierzcholek;
    int waga;
    list* nastepny;
};

list* stworzWezel(int wierzcholek, int waga, list* nastepny)
{
    list* nowyWezel = new list;
    nowyWezel->wierzcholek=wierzcholek;
    nowyWezel->waga=waga;
    nowyWezel->nastepny=nastepny;
    return nowyWezel;
}

void listaSasiedstwa()
{
    fstream odczyt;
    odczyt.open("grafLista.txt", ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }
    int n,m;
    odczyt >> n>>m;
    list* lista[n+1] = {nullptr};
    //tworzenie listy
    int u, v, w;
    for(int i=0; i<m; i++)
    {
        odczyt>>u>>v>>w;
        lista[u]=stworzWezel(v,w, lista[u]);
        lista[v]=stworzWezel(u,w,lista[v]);
    } 
    odczyt.close();                
    //wyświetlanie listy
    for(int i=1;i<=n;i++)
    {
        cout<<i<<" -> ";
        list* temp = lista[i];
        while(temp)
        {
            cout<<temp->wierzcholek<<"("<<temp->waga<<") -> ";
            temp=temp->nastepny;
        }
        cout<<"NULL"<<endl;
    }
    for(int i=1;i<=n;i++)
    {
        list* temp=lista[i];
        while(temp)
        {
            list* doUsuniecia=temp;
            temp=temp->nastepny;
            delete doUsuniecia;
        }
    }
}

//lista krawędzi
struct listK{
    int u;
    int v;
    int waga;
    listK* nastepny;
};

void listaKrawedzi()
{
    fstream odczyt;
    odczyt.open("grafLista.txt", ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }
    int n,m;
    odczyt >> n>>m;
    int u, v, w;
    listK* edgeList = nullptr;
    for(int i=0; i<m; i++)
    {
        odczyt>>u>>v>>w;
        listK* nowaKrawedz = new listK{u, v, w, edgeList};
        edgeList=nowaKrawedz;
    }
    odczyt.close();
    listK* temp = edgeList;
    while(temp)
    {
        cout<<temp->u<<"--("<<temp->waga<<")-->"<<temp->v<<endl;
        temp=temp->nastepny;
    }
    while(edgeList)
    {
        listK* temp=edgeList;
        edgeList=edgeList->nastepny;
        delete temp;
    }
}


