#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <Windows.h>
#include "math.h"
#include "random"
#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <stack>

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




int** full(int n)
{
    int **G = new int *[n];
    for (int i = 0; i < n; i++)
    {
        G[i] = new int[n]();
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
                G[i][j] = 1;
        }
    }
    return G;
}


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

void shuffle_matrix(int **M, int n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int t = rand() % (i + 1);

        int *tmp_row = M[i];
        M[i] = M[t];
        M[t] = tmp_row;

        int tmp;
        for (int j = 0; j < n; j++)
        {
            tmp = M[j][i];
            M[j][i] = M[j][t];
            M[j][t] = tmp;
        }
    }
}



//--------------------------------------------

bool delete_four(int **M, int row, int col)
{
    if (M[row][col] == 1 && M[row + 1][col] == 1 &&
            M[row + 1][col + 1] == 1 && M[row][col + 1] == 1 &&
            M[row][row] > 2 && M[row + 1][row + 1] > 2)
    {

        M[row][col] = 0;
        M[col][row] = 0;
        M[row + 1][col] = 0;
        M[col][row + 1] = 0;
        M[row + 1][col + 1] = 0;
        M[col + 1][row + 1] = 0;
        M[row][col + 1] = 0;
        M[col + 1][row] = 0;

        M[row][row] -= 2;
        M[col][col] -= 2;
        M[row + 1][row + 1] -= 2;
        M[col + 1][col + 1] -= 2;
        return 1;
    }
    return 0;
}

void delete_edges(int **G, int n, double nasycenie, int edges)  	//usuwa krawędzie czwórkami tak długo,
{
    int t_row, t_col;												//aż osiągnie wymaganą ilość
    while (edges > (n*(n - 1)/2)*nasycenie)
    {
        t_row = rand() % (n / 2 - 2) + 1;
        t_col = rand() % (n / 2 - 2) + n / 2 + 1;
        if (delete_four(G, t_row, t_col))
        {
            edges -= 4;
        }
    }
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

int **new_bipartite(int n)
{
    int **G = new_empty(n);

    for (int i = 0; i < n / 2; i++)  		//tworzy pełny graf dwudzielny K_n/2,n/2
    {
        for (int j = n / 2; j < n; j++)
        {
            G[i][j] = 1;
            G[j][i] = 1;
        }
    }
    return G;
}

int **new_graph_euler(int n,double nasycenie)
{
    int **G = new_bipartite(n);
    for (int i = 0; i < n; i++)  		//ilość jedynek w każdym z rzędów
    {
        G[i][i] = n / 2;
    }

    int edges = n*n / 4;
    delete_edges(G, n, nasycenie, edges);
    shuffle_matrix(G, n);				//przetasowuje macierz
    return G;
}



std::list<int>* mat2list(int** G, int n)
{
    std::list<int>* lista = new std::list<int>[n];
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(G[i][j] && i!=j)
            {
                lista[i].push_back(j);
            }
        }
    }
    return lista;
}



//------------------------------------
void DFS(int** G, int v, int n, int &liczba_odwiedzonych,int *visited)
{
    if (G[v][v])
    {
        for (int w = 0; w < n; w++ )
        {
            if (G[v][w] && v != w && !visited[w] )
            {
                visited[w] = 1;
                liczba_odwiedzonych++;
               // cout<<liczba_odwiedzonych;
          /*      if (liczba_odwiedzonych==n)
                {
                    cout<<"graf jest spojny"<<endl;
                }
*/                DFS(G, w, n,liczba_odwiedzonych,visited);
            }
        }
    }
}

void czy_spojny(int** G,int n)
{
    int* visited;
    visited = new int[n] {0};
    int liczba_odwiedzonych=0;
    DFS(G,0,n,liczba_odwiedzonych,visited);
}

void znajdz_cykl(list<int>* lista,int n,int** tablica)
{
    vector<int> cykl;
    stack<int> path;
    int curr_v=0;
    path.push(0);
    while (!path.empty())
    {
        if (tablica[curr_v][curr_v])
        {
            int next_v = lista[curr_v].back();
            if (!tablica[next_v][curr_v]) {
                tablica[curr_v][next_v] = 0;
                tablica[curr_v][curr_v]--;
                lista[curr_v].pop_back();
                continue;
            }

            path.push(curr_v);
            tablica[curr_v][curr_v]--;
            tablica[curr_v][next_v] = 0;
            lista[curr_v].pop_back();
            curr_v = next_v;
        }
         else
        {
            cykl.push_back(curr_v);

            //backtrack
            curr_v = path.top();
            path.pop();
        }
    }
 /*     for (int i =0;i<n;i++)
     {
         cout<<i<<" "<<tablica[i][i]<<endl;
     }
*/
/*
    for (int i=cykl.size()-1; i>=0; i--)
    {
        cout << cykl[i];
        if (i)
           cout<<" -> ";
    }
*/
}



void Euler(list<int>*G, int n, int** tablica)
{

  //  cout<<endl<<"Cykl Eulera:";
      czy_spojny(tablica, n);
    znajdz_cykl(G,n,tablica);
}



void average(double nasycenie)
{
    double suma_czasow=0;
    fstream zapis;
    int** graf;
    list<int>*lista;
    for (int n=250; n<=5000; n+=250)
    {
        for (int i =0; i<20; i++)
        {
            cout<<"tworze nowe grafy"<<endl;
            graf=new_graph_euler(n,nasycenie);
            lista=mat2list(graf,n);
            StartCounter();
            Euler(lista,n,graf);
            suma_czasow+=GetCounter();
            cout<<GetCounter()<<endl;
            for (int j=0; j<n; j++)
            {
                delete graf[j];
            }
            delete[] graf;
        }
        cout<<"sredni czas eulera "<<nasycenie<<" "<<n<<" "<<suma_czasow/20.0<<endl;


        zapis.open("wyniki euler.txt", ios::out | ios::app);
        if(zapis.good() == true)
        {
            zapis<<suma_czasow/20.0<<"\t"<<nasycenie <<" "<<n<<endl;
            zapis.close();
        }
        suma_czasow=0;
    }
}




int main(void)
{
    srand(time(NULL));

    //  average(0.2);
   //   average(0.3);
     // average(0.4);
     // average(0.6);
    //  average(0.8);
     // average(0.95);
/*     int n,V1,V2;
     cout<<"podaj liczbe wierzcholkow:";
     cin>>n;
     int **tab;
     tab=new int*[n];
            for ( int i=0; i<n; i++)
            {
                tab[i]=new int [n];
            }
            for ( int i=0; i<n; i++)
            {
                for ( int j=0; j<n; j++)
                {
                    tab[i][j]=0;
                }
            }
     char wyborT;
            do
            {
                wyborT=menuTworzenia();
                switch(wyborT)
                {
                case '1':
                    cout<<"podaj pare wierzcholkow od 0 do "<< n-1 <<endl;
                    cin>>V1;

                    cin>>V2;
                    tab[V1][V2]=1;
                    tab[V2][V1]=1;
                    tab[V1][V1]++;
                    tab[V2][V2]++;

                    break;
                default:
                    cout<< "stworzono graf"<<endl;
                }
                }while(wyborT != '2');
    print_matrix(tab,n);
    list<int>*lista=mat2list(tab,n);
    Euler(lista,n,tab);
  */
    return 0;
}
