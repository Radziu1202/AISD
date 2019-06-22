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

void DFSM(int **M, int n, int v, int *visited, int *RES, int &k) {
	visited[v] = 1;
	for (int i = 0; i < n; i++) {
		if (M[v][i] && !visited[i]) DFSM(M, n, i, visited, RES, k);
	}
	RES[--k] = v;
}

void TSM(int **M, int n, int* visited, int* RES, int k) {
	for (int i = 0; i < n; i++) {
		if (!visited[i]) DFSM(M, n, i, visited, RES, k);
	}
}

int main()
{

    srand(time(NULL));
    int n=9500;
    int k;
    int *visited = new int[n]{0}; int *RES = new int[n];
    int **tablica = new_DAG(n);
    k=n;
    StartCounter();
    TSM(tablica,n,visited,RES,k);
    double czas=GetCounter();
    cout<<"Czas sorto topo : "<<czas<<endl;
    /*
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
                if(tablica[i][j]==1)
                    cout<<i<<"->"<<j<<endl;

            }
        }
       */
    delete [] tablica;

    return 0;
}
