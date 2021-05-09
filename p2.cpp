#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cstdlib>

using namespace std;

struct lista_s  // struktura reprezentujaca pojedyncza liste sasiedztwa dla jednego wierzcholka
{
    int v,w;    // w - waga, v - sasiedni
    lista_s* nastepny;
};







void wypisz_do_pliku (int wierzcholki, int il_krawedz, fstream& strumien) // funkcja wypisujaca dane do pliku
{
    int liczba_poz_wyk = il_krawedz - wierzcholki + 1;  // liczba wykonan pozostalych po stworzeniu sciezki laczacej wszystkie wierzcholki grafu
    int tmp;
    int numer_wierzcholka = wierzcholki;
    int licznik = 0;

    strumien.open("dane.txt", ios_base::app);           ///otwieramy strumien danych zapisu do pliku

    strumien << wierzcholki<<" "<<il_krawedz<<" "<<rand()%wierzcholki<<endl;  //zapisujemy ilosc wierzcholkow, krawedzi i wierzcholek startowy (wierzcholek startowy oraz wagi krawedzi sa pseudolosowe)
    for(int i = 0; i < wierzcholki - 1 && i < il_krawedz -1 ; i++)            //zapisujemy glowny cykl laczacy wszystkie wierzcholki
    {
        strumien << i<< " "<<i+1<<" "<<rand()%100+1<<endl;
    }

    while(licznik < liczba_poz_wyk) //zapisujemy pozostale krawdzie w zaleznosci od wypelnienia
    {
        tmp = 0;

        while(licznik < liczba_poz_wyk && tmp < numer_wierzcholka - 2)
        {
            strumien << numer_wierzcholka - 1<<" "<< tmp <<" "<<rand()%10+1<<endl;

            licznik++;
            tmp++;
        }
        numer_wierzcholka--;
    }
    strumien.close(); //zamykamy strumien 
}






void generuj_dane(fstream& strumien)                // funkcja generujaca dane
{
    int wierzcholki[5] = {10, 50, 100, 500, 1000};  // tablica z ilosciami wierzcholkow
    int max_krawedzi[5];                            // tablica maksymalnych liczb krawedzi
    int krawedzie[5][4];                            // tablica liczb krawedzi dla roznych przypakow
    int wypelnienie[4] = {25, 50, 75, 100};         // tablica z procentowymi wypelnieniami

    strumien.open("dane.txt", ios_base::out);       // otwieramy strumien do zapisu danych do pliku dane.txt
    strumien.close();                               // zamykamy strumien, to czysci nam plik z poprzednich danych

    for (int i = 0; i < 5; i++)                     // generujemy nasze przypadki i dla kazdego z nich wypisujemy grafy do pliku
    {
        max_krawedzi [i] = wierzcholki[i] * (wierzcholki[i] - 1) /2;
        for (int j = 0; j < 4; j++)
        {
            krawedzie[i][j] = wypelnienie[j] * max_krawedzi[i] /100;
            for(int k = 0; k < 100; k++)
            {
                wypisz_do_pliku (wierzcholki[i], krawedzie[i][j], strumien);
            }
        }
    }
}






void wyswietl_sciezke(int* poprzednik, int* koszt_dojscia, int wierzch)
{
    int* wyswietlanie = new int [wierzch];  // rezerwujemy pamiec dla tablicy dynamicznej do wyswietlania sciezki

    int k = 0;
    int j;

    for(int i = 0; i < wierzch; i++)    // wyswietlamy dojscie do kazdego z wierzcholkow oraz koszt dojscia
    {
        cout << i <<": ";
        for(j = i; j != -1 && k < wierzch; j = poprzednik[j])wyswietlanie [k++] = j;

        while(k)cout << wyswietlanie[--k] << " ";

        cout << "$" << koszt_dojscia[i] << endl;
    }
    delete [] wyswietlanie;             // usuwamy tablice
}






void BF_lista(int wierzch, int kraw, int start, lista_s** tab_list)
{
    lista_s* sasiedzi;

    int max_int =2147483647;            // maksymalna wartosc int w 32bit -> 64bit 9223372036854775807

    int* koszt_dojscia;                 // wskaznik na tablice dynamiczna kosztow dojscia
    koszt_dojscia = new int [wierzch];

    int* poprzednik;                    // wskaznik na tablice dynamiczna poprzednikow
    poprzednik = new int [wierzch];

    for(int i = 0; i < wierzch; i++)
    {
        poprzednik[i] = -1;             // przypisujemy wartosci tablicy poprzednikow -1 nie ma wierzcholka ujmenego
        koszt_dojscia[i] = max_int;     // koszty dojscia ustawiamy na nieskonczonosc, tutaj na maksymalna wartosc inta
    }

    koszt_dojscia[start] = 0;           // zerujemy koszt dojscia do naszego wierzcholka startowego

    for(int i = 1; i < wierzch; i++)
    {
        for(int j = 0; j < wierzch; j++)    // przeszukujemy liste sasiedztwa w poszukiwaniu krawedzi dla danego wierzcholka relaksujac kolejne krawedzie
        {
            for(sasiedzi = tab_list[j]; sasiedzi; sasiedzi = sasiedzi -> nastepny)
            {
                if(koszt_dojscia[j] != max_int && koszt_dojscia[sasiedzi -> v] > koszt_dojscia[j] + sasiedzi -> w)
                {
                    koszt_dojscia[sasiedzi -> v] = koszt_dojscia [j] + sasiedzi -> w;
                    poprzednik[sasiedzi -> v] = j;
                }
            }
        }
    }
    //wyswietl_sciezke(poprzednik, koszt_dojscia, wierzch);    // wyswietlenie drog oraz kosztow dojscia
}






void BF_macierz(int** graf_m, int wierzch, int kraw, int start)
{
    int max_int =2147483647;            // maksymalna wartosc int w 32bit -> 64bit 9223372036854775807

    int* koszt_dojscia;                 // wskaznik na tablice dynamiczna kosztow dojscia
    koszt_dojscia = new int [wierzch];

    int* poprzednik;                    // wskaznik na tablice dynamiczna poprzednikow
    poprzednik = new int [wierzch];

    for(int i = 0; i < wierzch; i++)
    {
        poprzednik[i] = -1;             // przypisujemy wartosci tablicy poprzednikow -1 nie ma wierzcholka ujmenego
        koszt_dojscia[i] = max_int;     // koszty dojscia ustawiamy na nieskonczonosc, tutaj na maksymalna wartosc zmiennej typu int
    }

    koszt_dojscia[start] = 0;           // zerujemy koszt dojscia do naszego wierzcholka startowego

    for(int i = 1; i < wierzch; i++)
    {
        for(int j = 0; j < wierzch; j++)
        {
            for(int k = 0; k < wierzch; k++)    // przeszukujemy macierz sasiedztwa w poszukiwaniu krawedzi dla danego wierzcholka relaksujac kolejne krawedzie
            {
                if(koszt_dojscia[j] != max_int && graf_m[k][j] != 0 && koszt_dojscia[k] > koszt_dojscia[j] + graf_m[k][j])
                {
                    koszt_dojscia[k] = koszt_dojscia [j] +  graf_m[k][j];
                    poprzednik[k] = j;
                }
            }
        }
    }
    //wyswietl_sciezke(poprzednik, koszt_dojscia, wierzch);    //  wyswietlanie drog oraz kosztow dojscia
}






void wyswietl_lista(lista_s** tab_list, int wierzch)     // wyswietlania tablicy list
{
    lista_s* lista_w;
    cout<< "lista:\n";
    for(int i = 0; i < wierzch; i++)
      {
        cout << "tab[" << i << "] =";
        lista_w = tab_list[i];
        while(lista_w)
        {
          cout << lista_w->v <<" ";
          lista_w = lista_w->nastepny;
        }
        cout << endl;
    }
    delete [] lista_w;       // usuwamy liste
}




void graf_lista(int& wierzch, int& kraw, int& start, int** graf, lista_s** tab_list, lista_s* lista)
{
    int v1, v2, waga;

    for(int i = 0; i < wierzch; i++)   // wypelniamy tablice list NULL'ami
    {
        tab_list[i] = NULL;

    }

    for(int i = 0; i < kraw; i++)   // tworzymy listy dla grafu skierowanego
    {
        v1 = graf[i][0];            // wczytujemy dane z pliku
        v2 = graf[i][1];
        waga = graf[i][2];

        lista = new lista_s;

        lista->v = v2;
        lista->w = waga;
        lista->nastepny = tab_list[v1];
        tab_list[v1] = lista;

    }
    //wyswietl_lista(tab_list, wierzch);    // gdy chcemy wyswietlic liste sasiedztwa
}






void wyswietl_macierz(int** graf_m, int wierzch) // wyswietlanie macierzy sasiedztwa
{
    for(int i = 0; i < wierzch; i++)
    {
        for(int j = 0; j < wierzch; j++)
        {
            cout << graf_m[i][j] <<" ";
        }
        cout<<endl;
    }
}






void** graf_macierz(int& wierzch, int& kraw, int& start, int** graf, int** graf_m)
{
    int v1, v2, waga;
    int pom = 0;

    for (int i = 0; i < wierzch; ++i)    // zerowanie ilosci krawedzi
    {
        for(int j = pom; j < wierzch; ++j)
        {
            graf_m[i][j] = 0;
            graf_m[j][i] = 0;
        }
        pom++;
    }

    for (int i = 0; i < kraw; ++i)
    {
        v1 = graf[i][0];        // wczytujemy dane z reprezentacji grafu z pliku
        v2 = graf[i][1];
        waga = graf[i][2];

        graf_m[v1][v2] = waga;  // wpisujemy dane do macierzy sasiedztwa dla grafu nieskierowaniego
    }
    //wyswietl_macierz(graf_m, wierzch);    // gdy chcemy wyswietlic macierz sasiedztwa
}






void** wczytaj_graf(int** graf, int& wierzch, int& kraw, int& start, ifstream& wejscie)
{
    for(int x = 0; x < kraw;x++)    ///wczytujemy graf z pliku do tablicy dynamicznej dwuwymiarowej
    {
        wejscie >> graf[x][0];
        wejscie >> graf[x][1];
        wejscie >> graf[x][2];
    }
}






void znajdz_droge_lista(int** graf, int& wierzch, int& kraw, int& start, fstream& wyjscie)
{
    double czas_trwania;
    clock_t czas1, czas2;               // pomiar czasu

    lista_s** tab_list;
    lista_s* lista, *usuwanie;          // struktury dynamiczne odpowiadajace za liste sasiedztwa

    tab_list = new lista_s * [wierzch]; // alokujemy pamiec dla listy sasiedztwa

    graf_lista(wierzch, kraw, start, graf, tab_list, lista);    // funkcja odpowiedzialna za tworzenie listy sasiedztwa

    czas1 = clock();                            // czas start

    BF_lista(wierzch, kraw, start, tab_list);   // szukanie najkrotszej sciezki algorytmem Bellamana-Forda dla listy sasiedztwa

    czas2 = clock() - czas1;                    // czas stop


      for(int i = 0; i < wierzch; i++)          // usuwamy listy z tablicy list
      {
        lista = tab_list[i];
        while(lista)
        {
          usuwanie = lista;
          lista = lista->nastepny;
          delete usuwanie;
        }
      }
        delete [] tab_list;              //usuwamy tablice list

    czas_trwania = (double) (czas2) / CLOCKS_PER_SEC;

    wyjscie << "Czas szukania sciezki przy: "<<wierzch<<" i: "<<kraw*100/(wierzch * (wierzch - 1) /2)<<"% wypelnienia dla listy: "<<czas_trwania;
}






void znajdz_droge_macierz(int** graf, int& wierzch, int& kraw, int& start, fstream& wyjscie)
{
    double czas_trwania;
    clock_t czas1, czas2;             // pomiar czasu 

    int** graf_m;                     // tworzymy dynamiczna macierz sasiedztwa

    graf_m = new int *[wierzch];      // alokujemy pamiec dla macierzy sasiedztwa
    for(int v = 0; v < wierzch; ++v)
    {
        graf_m[v] = new int [wierzch];
    }

    graf_macierz(wierzch, kraw, start, graf, graf_m);   // funkcja odpowiedzialna za tworzenie macierzy sasiedztwa

    czas1 = clock();                          // czas start

    BF_macierz(graf_m, wierzch, kraw, start); // szukanie najkrotszej sciezki algorytmem Bellamana-Forda dla macierzy sasiedztwa

    czas2 = clock() - czas1;                  // czas stop

    for(int v = 0; v < wierzch; ++v)          // usuwamy macierz sasiedztwa
    {
        delete [] graf_m[v];
    }
    delete [] graf_m;

    czas_trwania = (double) (czas2) / CLOCKS_PER_SEC;

    wyjscie << " ,a dla macierzy: "<<czas_trwania<<endl;
}






void znajdz_droge(ifstream& wejscie)
{
    fstream wyjscie;
    int wierzch, kraw, start;
    int** graf;

    wyjscie.open("pomiar.txt", ios_base::app);  // otwieramy strumien wyjsciowy do pliku pomiar.txt, dopisywanie danych

    for(int i = 0; i < 2000; i++)
    {
        wejscie >> wierzch;        // wczytujemy kolejno: liczbe wierzcholkow, krawedzi i wierzcholek startowy
        wejscie >> kraw;
        wejscie >> start;

        graf = new int* [kraw];    // rezerwacja pamieci dla tablicy dynamicznej dwuwymiarowej (potrzebnej do grafu)

        for(int j = 0; j < kraw; j++)
        {
            graf[j] = new int [3];
        }

        wczytaj_graf(graf, wierzch, kraw, start, wejscie);     // wczytujemy graf z pliku i realizujemy zadanie dla macierzy i listy sąsiedztwa
        znajdz_droge_lista(graf, wierzch, kraw, start, wyjscie);
        znajdz_droge_macierz(graf, wierzch, kraw, start, wyjscie);

        for(int k = 0; k < kraw; ++k) // usuwamy tablice dynamiczna przechowujaca dane grafu z pliku
        {
            delete [] graf[k];
        }
        delete [] graf;
    }
    wyjscie.close();    // zamykamy strumien wyjsciowy
}






void pomiar(ifstream& strumien)
{

    strumien.open("dane.txt", ios_base::in); // otwarcie strumienia do pliku z danymi wejsciowymi dla grafow dla odczytywania grafów
    znajdz_droge(strumien);                  // szukanie grogi dla grafow
    strumien.close();                        // zamykamy strumien danych
}






int main()
{
    int wybor = 0;          //zmienna potrzebna do menu wyboru opcji

    fstream dane;
    ifstream wejscie;       //zmienne potrzebne do strumienia danych

    srand(time(NULL));      //wyzerowanie pomiaru czasu

    while( wybor > 2 || wybor < 1 )   // menu
    {
        while( wybor > 2 || wybor < 1 )
        {
            cout << "Opcje: \n";
            cout << "Wybierz '1', aby wygenerować dane do pliku tekstowego. \n";
            cout << "Wybierz '2', aby zrealizować pomiar najkrótszej ścieżki dla wcześniej wygenerowanych danych. \n";
            cin >> wybor;
            if(wybor > 2 || wybor < 1)
            cout << "Nie ma takiej opcji, wybierz ponownie\n";
        }

        switch(wybor)
        {
            case 1: generuj_dane(dane);     // generuje dane i zabiera ok. 1.2 GB pamięci
            case 2: pomiar(wejscie);        // czytuje dane, znajduje ścieżkę i zapisuje ją do pliku
        }
    }
    return 0;
}
