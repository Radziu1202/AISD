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
            {
                G[i][j] = 1;
                G[j][j]++;
            }
        }
    }
    return G;
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



void usuwanie(int** graf,double nasycenie,int n)
{
    int V1,V2,V3,V4;

    int liczba_krawedzi=(n*(n-1))/2;
    int obecna_liczba_krawedzi=liczba_krawedzi;
    if((n%2)==1)
    {
        while(obecna_liczba_krawedzi>(liczba_krawedzi*nasycenie))
        {
            V1 = rand()%n;
            V2 = rand()%n;
            while(V2==V1 || graf[V1][V2]==0 )
            {
                V2=rand()%n;
            }
            V3=rand()%n;
            while(V3==V1 || V3==V2 || graf[V2][V3]==0)
            {
                V3=rand()%n;
            }
            V4=rand()%n;
            while(V4==V1 || V4==V2 || V4==V3 || graf[V3][V4]==0 || graf[V1][V4]==0 )
            {
                V4=rand()%n;
            }
            graf[V1][V2]=0;
            graf[V2][V1]=0;
            graf[V2][V3]=0;
            graf[V3][V2]=0;
            graf[V3][V4]=0;
            graf[V4][V3]=0;
            graf[V4][V1]=0;
            graf[V1][V4]=0;
            graf[V1][V1]-=2;
            graf[V2][V2]-=2;
            graf[V3][V3]-=2;
            graf[V4][V4]-=2;
            obecna_liczba_krawedzi-=4;
        }
    }
    else
    {
        graf[0][0]--;
        obecna_liczba_krawedzi--;
        for (int i=0;i<(n-1);i++)
        {
            graf[i][i+1]=0;
             graf[i+1][i]=0;
             graf[i+1][i+1]--;
             obecna_liczba_krawedzi--;
        }
         while(obecna_liczba_krawedzi>(liczba_krawedzi*nasycenie))
        {
            V1 = rand()%n;
            V2 = rand()%n;
            while(V2==V1 || graf[V1][V2]==0 )
            {
                V2=rand()%n;
            }
            V3=rand()%n;
            while(V3==V1 || V3==V2 || graf[V2][V3]==0)
            {
                V3=rand()%n;
            }
            V4=rand()%n;
            while(V4==V1 || V4==V2 || V4==V3 || graf[V3][V4]==0 || graf[V1][V4]==0 )
            {
                V4=rand()%n;
            }
            graf[V1][V2]=0;
            graf[V2][V1]=0;
            graf[V2][V3]=0;
            graf[V3][V2]=0;
            graf[V3][V4]=0;
            graf[V4][V3]=0;
            graf[V4][V1]=0;
            graf[V1][V4]=0;
            graf[V1][V1]-=2;
            graf[V2][V2]-=2;
            graf[V3][V3]-=2;
            graf[V4][V4]-=2;
            obecna_liczba_krawedzi-=4;
        }
    }
}
int **Eulerian(int n,double nasycenie)
{
    int **graf=full(n);
    usuwanie(graf,nasycenie,n);
    shuffle_matrix(graf,n);
    return graf;
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
                if (liczba_odwiedzonych==n)
                {
                    //  cout<<"graf jest spojny"<<endl;
                }
                DFS(G, w, n,liczba_odwiedzonych,visited);
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
            if (!tablica[next_v][curr_v])
            {
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


void test(double nasycenie)
{
    double suma_czasow=0.0;
    int** graf;
    list<int>*lista;
    for (int n = 300; n<=500; n+=100)
    {
        for (int i =0; i<20; i++)
        {
            graf=Eulerian(n,nasycenie);
            lista=mat2list(graf,n);
            StartCounter();
            Euler(lista,n,graf);
            suma_czasow+=GetCounter();

            for (int j=0; j<n; j++)
            {
                delete[]graf[j];
            }
            delete[]graf;
        }
        cout<<n<<" "<<nasycenie<<": "<<suma_czasow/10.0<<"\t";
        suma_czasow=0;
    }
    cout<<endl;
}

int main()
{
    srand(time(NULL));
     test(0.25);
     test(0.4);
     test(0.7);
     test(0.98);



}

