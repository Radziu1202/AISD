#include <iostream>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <ctime>
using namespace std;

struct node{
	int numer;
	int *tab;
	int liczba_polaczen;
	node *next;
};
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

int countNumberOfLines(const char * fileName){
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

struct data_batch{
	int* wierzcholkiZ;
	int* wierzcholkiDo;
	int length;
	int range;
};



data_batch readFromFile(const char* fileName){
	int n = countNumberOfLines("dane.txt");
	string wierzcholek1,wierzcholek2;

    int max=0;
    int *wierzcholkiZ=new int[n];
    int *wierzcholkiDo=new int[n];
    int index=0;
	string line;
	size_t read; size_t len;
	string delimiter = ";";
	fstream fp;
	fp.open("dane.txt");
	while (getline(fp,line)) {
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
        if(max<V1)  max=V1;
        if(max<V2)  max=V2;
    }
    fp.close();

    data_batch ret;
    ret.wierzcholkiZ = wierzcholkiZ;
    ret.wierzcholkiDo = wierzcholkiDo;
    ret.length = n;
    ret.range = max+1;
    return ret;
}



void shuffle(int *array, size_t n)
{
	for (int i = n - 1; i > 0; i--) {
		int t = rand() % (i + 1);
		int tmp = array[i];
		array[i] = array[t];
		array[t] = tmp;
	}
}




int** generator(int n, double nasycenie){
    int **A;
    A = new int * [n];

    for(int i = 0; i < n; i++)
    {
        A[i] = new int[n];
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            A[i][j] = 0;
        }
    }

default_random_engine generator;
uniform_int_distribution<int> distribution(0,n-1);
    for (int i=0;i<nasycenie*((n*(n-1))/2);i++)
    {


        int w =rand()% n;

        int k = distribution(generator);

        while (w==k)
        {
            k= distribution(generator);
        }
        if (A[w][k]!=1)
        {
            A[w][k]=1;
            A[k][w]=1;
        }
        else
            i-=1;
    }

    return A;
}

node *L_sasiad(int **tab,int n)
{

    node* head = NULL;

    int ind=0;
    for(int i = 0;i<n;i++)
    {
        cout<<endl<<i<<endl;  //------------Printowanie listy
        node *p=new node;
        p->numer = i;
        p->liczba_polaczen=0;
        for (int j =0;j<n;j++)
        {
            if (tab[i][j]==1)
            {
               p->liczba_polaczen++;
            }
        }
        p->tab = new int[p->liczba_polaczen];
        for(int k = 0 ;k<n;k++)
        {
            if (tab[i][k]==1)
                {
                p->tab[ind]=k;
                cout<<p->tab[ind]<<" ";      //-----PRINTOWANIE LISTY TU I NA Gorze
                ind++;
                }

        }
        p->next = head;
		head = p;
		ind=0;
    }

    return head;
}

int czy_istnieje_krawedz(node *head ,int a,int b,int n)
{
    int ind=0;

while(head->numer!=a)
{
    head=head->next;
}
    int rozmiar_tab=head->liczba_polaczen;
    while(ind < rozmiar_tab)
         {
             if(head->tab[ind]==b)
                {
                    return 1;
                }
                ind++;
         }


    return 0;
}

int executeLS(node *head,int n)
{
    int *losowa=new int[n];
    for (int i=0;i<n;i++)
      {
       losowa[i]=i;
      }
      shuffle(losowa,n);
    int liczba_krawedzi=0;
    for (int i = 0 ;i<n ; i++)
    {
        for (int j=0;j<n;j++)
        {
            liczba_krawedzi+=czy_istnieje_krawedz(head,losowa[i],losowa[j],n);
        }
    }
    return liczba_krawedzi/2;
}
int main()
{
    srand(time(0));

    data_batch data = readFromFile("dane.txt");
    const char* plik = "dane.txt";
    int **graf=new_empty(data.range);
    cout<<data.range<<"yo";
    for (int i=0;i< data.length;i++)
    {
        graf[data.wierzcholkiZ[i]][data.wierzcholkiDo[i]]=1;
        graf[data.wierzcholkiDo[i]][data.wierzcholkiZ[i]]=1;
    }
     for (int i=0;i< data.range;i++)
    {
        for (int j=0;j<data.range;j++)
        {
            cout<<graf[i][j]<<" ";
        }
        cout<<endl;
    }








/*
    for (int i = 0;i<n;i++)
    {
        for (int j =0;j<n;j++)
        {
            cout<<tab[i][j]<<" ";
        }
        cout<<endl;
    }
*/
    node *lista= L_sasiad(graf,data.range);


    StartCounter();
    int a = executeLS(lista,data.range);
    double czas = GetCounter();
    czas=czas/(double)data.range;
    cout<<endl<<"liczba krawedzi = "<<a<<endl;;
    cout<<czas;

    return 0;
}
