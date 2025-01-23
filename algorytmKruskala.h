#pragma once
#include "header.h"

void sortujListe(listK*& head) {
    if (!head || !head->nastepny) 
    {
        return; //jesli lista pusta lub ma jeden element, nie sortuj
    }
    
    bool zamieniono;
    do 
    {
        zamieniono = false;
        listK* current = head;
        listK* prev = nullptr;
        listK* next = nullptr;

        while (current->nastepny) 
        {
            next = current->nastepny;

            //sprawdzenie, czy nalezy zamienic krawedzie
            if (current->waga > next->waga) 
            {
                zamieniono = true;

                //zamiana miejscami
                if (prev) {
                    prev->nastepny = next;
                } else {
                    head = next; //zmiana poczztku listy
                }
                current->nastepny = next->nastepny;
                next->nastepny = current;

                //zktualizacja wskaznikow
                prev = next;
            } else 
            {
                //przejscie do następnej pary
                prev = current;
                current = current->nastepny;
            }
        }
    } while (zamieniono);
}

void Kruskal(string plik)
{
    fstream odczyt;
    odczyt.open(plik, ios::in);
    if (!odczyt.good())
    {
        cout << "Blad odczytu pliku" << endl;
        exit(1);
    }

    int n, m;
    odczyt >> n >> m; // odczytujemy liczbę wierzchołków i krawędzi
    odczyt.close();
    listK* listLE = listaKrawedzi(plik);

    //sortowanie listy ze wzgledu na wagi
    sortujListe(listLE);
    cout << "Posortowana lista krawedzi:" << endl;
    listK* temp = listLE;
    while (temp) {
        cout << temp->u << " --(" << temp->waga << ")--> " << temp->v << endl;
        temp = temp->nastepny;
    }
    int* kolor = new int[n+1]{0}; //0-> biały, >0 -> numer lasu;
    int aktualnyLas = 0;
    listK* listaLEKruskal = nullptr;
    int calkowityKoszt = 0; //calkowity koszt trasy po minimalnym drzwie rozpinajacym
    
    listK* temp2 = listLE;
    while(temp2)
    {
        int u = temp2->u;
        int v = temp2->v;
        int waga = temp2->waga;
        if(kolor[u]==0 && kolor[v]==0) //jesli oba wierzcholki biale
        {
            aktualnyLas++;
            kolor[u] = kolor[v] = aktualnyLas; //tworzymy nowy las
            listaLEKruskal = new listK{u, v, waga, listaLEKruskal};
            calkowityKoszt += waga;
        }
        else if(kolor[u]==0 || kolor[v]==0) //jesli jeden bialy - jeden w istniejacym lesie
        {
            int las = max(kolor[u], kolor[v]); //przypisanie aktualnego lasu
            kolor[u]=kolor[v] = las;
            listaLEKruskal = new listK{u, v, waga, listaLEKruskal};
            calkowityKoszt += waga;
        }
        else if(kolor[u]!=kolor[v]) //jesli dwa rozne lasy
        {
            int lasDoZmiany = kolor[v];
            int lasDocelowy = kolor[u];
            for(int i=1; i<=n; i++)
            {
                if(kolor[i]==lasDoZmiany)
                {
                    kolor[i]=lasDocelowy; //laczenie lasow
                }
            }
            listaLEKruskal = new listK{u, v, waga, listaLEKruskal};
            calkowityKoszt += waga;
        }
        //jesli oba wierzcholki sa w tym samym lesie, to ignorujemy krawedz
        temp2 = temp2->nastepny;
    }
    cout<<"Minimalne drzewo rozpinajace: "<<endl;
    temp2 = listaLEKruskal;
    while(temp2)
    {
        cout << temp2->u << " --(" << temp2->waga << ")--> " << temp2->v << endl;
        temp2 = temp2->nastepny;
    }
    cout<<"Calkowity koszt minimalnego drzewa rozpinajacego: "<<calkowityKoszt<<endl;
    while(listaLEKruskal)
    {
        temp = listaLEKruskal;
        listaLEKruskal = listaLEKruskal->nastepny;
        delete temp;
    }
    while(listLE)
    {
        temp = listLE;
        listLE = listLE->nastepny;
        delete temp;
    }
}