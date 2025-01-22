#pragma once
#include "header.h"
using namespace std;

//macierz sąsiedztwa
int** macierzSasiedztwa(string plik)
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

    //Zwolnienie pamięci
    // for (int i = 0; i < n; ++i)
    // {
    //     delete[] tab[i];
    // }
    // delete[] tab;
    delete[] tabWagi;
    delete[] tabKrawedzie;

    odczyt.close();
    return tab;
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

list** listaSasiedstwa(string plik)
{
    fstream odczyt;
    odczyt.open(plik, ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }
    int n,m;
    odczyt >> n>>m;
    list** lista = new list*[n+1];
    for (int i = 0; i <= n; i++) 
    {
        lista[i] = nullptr;
    }
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
    // for(int i=1;i<=n;i++)
    // {
    //     cout<<i<<" -> ";
    //     list* temp = lista[i];
    //     while(temp)
    //     {
    //         cout<<temp->wierzcholek<<"("<<temp->waga<<") -> ";
    //         temp=temp->nastepny;
    //     }
    //     cout<<"NULL"<<endl;
    // }
    // for(int i=1;i<=n;i++)
    // {
    //     list* temp=lista[i];
    //     while(temp)
    //     {
    //         list* doUsuniecia=temp;
    //         temp=temp->nastepny;
    //         delete doUsuniecia;
    //     }
    // }
    return lista;
}

//lista krawędzi
struct listK{
    int u;
    int v;
    int waga;
    listK* nastepny;
};

listK* listaKrawedzi(string plik)
{
    fstream odczyt;
    odczyt.open(plik, ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }
    int n,m;
    odczyt >> n>>m;
    int u, v, w;
    listK* edgeList = new listK;
    edgeList = nullptr;
    for(int i=0; i<m; i++)
    {
        odczyt>>u>>v>>w;
        listK* nowaKrawedz = new listK{u, v, w, edgeList};
        edgeList=nowaKrawedz;
    }
    odczyt.close();
    // listK* temp = edgeList;
    // while(temp)
    // {
    //     cout<<temp->u<<"--("<<temp->waga<<")-->"<<temp->v<<endl;
    //     temp=temp->nastepny;
    // }
    // while(edgeList)
    // {
    //     listK* temp=edgeList;
    //     edgeList=edgeList->nastepny;
    //     delete temp;
    // }
    return edgeList;
}

//wygenerowac liste krawedzi w oparciu o liste sasiedztwa
listK* zamianaNaLE(string plik)
{
    fstream odczyt;
    odczyt.open(plik, ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }
    int n;
    odczyt >> n;
    odczyt.close();
    listK* edgeList = nullptr;
    bool** odwiedzone = new bool*[n+1];
    for(int i=0;i<=n;i++)
    {
        odwiedzone[i]=new bool[n+1]{false};
    }
    list** listaS = listaSasiedstwa(plik);
    for(int i=1; i<=n; i++)
    {
        list* temp = listaS[i];
        while(temp)
        {
            int u = i;
            int v = temp->wierzcholek;
            int waga = temp->waga;
            if(odwiedzone[u][v]==false)
            {
                listK* nowaKrawedz = new listK{u, v, waga, edgeList};
                edgeList=nowaKrawedz;
                odwiedzone[u][v]=odwiedzone[v][u]=true;
            }
            temp=temp->nastepny;
        }
    }

    listK* temp = edgeList;
    while(temp)
    {
        cout<<temp->u<<"--("<<temp->waga<<")-->"<<temp->v<<endl;
        temp=temp->nastepny;
    }

    for (int i = 0; i <= n; i++) 
    {
        delete[] odwiedzone[i];
    }
    delete[] odwiedzone;
    
    return edgeList;
}

//wygenerowac liste sasiedztwa w oparciu o liste krawedzi
list** zamianaNaLN(string plik)
{
    fstream odczyt;
    odczyt.open(plik, ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }
    int n;
    odczyt >> n;
    odczyt.close();
    list** listS = new list*[n+1];
    for (int i = 0; i <= n; i++) 
    {
        listS[i] = nullptr;
    }
    listK* listLE = listaKrawedzi(plik);
    listK* temp = listLE;
    while(temp)
    {
        int u = temp->u;
        int v = temp->v;
        int waga = temp->waga;
        listS[u]=stworzWezel(v,waga, listS[u]);
        listS[v]=stworzWezel(u,waga,listS[v]);
        temp = temp->nastepny;
    }
    for(int i=1;i<=n;i++)
    {
        cout<<i<<" -> ";
        list* temp = listS[i];
        while(temp)
        {
            cout<<temp->wierzcholek<<"("<<temp->waga<<") -> ";
            temp=temp->nastepny;
        }
        cout<<"NULL"<<endl;
    }
    return listS;
}

//wygenerowac liste krawedzi w oparciu o macierz sasiedzwta
listK* zamianaNaLEzMacierzy(string plik, int** macierz)
{
    fstream odczyt;
    odczyt.open(plik, ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }
    int n;
    odczyt >> n;
    odczyt.close();
    listK* edgeList = nullptr;
    for(int i=0; i<n;i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(macierz[i][j]!=0)
            {
                listK* nowaKrawedz = new listK{i+1, j+1, macierz[i][j], edgeList};
                edgeList=nowaKrawedz;
            }
        }
    }
    listK* temp = edgeList;
    while(temp)
    {
        cout<<temp->u<<"--("<<temp->waga<<")-->"<<temp->v<<endl;
        temp=temp->nastepny;
    }
    return edgeList;
}

