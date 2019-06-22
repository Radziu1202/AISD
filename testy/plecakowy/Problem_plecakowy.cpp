#include "stdlib.h"
#include "time.h"
#include <Windows.h>
#include "math.h"
#include "random"
#include "stdio.h"
#include "iostream"
#include "algorithm"
#include <fstream>

using namespace std;


struct item
{
    int waga;
    int wartosc;
};

void print_matrix(int**K, int n, int n1)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            if (K[i][j]<10)
            cout<<K[i][j]<<"  ";
            else cout<<K[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

double **new_part(int n)
{
    double** part = new double*[n];
    for (int i = 0; i < n; i++)
    {
        part[i] = new double[3];
    }
    return part;
}

int **new_matrix(int n,int n1)
{
    int **K = new int*[n + 1];
    for (int i = 0 ; i<(n+1) ; i++)
    {
        K[i]=new int[n1+1]();
    }
    return K;
}

void items(int **K, int n, int n1, struct item *itemy)
{
    cout<<"Dynamic wartosci Przedmiotow: ";
    int g = n, g1 = n1;
    int waga = 0;
    int M = -1, maksymalna = -1;
    while (M != 0)
    {
        for (int i = 0; i < g; i++)
        {
            for (int j = 0; j < g1; j++)
            {
                if (K[i][j] > maksymalna)
                {
                    maksymalna = K[i][j];
                    M = i;
                }
            }
        }
        g = M;
        g1 -= itemy[M - 1].waga;
        maksymalna = -1;
        if(M>=1)
            waga += itemy[M - 1].waga;
        if(M)
            cout<<itemy[M-1].wartosc<<" ";
    }
    cout<<endl<<"waga przdmiotow dynamic: "<<waga<<endl;
}

int dynamic(int**K, int W, struct item *itemy, int n)
{
    for (int i = 1; i < n+1; i++)
    {
        for (int w = 1; w < W+1; w++)
        {
            if (itemy[i-1].waga <= w)
                K[i][w] = max(itemy[i-1].wartosc+ K[i - 1][w - itemy[i-1].waga], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }

    }
	print_matrix(K, n + 1, W + 1);
    items(K, n + 1, W + 1, itemy);
    cout<<"Dynamic Wartosc "<<K[n][W]<<endl;
    return K[n][W];
}

bool sort_by_first(double* A, double* C)
{
    return A[0] > C[0];
}

int greedy(double**part, int W, struct item* itemy, int n)
{
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        part[i][1] = itemy[i].wartosc;
        part[i][2] = itemy[i].waga;
        part[i][0] = (part[i][1]/part[i][2]);
    }
    sort(part, part + n, sort_by_first);
    int k = 0;
    while (k < n)
    {
        if (W - part[k][2] < 0)
        {
            k++;
            continue;
        }
        res += part[k][1];
        W -= part[k++][2];
    }
    return res;
}

void test(int b)
{
    int n=5;
    struct item *itemy= new item[n];
    struct item IT;
    IT.waga=2;
    IT.wartosc=4;
    itemy[0]=IT;

    IT.waga=4;
    IT.wartosc=5;
    itemy[1]=IT;

    IT.waga=3;
    IT.wartosc=2;
    itemy[2]=IT;

    IT.waga=1;
    IT.wartosc=3;
    itemy[3]=IT;

    IT.waga=4;
    IT.wartosc=3;
    itemy[4]=IT;


    int** K = new_matrix(n,b);
    dynamic(K, b,itemy, n);
    double **part=new_part(n);
    cout<<endl<<"Wartosc greedy: "<<greedy(part,b,itemy,n);
}

int main()
{
    int b=8;
    test(b);
}
