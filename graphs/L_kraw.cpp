#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
using namespace std;

struct node{
	int numer;
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
    //cout<<losowa[i]<<" "<<losowa[i]<<endl;

        int w =rand()% n;
       // cout<<"w= "<<w<<endl;
        int k = distribution(generator);
       // cout<<"k= "<<k<<endl;
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

int **L_kraw(int **tab,int n)
{
    int **tablica;
    int ile=0;
    for (int i = 0;i<n;i++)
    {
        for (int j =0;j<n;j++)
        {
            if (tab[i][j]==1)
            {
                ile++;
            }
        }
    }
    tablica=new int *[ile];
    for (int i = 0 ; i < ile ; i++)
    {
        tablica[i]=new int[2];
    }

    int index=0;
    for (int i =0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                if (tab[i][j]==1)
                {
                    tablica[index][0]=i;
                    tablica[index][1]=j;
                    cout<<i<<"->"<<j<<endl;
                    index++;
                }
            }
        }
        return tablica;
}
int czy_posiada_krawedz(int **tab,int a, int b, int m)
{

    for (int i =0;i<m;i++)
    {

        if ((tab[i][0]==a && tab[i][1]==b)||(tab[i][0]==b && tab[i][1]==a));
            return 1;

    }
    return 0;
}


double executeLK(int **tab,int n)
{
int m =((n*(n-1))+1)/2;

    int *losowa=new int[n];
    for (int i=0;i<n;i++)
      {
       losowa[i]=i;
      }
      shuffle(losowa,n);
      int liczba_krawedzi=0;
      int ile_par = m;
      StartCounter();
      for (int i=0;i<n;i++)
        {
        for (int j = 0; j<n;j++)
            {
         //   cout<<losowa[i]<<" "<<losowa[j]<<endl;
            liczba_krawedzi+=czy_posiada_krawedz(tab,losowa[i],losowa[j],ile_par);
            }
        }
        double czas= GetCounter();
     //   cout<<"liczba krawedzi: "<<liczba_krawedzi/2<<endl;
        return czas/(n*n);

}

void print_lista(int**tab,int n, double nasycenie)
{
    int m =((n*(n-1))/2)*nasycenie;
    for (int i=0;i<(m+1);i++)
    {
        cout<<tab[i][0]<<" -> "<<tab[i][1]<<endl;
    }
}


int main()
{

    srand(time(0));

   int **tab;

    data_batch data = readFromFile("dane.txt");
    const char* plik = "dane.txt";
    int **graf=new_empty(data.range+1);
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





 /*   for (int i = 0;i<n;i++)
    {
        for (int j =0;j<n;j++)
        {
            cout<<tab[i][j]<<" ";
        }
        cout<<endl;
    }
*/
    int **lista_krawedzi= L_kraw(graf,data.range);
    double czas = executeLK(lista_krawedzi,data.range);
    cout<< "czas szukania: "<<czas<<endl;

    int m=(data.range*(data.range-1))/2;

    for ( int i = 0 ; i < data.length ; i++)
        delete []lista_krawedzi[i];
    delete [] lista_krawedzi;
    delete[]tab;


    return 0;
}
