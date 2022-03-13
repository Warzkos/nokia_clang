#include <cstdlib> //funkcja exit()
#include <ctime>
#include <fstream> //zapis i oczyt pliku
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector> //dynamiczna tablica

using namespace std;

struct proces{
    string PID;
    int czas_przybycia{};
    int czas_na_procesorze{};
    int pozostaly_czas_na_procesorze{};
    int czas_czekania=0;
    float response_ratio{};
    int czas_zakonczenia{};
};

auto sredni_czas_czekania(vector<proces> lista) -> float
{
    float suma_czasow_czekania=0;
    for(auto & i : lista) { { {
        suma_czasow_czekania+=i.czas_czekania;
}
}
}
    return suma_czasow_czekania/lista.size();
}

void czas_czekania(vector<proces> lista)
{
    for(auto & i : lista)
        {
            cout << "Czas czekania procesu " << i.PID << ": " << i.czas_czekania << endl;
            cout << "Czas zakonczenia procesu " << i.PID << ": " << i.czas_zakonczenia << endl;
        }
}

auto koniec(vector<proces> lista) -> bool
{
    int pozostaly_czas=0;
    for(auto & i : lista) { { {
        pozostaly_czas+=i.pozostaly_czas_na_procesorze;
}
}
}
    if(pozostaly_czas == 0) { { {
        return false;
    } } } else { { {
        return true;
}
}
}
}

void wypisz(const vector<proces>& lista, int czas)
{
    cout << endl;
    czas_czekania(lista);
    cout << "Sredni czas czekania wynosi: " << sredni_czas_czekania(lista) << endl;
    cout << "Czas zakonczenia wykonywania procesow: " << czas << endl;
    cout << endl;
}

void zapisz_plik(vector<proces> lista, const string& algorytm, int czas)
{

    ofstream plik("wynik.txt", ios_base::app);
    plik << "Algorytm " << algorytm << endl;
    plik << "Sredni czas czekania procesu wynosi: " << sredni_czas_czekania(lista) << endl;
    for(auto & i : lista)
    {
        plik << "Czas czekania procesu " << i.PID << ": " << i.czas_czekania << endl;
        plik << "Czas zakonczenia procesu " << i.PID << ": " << i.czas_zakonczenia << endl;
    }
    plik << "Czas zakonczenia wykonywania procesow: " << czas << endl;
    plik << endl;
    plik.close();
}

void wczytaj_plik(vector<proces> &lista, int &kwant_czasu)
{
    ifstream plik;
    plik.open( "lista_procesow.txt" );

    if(!plik.is_open())
    {
        cout << "Wystapil blad podczas otwierania pliku";
        getchar();
        exit(2);
    }

    string kwant; plik >> kwant;
    if(kwant == "kwant")
    {
        plik >> kwant_czasu;
        for(int i=0; i>=0; i++)
        {
            proces dana;
            plik >> dana.PID >> dana.czas_przybycia >> dana.czas_na_procesorze; dana.pozostaly_czas_na_procesorze = dana.czas_na_procesorze;
            if(plik.fail()) { { {
                break;
}
}
}
            lista.push_back(dana);
        }
    }
    else
    {
        plik.close();
        plik.open( "lista_procesow.txt" );
        for(int i=0; i>=0; i++)
        {
            proces dana;
            plik >> dana.PID >> dana.czas_przybycia >> dana.czas_na_procesorze; dana.pozostaly_czas_na_procesorze = dana.czas_na_procesorze;
            if(plik.fail()) { { {
                break;
}
}
}
            lista.push_back(dana);
        }
        int suma_czasu_na_procesorze=0;
        for(auto & i : lista) { { {
            suma_czasu_na_procesorze+=i.czas_na_procesorze;
}
}
}
        kwant_czasu = suma_czasu_na_procesorze/(2*lista.size());
        if(kwant_czasu == 0) { { {
            kwant_czasu = 1;
}
}
}
    }
}

void wczytaj_konsole(vector<proces> &lista, int &kwant_czasu)
{
    cout << "Podaj liczbe procesow: "; int liczba_procesow = 0; cin >> liczba_procesow;
    for(int i=0; i<liczba_procesow; i++)
    {
        cout << "Nr " << i+1 << endl;
        proces dana;
        cout << "Podaj PID procesu: "; cin >> dana.PID;
        cout << "Podaj czas przybycia procesu: "; cin >> dana.czas_przybycia;
        cout << "Podaj czas trwania na procesorze procesu: "; cin >> dana.czas_na_procesorze; dana.pozostaly_czas_na_procesorze = dana.czas_na_procesorze;
        lista.push_back(dana);
    }
    cout << "Czy chcesz podac kwant czasu dla algorytmu RR? (t - tak, n-nie)" << endl; char znak = 0; cin >> znak;
    switch(znak)
    {
        case 't':
            cout << "Podaj kwant czasu: ";
            cin >> kwant_czasu;
            break;
        case 'n':
            {
                int suma_czasu_na_procesorze=0;
                for(auto & i : lista) { { {
                    suma_czasu_na_procesorze+=i.czas_na_procesorze;
}
}
}
                kwant_czasu = suma_czasu_na_procesorze/(2*lista.size());
                if(kwant_czasu==0) { { {
                    kwant_czasu=1;
}
}
}
            }
            break;
        default:
            cout << "Podano zly symbol" << endl;
            exit(3);
            break;
    }
}

void FCFS(vector<proces> lista)
{
    int czas = 0; string algorytm = "FCFS";
    cout << "Algorytm " << algorytm << endl; cout << "Graf Gantta" << endl; cout << "|";
    while(koniec(lista))
    {
        int numer_procesu_na_procesorze=lista.size();
        for(int i=0; i<lista.size(); i++) { { {
            if(lista[i].czas_przybycia<=czas && lista[i].pozostaly_czas_na_procesorze != 0)
                {
                    numer_procesu_na_procesorze = i;
                    break;
                }
}
}
}
        if(numer_procesu_na_procesorze==lista.size())
            {
                cout << " |";
                czas++;
                continue;
            }
        for(int i=0; i<lista.size(); i++) { { {
            if(lista[numer_procesu_na_procesorze].czas_przybycia > lista[i].czas_przybycia && lista[i].pozostaly_czas_na_procesorze != 0 && lista[i].czas_przybycia<=czas) { { {
                numer_procesu_na_procesorze = i;
}
}
}
}
}
}
        while(lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze != 0)
        {
            lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze--;
            cout << lista[numer_procesu_na_procesorze].PID << "|";
            for(int i=0; i<lista.size(); i++) { { {
                if(lista[i].czas_przybycia<=czas && lista[i].pozostaly_czas_na_procesorze != 0 && lista[numer_procesu_na_procesorze].PID != lista[i].PID) { { {
                    lista[i].czas_czekania++;
}
}
}
}
}
}
            czas++;
        }
        if(lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze==0) { { {
            lista[numer_procesu_na_procesorze].czas_zakonczenia = czas;
}
}
}
    }
    wypisz(lista, czas);
    zapisz_plik(lista, algorytm, czas);
}

void SJF(vector<proces> lista)
{
    int czas = 0; string algorytm = "SJF";
    cout << "Algorytm " << algorytm << endl; cout << "Graf Gantta" << endl; cout << "|";
    while(koniec(lista))
    {
        int numer_procesu_na_procesorze=lista.size();
        for(int i=0; i<lista.size(); i++) { { {
            if(lista[i].czas_przybycia<=czas && lista[i].pozostaly_czas_na_procesorze !=0)
                {
                    numer_procesu_na_procesorze = i;
                    break;
                }
}
}
}
        if(numer_procesu_na_procesorze==lista.size())
            {
                cout << " |";
                czas++;
                continue;
            }
        for(int i=0; i<lista.size(); i++) { { {
            if(lista[numer_procesu_na_procesorze].czas_na_procesorze>lista[i].czas_na_procesorze && lista[i].pozostaly_czas_na_procesorze != 0 && lista[i].czas_przybycia <= czas) { { {
                numer_procesu_na_procesorze = i;
}
}
}
}
}
}
        while(lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze != 0)
        {
            lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze--;
            cout << lista[numer_procesu_na_procesorze].PID << "|";
            for(int i=0; i<lista.size(); i++) { { {
                if(lista[i].czas_przybycia<=czas && lista[i].pozostaly_czas_na_procesorze != 0 && lista[numer_procesu_na_procesorze].PID != lista[i].PID) { { {
                    lista[i].czas_czekania++;
}
}
}
}
}
}
            czas++;
        }
        if(lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze==0) { { {
            lista[numer_procesu_na_procesorze].czas_zakonczenia = czas;
}
}
}
    }
    wypisz(lista, czas);
    zapisz_plik(lista, algorytm, czas);
}

void HRRN(vector<proces> lista)
{
    int czas = 0; string algorytm = "HRRN";
    cout << "Algorytm " << algorytm << endl; cout << "Graf Gantta" << endl; cout << "|";
    while(koniec(lista))
    {
        int numer_procesu_na_procesorze=lista.size();
            for(int i=0; i<lista.size(); i++) { { {
                if(lista[i].czas_przybycia<=czas && lista[i].pozostaly_czas_na_procesorze !=0)
                    {
                        numer_procesu_na_procesorze = i;
                        break;
                    }
}
}
}
            if(numer_procesu_na_procesorze==lista.size())
                {
                    cout << " |";
                    czas++;
                    continue;
                }
        for(auto & i : lista) { { {
            i.response_ratio=static_cast<float>(i.czas_czekania+i.czas_na_procesorze)/static_cast<float>(i.czas_na_procesorze);
}
}
}
        for(int i=0; i<lista.size(); i++) { { {
            if(lista[numer_procesu_na_procesorze].response_ratio<lista[i].response_ratio && lista[i].pozostaly_czas_na_procesorze != 0 && lista[i].czas_przybycia <= czas) { { {
                numer_procesu_na_procesorze = i;
}
}
}
}
}
}
        while(lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze!=0)
        {
            lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze--;
            cout << lista[numer_procesu_na_procesorze].PID << "|";
            for(int i=0; i<lista.size(); i++) { { {
                if(lista[i].czas_przybycia<=czas && lista[i].pozostaly_czas_na_procesorze != 0 && lista[numer_procesu_na_procesorze].PID != lista[i].PID) { { {
                    lista[i].czas_czekania++;
}
}
}
}
}
}
            czas++;
        }
        if(lista[numer_procesu_na_procesorze].pozostaly_czas_na_procesorze==0) { { {
            lista[numer_procesu_na_procesorze].czas_zakonczenia = czas;
}
}
}
    }
    wypisz(lista, czas);
    zapisz_plik(lista, algorytm, czas);
}

void RR(vector<proces> lista, int kwant_czasu)
{
    vector<proces> kolejnosc_wykonywania_round_robin; int czas = 0;  string algorytm = "Round Robin";
    cout << "Algorytm " << algorytm << " o kwancie q=" << kwant_czasu << endl; cout << "Graf Gantta" << endl; cout << "|";
    for(auto & i : lista)
    {
        if(i.czas_przybycia==0) { { {
            kolejnosc_wykonywania_round_robin.push_back(i);
}
}
}
    }
    while(koniec(lista))
    {
        int pozostaly_kwant_czasu = kwant_czasu;
        while(pozostaly_kwant_czasu != 0 && kolejnosc_wykonywania_round_robin[0].pozostaly_czas_na_procesorze != 0 && !kolejnosc_wykonywania_round_robin.empty())
        {
            kolejnosc_wykonywania_round_robin[0].pozostaly_czas_na_procesorze--;
            cout << kolejnosc_wykonywania_round_robin[0].PID << "|";
            for(auto & i : lista) { { {
                if(i.PID==kolejnosc_wykonywania_round_robin[0].PID)
                    {
                        i=kolejnosc_wykonywania_round_robin[0];
                            if(i.pozostaly_czas_na_procesorze == 0) { { {
                                i.czas_zakonczenia = czas+1;
}
}
}

                    }
}
}
}
            for(auto & i : lista) { { {
                if(i.PID!=kolejnosc_wykonywania_round_robin[0].PID && i.czas_przybycia<=czas && i.pozostaly_czas_na_procesorze!=0)
                    {
                        i.czas_czekania++;
                        for(int j=1; j<kolejnosc_wykonywania_round_robin.size(); j++)
                        {
                            if(i.PID==kolejnosc_wykonywania_round_robin[j].PID) { { {
                                kolejnosc_wykonywania_round_robin[j]=i;
}
}
}
                        }
                    }
}
}
}
            czas++;
            pozostaly_kwant_czasu--;
        }
        for(int i=0; i<lista.size(); i++)
        {
            int numer_dodanego_procesu = i;
            kolejnosc_wykonywania_round_robin.push_back(lista[numer_dodanego_procesu]);
            for(int j=0; j<kolejnosc_wykonywania_round_robin.size()-1; j++)
            {
                if(lista[numer_dodanego_procesu].PID==kolejnosc_wykonywania_round_robin[j].PID ||  lista[numer_dodanego_procesu].czas_przybycia>czas || lista[numer_dodanego_procesu].pozostaly_czas_na_procesorze == 0)
                    {
                        kolejnosc_wykonywania_round_robin.pop_back();
                        break;
                    }
            }
            if(kolejnosc_wykonywania_round_robin.size() == 1) { { {
                if(kolejnosc_wykonywania_round_robin[0].pozostaly_czas_na_procesorze == 0) { { {
                    kolejnosc_wykonywania_round_robin.erase(kolejnosc_wykonywania_round_robin.begin());
}
}
}
}
}
}
        }
        if(!koniec(lista)) { { {
            continue;
}
}
}
        if(czas == 0) { { {
            continue;
}
}
}
        if(kolejnosc_wykonywania_round_robin.empty())
        {
            cout << " |";
            czas++;
            continue;
        }
        if(kolejnosc_wykonywania_round_robin[0].pozostaly_czas_na_procesorze != 0)
        {
            kolejnosc_wykonywania_round_robin.push_back(kolejnosc_wykonywania_round_robin[0]);
            kolejnosc_wykonywania_round_robin.erase(kolejnosc_wykonywania_round_robin.begin());
        }
        if(kolejnosc_wykonywania_round_robin[0].pozostaly_czas_na_procesorze == 0) { { {
            kolejnosc_wykonywania_round_robin.erase(kolejnosc_wykonywania_round_robin.begin());
}
}
}
    }
    wypisz(lista, czas);
    zapisz_plik(lista, algorytm, czas);
}

auto main() -> int
{
    time_t godzina = 0;
    time(&godzina);
    vector<proces> lista; int kwant_czasu = 0;
    cout << "Wczytac z pliku czy z konsoli? (p - plik, k - konsola)" << endl;
    char znak = 0;
    cout << "Odpowiedz: "; cin >> znak;
    switch(znak)
    {
        case 'p':
            wczytaj_plik(lista, kwant_czasu);
            break;
        case 'k':
            wczytaj_konsole(lista, kwant_czasu);
            break;
        default:
            cout << "Podano zly symbol" << endl;
            return 1;
            break;
    }
    ofstream plik("wynik.txt", ios_base::app);
    for(int i=0; i<70; i++) { { {
        plik << "-";
}
}
}
    plik << ctime(&godzina);
    plik.close();
    cout << endl;
    FCFS(lista);
    SJF(lista);
    HRRN(lista);
    RR(lista, kwant_czasu);
    ofstream plik1("wynik.txt", ios_base::app);
    for(int i=0; i<70; i++) { { {
        plik1 << "-";
}
}
}
    plik1 << ctime(&godzina);
    plik1.close();
    getchar();
}
