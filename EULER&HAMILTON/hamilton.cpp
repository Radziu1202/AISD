#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <Windows.h>
#include "math.h"
#include "random"
#include <iostream>
#include <fstream>

using namespace std;
double PCFreq = 0.0;
__int64 CounterStart = 0;
void StartCounter()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        printf("QueryPerformanceFrequency failed!\n");

    PCFreq = double(li.QuadPart);

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart - CounterStart) / PCFreq;
}		//chronometr


//------FUNKCJE POMOCNICZNE------------------------------

void graphiz(int **M, int n)
{
    printf("graph G {\n");
    for (int i = 0; i < n; i++)
    {
        for (int j =  i+1; j < n; j++)
        {
            if (M[i][j])
                printf("%d -> %d\n", i, j);
        }
    }
    printf("}\n");
}


void print_matrix(int **A, int n)
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int **new_empty(int n)
{
    int **G = new int *[n];
    for (int i = 0; i < n; i++)
    {
        G[i] = new int[n]();
    }
    return G;
}

void DFS(int** G, int v, int n, int &liczba_odwiedzonych)
{

    if (G[v][v])
    {
        for (int w = 0; w < n; w++)
        {
            if (G[v][w] && v != w)
            {
                G[v][w] = 0;
                G[w][v] = 0;
                G[v][v]--;
                G[w][w]--;
                liczba_odwiedzonych++;
                if (liczba_odwiedzonych==n)
                {
  //                  cout<<"graf jest spojny"<<endl;
                }
                DFS(G, w,  n,liczba_odwiedzonych);
            }
        }
    }
}


void czySpojny(int** graf, int n)
{
    int liczba_odwiedzonych=0;
    DFS(graf,0,n,liczba_odwiedzonych);

}
//-------------------Funkcja szukająca cyklu Hamiltona-------------------------

void printSolution(int* path,int n);

/*funkcja ktora sprawdza czy wierzcholek moze byc dodany na
   index 'pos' w dotychczasowym cyklu Hamiltona  przechowywanym w '*path' */
bool isSafe(int v, int** graph,int n, int *path, int pos)
{
    /* sprawdzamy czy wierzchołek ma krawedz z poprzednio dodanym wierzchołkiem*/
    if (graph [ path[pos-1] ][ v ] == 0)
        return false;

    /* sprawdzamy czy wierzchołek był juz uprzednio dodany */
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

/* Główna funkcja - rekurencyjna*/
bool hamCycleUtil(int** graph,int n, int path[], int pos)
{
    double przerwanie;
    /* sprawdzamy czy liczba wierzchołków w grafie jest równa podanemu n */
    if (pos == n)
    {
        // sprawdzamy czy istnieje krawedz miedzy ostatnim dodanym wierzchołkiem
        //a pierwszym dodanym.
        if ( graph[ path[pos-1] ][ path[0] ] == 1 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Sprawdzamy rozne wierzchołki jako kandydatow do polączenia
    // nie sprawdzamy zera bo zero zawsze dodajemy jako pierwsze
    for (int v = 1; v < n; v++)
    {
        /* funkcją isSafe sprawdzamy czy wierzchołek moze byc dodany do cyklu */
        if (isSafe(v, graph,n, path, pos))
        {
            path[pos] = v;
            przerwanie = GetCounter();
            if (przerwanie>20)
            {
                return false;
            }
            /* rekurencyjnie wywołujemy główną fukncje jesli dodalismy wierzchołek */
            if (hamCycleUtil (graph,n, path, pos+1) == true)
                return true;

            /* jeśli dodanie wierzchołka było błędne to je cofamy*/
            path[pos] = -1;
        }
    }

    /* jesli zaden z wierzchołków nie pasuje do cyklu zwracamy false */
    return false;
}

bool hamCycle(int **graph, int n)
{
    StartCounter();
    int *path = new int[n];
    for (int i = 0; i < n; i++)
        path[i] = -1;

    /* Ustawiwamy wierzchołek 0 jako pierwszym w cyklu (mozemy z jakiegokolwiek
    jesli graf jest nieskierowany)*/
    path[0] = 0;
    if ( hamCycleUtil(graph,n, path, 1) == false )
    {
   //     printf("\nSolution does not exist");
        return false;
    }

    printSolution(path,n);
    return true;
}

/* funkcja do wypisania przykładowego cyklu */
void printSolution(int *path, int n)
{
  /*  printf ("Solution Exists:"
            " Following is one Hamiltonian Cycle \n");
    for (int i = 0; i < n; i++)
        printf(" %d ", path[i]);

    printf(" %d ", path[0]);
    printf("\n");
 */
}



//-----------TWORZENIE GRAFU-------------------------

int** spojny_ham(int n)
{
    int temp1,temp2=0;
    int *used;
    used = new int[n] {0};
    int connected;
    int ** graf=new_empty(n);

    for (int i=0; i<n-1; i++)
    {
        temp1=temp2;
        temp2 = rand()%n;

        while (temp1 == temp2||used[temp2])
        {
            temp2 = rand()%n;

        }
        graf[temp1][temp2] = 1;
        graf[temp2][temp1]=1;
        graf[temp1][temp1]++;
        graf[temp2][temp2]++;
        used[temp2]=1;
        used[temp1]=1;
    }
    graf[temp2][0]=1;
    graf[0][temp2]=1;
    return graf;
}

int** ham_nasycony(double nasycenie,int n)
{
    int**G =spojny_ham(n);
    int temp1,temp2;
    int liczba_krawedzi=((n*(n-1))/2)*nasycenie;
    for (int i = n; i<=liczba_krawedzi; i++)
    {
        temp1=rand()%n;
        temp2=rand()%n;
        while(temp1==temp2)
        {
            temp2=rand()%n;
        }
        G[temp1][temp2]=1;
        G[temp2][temp1]=1;
    }

    return G;
}

//--------------------Główna Funkcja---------------------------
void average(double nasycenie)
{

    fstream zapis;
    int** nasycony;
    double suma_czasow=0;
    for (int n = 10; n<=100; n+=5)
    {
        for (int i =0; i<15; i++)
        {
            cout<< n<< " "<<i<<endl;
            nasycony=ham_nasycony(nasycenie,n);
            StartCounter();
            hamCycle(nasycony,n);
            suma_czasow+=GetCounter();
            cout<<GetCounter()<<endl;
            czySpojny(nasycony,n);
           for (int j=0; j<n; j++)
            {
                delete nasycony[j];
            }
            delete[] nasycony;

        }
        cout<<"sredni czas ham "<<nasycenie<<" "<<n<<" "<<suma_czasow/15.0<<endl;


        zapis.open("wyniki.txt", ios::out | ios::app);
        if(zapis.good() == true)
        {
            zapis<<suma_czasow/15.0<<"\t"<< n <<" " <<nasycenie<<endl;
            zapis.close();
        }
        suma_czasow=0;
    }
}

void test(double nasycenie)
{

    int** nasycony;
    double suma_czasow=0;
    for (int n = 300; n<=500; n+=100)
    {
        for (int i =0; i<10; i++)
        {
            nasycony=ham_nasycony(nasycenie,n);
            StartCounter();
            hamCycle(nasycony,n);
            suma_czasow+=GetCounter();
            czySpojny(nasycony,n);
           for (int j=0; j<n; j++)
            {
                delete nasycony[j];
            }
            delete []nasycony;
        }
        cout<<n<<" "<<nasycenie<<" "<<suma_czasow/10.0<<"\t";
        suma_czasow=0;
    }
    cout<<endl;
}


int main(void)
{

    srand(time(NULL));
   // test(0.25);
    test(0.4);
    test(0.7);
    test(0.98);
  //  average(0.2);
  //  average(0.3);
   // average(0.95);
   // average(0.8);
   // average(0.6);
   // average(0.4);




    return 0;

}
