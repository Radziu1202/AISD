#include "stdlib.h"
#include "time.h"
#include <Windows.h>
#include "math.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <random>
#include <string>
#define  RATE 0.3
using namespace std;
const int P = 1;			//liczba prób dla pojedynczego grafu
const int G = 1;			//liczba różnych grafów tego samego rozmiaru


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




int **new_DAG(int n)
{
    int **DAG = new int*[n];
    for (int i = 0; i < n; i++)
    {
        DAG[i] = new int[n]();
    }
    const double chance = RATE*RAND_MAX;
    for (int j = 0; j < n-1; j++)
    {
        for (int k = j + 1; k < n; k++)
        {
            if (rand()<chance)
            {
                DAG[j][k] = 1;
            }
        }
    }
    shuffle_matrix(DAG, n);
    return DAG;
}

int *topological_sort( int **tab,int n)
{
    int *indeg,*flag,count=0;
    indeg = new int [n]{0};
    flag= new int [n]{0};


    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            indeg[i]+=tab[j][i];

    cout<<"\nThe topological order is:";

        while(count<n){
            for(int k=0;k<n;k++){
                if((indeg[k]==0) && (flag[k]==0)){
                    cout<<k<<" ";
                    flag[k]=1;
                }

                indeg[k]=0;
            }

            count++;
        }

        return 0;
    }
}
int main()
{

    srand(time(NULL));
    double suma_czasow;
    int n=10;
    int k;
    int *visited = new int[n] {0};
    int *RES = new int[n];
    int **tablica = new_DAG(n);
    k=n;
    StartCounter();
    int *kamila= TSM(tablica,n,visited,RES,k);
    double czas=GetCounter();
    cout<<"Czas kamila metody : "<<czas<<endl;

    for (int i = 0 ; i <n ; i++)
    {
        for (int j=0 ; j < n ; j++)
        {
            cout<<tablica[i][j]<<" ";
        }
        cout<<endl;
    }


    for (int i = 0 ; i <n ; i++)
    {
        for (int j=0 ; j < n ; j++)
        {
            if(tablica[i][j])
                cout<<i<<"->"<<j<<endl;
        }
    }

    StartCounter();
    int *tab = topological_sort(tablica,n);
    czas= GetCounter();
    cout<<"Czas: "<<czas<<endl;

    for (int i = 0 ; i <n ; i++)
    {
        cout<<kamila[i]<<" ";

    }
    cout<<"to moje: "<<endl;
    for (int i = 0 ; i <n ; i++)
    {
        cout<<tab[i]<<" ";

    }


    delete[]tab;
    delete [] tablica;


    return 0;
}
