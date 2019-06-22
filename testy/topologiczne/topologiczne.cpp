#include "stdlib.h"
#include "time.h"
#include <Windows.h>
#include "math.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <random>
#include <set>`
#include <string>
#define  RATE 0.3
using namespace std;
const int P = 1;			//liczba prób dla pojedynczego grafu
const int G = 1;			//liczba ró¿nych grafów tego samego rozmiaru


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

int **new_empty(int n)
{
    int **G = new int *[n];
    for (int i = 0; i < n; i++)
    {
        G[i] = new int[n]();
    }
    return G;
}

int countNumberOfLines(const char * fileName)
{
    int lines = 0;
    FILE *infile;
    infile = fopen(fileName, "r");
    char ch;


    while (EOF != (ch=getc(infile)))
        if (ch=='\n')
            lines++;
    fclose(infile);
    return lines;
}

struct data_batch
{
    int* wierzcholkiZ;
    int* wierzcholkiDo;
    int length;
    int range;
};



data_batch readFromFile(const char* fileName)
{
    int n = countNumberOfLines("dane.txt");
    string wierzcholek1,wierzcholek2;

    int max=0;
    int *wierzcholkiZ=new int[n];
    int *wierzcholkiDo=new int[n];
    int index=0;
    string line;
    size_t read;
    size_t len;
    string delimiter = ";";
    fstream fp;
    fp.open("dane.txt");
    while (getline(fp,line))
    {
        string l = line;
        int pos = 0;
        pos = l.find(delimiter);
        wierzcholek1 = l.substr(0, pos);
        stringstream geek(wierzcholek1);
        int V1=0;
        geek>> V1;
        wierzcholkiZ[index]=V1;
        l.erase(0, pos + 1);
        stringstream v2(l);
        int V2 = 0;
        v2 >> V2;
        wierzcholkiDo[index]=V2;
        index++;
        if(max<V1)
            max=V1;
        if(max<V2)
            max=V2;
    }
    fp.close();

    data_batch ret;
    ret.wierzcholkiZ = wierzcholkiZ;
    ret.wierzcholkiDo = wierzcholkiDo;
    ret.length = n;
    ret.range = max+1;
    return ret;
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
/*
bool isCyclicUtil(int v, bool *visited, int parent)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        // If an adjacent is not visited, then recur for that adjacent
        if (!visited[*i])
        {
           if (isCyclicUtil(*i, visited, v))
              return true;
        }

        // If an adjacent is visited and not parent of current vertex,
        // then there is a cycle.
        else if (*i != parent)
           return true;
    }
    return false;
}

// Returns true if the graph contains a cycle, else false.
bool isCyclic(int** graf;)
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to detect cycle in different
    // DFS trees
    for (int u = 0; u < V; u++)
        if (!visited[u]) // Don't recur for u if it is already visited
          if (isCyclicUtil(u, visited, -1))
             return true;

    return false;

*/

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

void DFSM(int **M, int n, int v, int *visited, int *RES, int &k)
{
    visited[v] = 1;

    for (int i = 0; i < n; i++)
    {
        if (M[v][i] && !visited[i])
            DFSM(M, n, i, visited, RES, k);
    }
    RES[--k] = v;
}

void TSM(int **M, int n, int* visited, int* RES, int k)
{
    for (int i = 0; i < n; i++)
    {

        if (!visited[i])
            DFSM(M, n, i, visited, RES, k);
    }
}
bool is_acyclic(int** A, int n, int v, set<int>* current)
{
    if(current -> count(v))
        return false;
    current -> insert(v);
    for(int i = 0; i < n; i++)
    {
        if(A[v][i])
            if(! is_acyclic(A, n, i, current))
                return false;
    }
    current -> erase(current -> find(v));
    return true;

}

bool check_if_cyclic(int** A, int n)
{
    bool ret = true;
    for(int i  = 0; i<n; i++)
        ret &= is_acyclic(A, n, i, new set<int>);
    return !ret;
}



int main()
{

    data_batch data = readFromFile("dane.txt");
    const char* plik = "dane.txt";
    int **graf=new_empty(data.range);
    for (int i=0; i< data.length; i++)
    {
        graf[data.wierzcholkiZ[i]][data.wierzcholkiDo[i]]=1;
    }
    for (int i=0; i< data.range; i++)
    {
        for (int j=0; j<data.range; j++)
        {
            cout<<graf[i][j]<<" ";
        }
        cout<<endl;
    }


    srand(time(NULL));
    int n=data.range;
    int *visited = new int[n] {0};
    int *RES = new int[n];
    int k=n;
    if (!check_if_cyclic(graf,n))
    {
        StartCounter();
        TSM(graf,n,visited,RES,k);
        double czas=GetCounter();
        cout<<"Czas sorto topo : "<<czas<<endl;
        cout<<RES[0];
        for (int i = 1 ; i <n ; i++)
        {
            if (RES[i]!=0)
            cout<<"->"<<RES[i];
        }
    }
    else
    {
        cout<<"Graf jest Cykliczny"<<endl;
    }
    delete [] graf;


    return 0;
}


