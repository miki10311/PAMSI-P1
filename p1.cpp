#include<iostream>
#include<ctime>
#include<fstream>
#include<vector>


using namespace std;



class sortowanie_szybkie
{
    vector <int> &tablica;
public:

    sortowanie_szybkie(vector <int>& tablica) :tablica(tablica) {};
    void sortowanie(int lewy, int prawy);
    void sortowanie_odwrotne(int lewy, int prawy);            // lewy i prawy to pierwszy i ostatni element tablicy
};

void sortowanie_szybkie::sortowanie_odwrotne(int lewy, int prawy)
{
    int i = (lewy + prawy) / 2;
    int piwot = tablica[i];
    tablica[i] = tablica[prawy];
    int j = lewy;
    for (i = lewy; i < prawy; i++)
    {
        if (tablica[i] > piwot)
        {
            swap(tablica[i], tablica[j]);
            j++;
        }
    }
    tablica[prawy] = tablica[j];
    tablica[j] = piwot;
    if (lewy < j - 1)
        sortowanie_odwrotne(lewy, j - 1);
    if (prawy > j + 1)
        sortowanie_odwrotne(j + 1, prawy);
}

void sortowanie_szybkie::sortowanie(int lewy, int prawy)
{
    int i = (lewy + prawy) / 2;
    int piwot = tablica[i];
    tablica[i] = tablica[prawy];
    int j = lewy;
    for (i = lewy; i < prawy; i++)
    {
        if (tablica[i] < piwot)
        {
            swap(tablica[i], tablica[j]);
            j++;
        }
    }
    tablica[prawy] = tablica[j];
    tablica[j] = piwot;
    if (lewy < j - 1)
        sortowanie(lewy, j - 1);
    if (prawy > j + 1)
        sortowanie( j + 1 ,prawy);
}



class sortowanie_przez_scalanie
{
    vector <int> &tablica;
    vector <int> tablice_pomocnicza;
public:

    sortowanie_przez_scalanie(vector <int>& tablica) :tablica(tablica)
    {
        tablice_pomocnicza.resize(tablica.size());
    }
    void sortowanie(int lewy, int prawy);

};

void sortowanie_przez_scalanie::sortowanie(int lewy, int prawy)
{
    int srodek, i, i2, i1;
    srodek = (prawy + lewy + 1) / 2;
    if (srodek - lewy > 1)
        sortowanie(lewy, srodek - 1);
    if (prawy - srodek > 0)
        sortowanie(srodek, prawy);

    i1 = lewy;
    i2 = srodek;

    for (i = lewy; i <= prawy; i++)
    {
        if ((i1 == srodek) || ((i2 <= prawy) && (tablica[i1] > tablica[i2])))
        {
            tablice_pomocnicza[i] = tablica[i2++];
        }
        else
        {
            tablice_pomocnicza[i] = tablica[i1++];
        }
    }

    for (i = lewy; i <= prawy; i++)
    {
        tablica[i] = tablice_pomocnicza[i];
    }
    
}



class sortowanie_shella
{
    vector <int>& tablica;
    int N;
public:

    sortowanie_shella(vector <int>& tablica) :tablica(tablica) { N = tablica.size(); };
    void sortowanie();

};


void sortowanie_shella::sortowanie()
{
    int podzial,i,pom;
    for (podzial = 1; podzial < N; podzial = 3 * podzial + 1);
    podzial = podzial/ 9;
    if (!podzial) podzial++;



    while (podzial)
    {
        for (int j = N - podzial - 1; j >= 0; j--)
        {
            pom = tablica[j];
            i = j + podzial;
            while ((i < N) && (pom > tablica[i]))
            {
                tablica[i - podzial] = tablica[i];
                i = i+ podzial;
            }
            tablica[i - podzial] = pom;
        }
        podzial = podzial/ 3;
    }
}

int main()
{
    srand(time(NULL));
    time_t czas,suma=0;    // do zliczania czasu trwania algorytmu
    fstream plik;          // do zapisania wyników w pliku
    int ik;                // do wyboru w menu
    char znak;             // do wyboru z menu
    vector <int> tablica;  // wektor będący naszą pojedyńczą tablicą
    int tab[] = { 10,50,100,500,1000 };                                    // tablica z ilością elementów podzieloną przez tysiąc dla ułatwienia testów
    double poziom_posortowania[] = { 0.25,0.50,0.75,0.95,0.99,0.997,0 };   // tablica zawierająca poziomy posortowania pierwszych x procent elementów tablicy
    plik.open("wyniki.txt", ios::app);

    
    cout << " q - sortowanie szybkie \n s - sortowanie przez scalanie \n h - sortowanie shella \n" << endl;
    cout << " 1 - sortowanie szybkie tab odwrotnej \n 2 - sortowanie przez scalanie tab odwrotnej \n 3 - sortowanie shella tab odwrotnej \n" << endl;
    cin >> znak;

    switch (znak)
    {
    case 'q':
        cout << " 0 - 25%\n 1 - 50%\n 2 - 75%\n 3 - 95%\n 4 - 99%\n 5 - 99.7%\n 6 - 0%\n" << endl;
        cin >> ik;
        for (int k = 0; k < 5; k++)            // pięć rozmiarów tablic
        {
            for (int i = 0; i < 100; i++)        // sto tablic sortowanych jednocześnie
            {
                for (int j = 0; j < tab[k] * 1000 ; j++)   // wypełnianie tablicy losowymi liczbami, tyle tysięcy ile w tab
                {
                    tablica.push_back(rand());
                }

                if (ik != 6)      // zapewnienie posortowania pierwszych x % elementów
                {
                    sortowanie_szybkie sort(tablica);

                    sort.sortowanie(0, tablica.size() * poziom_posortowania[ik] - 1); // wysyłamy do sortowania pierwszy i ostatni element
                }
                sortowanie_szybkie sort(tablica);
                clock_t start = clock();

                /*
                for(int g=0; g<10; g++)     // testy poprawności sortowania
                cout<<tablica[g]<<endl;
                cout<<endl;
                */

                sort.sortowanie(0, tablica.size() - 1);

                /*
                for(int g=0; g<10; g++)     // testy poprawności sortowania
                cout<<tablica[g]<<endl;

                sort.sortowanie_odwrotne(0, tablica.size()); 
                cout<<endl;

                for(int g=0; g<10; g++)
                cout<<tablica[g]<<endl;
                */

                suma += clock() - start;
                tablica.clear();
            }
            plik << suma / 100 << endl; //średnia ze stu tablic
        }
        break;
        
    case 's':
        cout << " 0 - 25%\n 1 - 50%\n 2 - 75%\n 3 - 95%\n 4 - 99%\n 5 - 99.7%\n 6 - 0%\n" << endl;
        cin >> ik;
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < tab[k] * 1000 ; j++)
                {
                    tablica.push_back(rand());
                }

                if (ik != 6)
                {
                    sortowanie_szybkie sort(tablica);

                    sort.sortowanie(0, tablica.size() * poziom_posortowania[ik] - 1);
                }
                sortowanie_przez_scalanie sort(tablica);
                clock_t start = clock();

                /*
                for(int g=0; g<10; g++)     // testy poprawności sortowania
                cout<<tablica[g]<<endl;
                cout<<endl;
                */

                sort.sortowanie(0, tablica.size() - 1);

                /*
                for(int g=0; g<10; g++)     // testy poprawności sortowania
                cout<<tablica[g]<<endl;
                cout<<endl;
                */

                suma += clock() - start;
                tablica.clear();
            }
            plik << suma / 100 << endl;
        }
        break;

    case 'h':
        cout << " 0 - 25%\n 1 - 50%\n 2 - 75%\n 3 - 95%\n 4 - 99%\n 5 - 99.7%\n 6 - 0%\n" << endl;
        cin >> ik;
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < tab[k] * 1000 ; j++)
                {
                    tablica.push_back(rand());
                }

                if (ik != 6)
                {
                    sortowanie_szybkie sort(tablica);

                    sort.sortowanie(0, tablica.size() * poziom_posortowania[ik] - 1);
                }
                sortowanie_shella sort(tablica);
                clock_t start = clock();

                /*
                for(int g=0; g<10; g++)     // testy poprawności sortowania
                cout<<tablica[g]<<endl;
                cout<<endl;
                */

                sort.sortowanie();

                /*
                for(int g=0; g<10; g++)     // testy poprawności sortowania
                cout<<tablica[g]<<endl;
                cout<<endl;
                */

                suma += clock() - start;
                tablica.clear();
            }
            plik << suma / 100 << endl;
        }
        break;

    case '1':      // od teraz w dół dla odwrotnych
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < tab[k] * 1000; j++)
                {
                    tablica.push_back(rand());
                }

                sortowanie_szybkie sort(tablica);
                sort.sortowanie_odwrotne(0, tablica.size());
                clock_t start = clock();
                sort.sortowanie(0, tablica.size() - 1);

                suma += clock() - start;
                tablica.clear();
            }
            plik << suma / 100 << endl;
        }
        break;

    case '2':
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < tab[k] * 1000; j++)
                {
                    tablica.push_back(rand());
                }

                sortowanie_szybkie sort2(tablica);
                sort2.sortowanie_odwrotne(0, tablica.size());
                sortowanie_przez_scalanie sort(tablica);
                clock_t start = clock();
                sort.sortowanie(0, tablica.size() - 1);

                suma += clock() - start;
                tablica.clear();
            }
            plik << suma / 100 << endl;
        }
        break;

    case '3':
        for (int k = 0; k < 5; k++)
        {
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < tab[k] * 1000; j++)
                {
                    tablica.push_back(rand());
                }

                sortowanie_szybkie sort2(tablica);
                sort2.sortowanie_odwrotne(0, tablica.size());
                sortowanie_shella sort(tablica);
                clock_t start = clock();
                sort.sortowanie();

                suma += clock() - start;
                tablica.clear();
            }
            plik << suma / 100 << endl;
        }
        break;
    }
    plik.close();
}
