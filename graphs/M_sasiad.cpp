#include <iostream>
#include <iomanip>
#include <random>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct node
{
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


void shuffle(int *array, size_t n)
{
    for (int i = n - 1; i > 0; i--)
    {
        int t = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[t];
        array[t] = tmp;
    }
}


int** generator(int n, double nasycenie)
{
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
    for (int i=0; i<nasycenie*((n*(n-1))/2); i++)
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


//-------------MACIERZ INCYDENCJI--------------------------------------


int** s2i(int **tab, int V, int E)
{
    int** big = new int*[V];
    for(int i=0; i<V; i++)
        big[i] = new int[E] {0};

    int curr_e = 0;
    for(int i = 0; i< V; i++)
    {
        for(int j = i; j<V; j++)
        {
            if (tab[i][j])
            {
                big[i][curr_e] = 1;
                big[j][curr_e] = 1;
                curr_e++;
            }
        }
    }
    return big;
}


//--funckje do szukania------------------------------------------
int czy_ma_krawedz(int **tab, int a, int b)
{
    //  cout<<tab[a][b]<<endl;
    return tab[a][b];
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

double executeMS(int **tab,int n)
{
    int *losowa=new int[n];
    for (int i=0; i<n; i++)
    {
        losowa[i]=i;
    }
    shuffle(losowa,n);
    int liczba_krawedzi=0;
    StartCounter();
    for (int i=0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
        {
            //   cout<<losowa[i]<<" "<<losowa[j]<<endl;
            liczba_krawedzi+=czy_ma_krawedz(tab,losowa[i],losowa[j]);
        }

    }

    double czas = GetCounter();
    cout<<"liczba krawedzi: "<<liczba_krawedzi/2<<endl;
    delete[]*tab;
    delete[]tab;
    return czas/(n*n);

}

int krawedz_w_inc(int **tab,int a,int b,int n)
{
    if(b==a)
        return 0;
    int m = (n*(n-1))/2;
    for (int i=0; i<m; i++)
    {
        if (tab[a][i]==1 && tab[b][i]==1)
            return 1;
    }
    return 0;
}

double executeM_INC(int** tab,int n,int m)
{
    int *losowa=new int[n];
    for (int i=0; i<n; i++)
    {
        losowa[i]=i;
    }
    shuffle(losowa,n);


    int liczba_krawedzi=0;

    StartCounter();
    for (int i =0 ; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            liczba_krawedzi+=krawedz_w_inc(tab,losowa[i],losowa[j],n);
        }
    }
    double czas=GetCounter();
    cout<<"liczba krawedzi: "<<liczba_krawedzi/2<<endl;
    delete []*tab;
    delete []tab;
    return czas/(n*n);
}

int main()
{

    srand(time(0));

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
    int n = data.range;

    int m=(n*(n-1))/2;


        cout<<endl;
    int **inc = s2i(graf,n,m);

        for (int i = 0 ; i<n;i++)
        {
            for (int j = 0 ; j<((0.6*m)+1);j++)
            {
                cout<<inc[i][j]<<" ";
            }
            cout<<endl;
        }


    double a=executeMS(graf,n);

    cout<<endl<<"czas MS "<<a<<endl;

    double b=executeM_INC(inc,n,m);
    cout<<endl<<"czas MI "<<b<<endl;

    for (int k = 0 ; k < n ; k++)
    {
        delete graf[k];
    }

    delete [] graf;
    // delete[] inc;






    return 0;
}




