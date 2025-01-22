#include "header.h"

int main()
{
    fstream odczyt;
    odczyt.open("graf.txt", ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }

    int n, m;
    odczyt >> n >> m; // odczytujemy liczbę wierzchołków i krawędzi
    odczyt.close();
    int** macierz = new int*[n];
    for (int i = 0; i < n; ++i)
    {
        macierz[i] = new int[n];
    }
    cout<<"Macierz sasiedztwa:"<<endl;
    macierz = macierzSasiedztwa("graf.txt");
    cout<<"Lista sasiedztwa:"<<endl;
    listaSasiedstwa("grafLista.txt");
    cout<<"Lista krawedzi:"<<endl;
    listaKrawedzi("grafLista.txt");
    cout<<"Zamiana listy sasiedztwa na liste krawedzi:"<<endl;
    zamianaNaLE("grafLista.txt");
    cout<<"Zamiana listy krawedzi na liste sasiedztwa:"<<endl;
    zamianaNaLN("grafLista.txt");
    cout<<"Zamiana macierzy sasiedztwa na liste krawedzi:"<<endl;
    zamianaNaLEzMacierzy("grafLista.txt", macierz);
    //Kruskal();

    for (int i = 0; i < n; ++i)
    {
        delete[] macierz[i];
    }
    delete[] macierz;
    return 0;
}