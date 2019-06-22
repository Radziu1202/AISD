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




void print_matrix(int**K, int n, int n1)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            cout<<K[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

struct item
{
    int waga;
    int wartosc;
};

struct item* tab_itemy(int n)
{
    struct item *tablica_itemow=new struct item[n];
    for (int i = 0; i < n; i++)
    {
        struct item IT;
        IT.waga=rand() % 100 + 1;
        IT.wartosc=rand() % 100 + 1;
        tablica_itemow[i]=IT;

    }
    return tablica_itemow;
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
    cout<<"Dynamic numery Przedmiotow: ";
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
            cout<<M<<" ";
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

//-------------------BRUTE FORCE----------------

bool check_candidate(vector<struct item> candidate,int b)
{
    int whole_weight=0;
    for (int i=0; i<candidate.size(); i++)
    {
        whole_weight+=candidate[i].waga;
    }
    if (whole_weight<=b)
        return true;
    return false;
}

int evalue_candidate(vector<struct item> candidate)
{
    int whole_value=0;
    for (int i =0; i<candidate.size(); i++)
    {
        whole_value+=candidate[i].wartosc;
    }
    return whole_value;
}
vector<struct item> gen_solution(struct item* items, int n, int N)
{
    vector<struct item> solution_vec;
    int k;
    for(int i = 0; i < N; i++)
    {
        k = pow(2,i);
        if(n & k)
        {
            solution_vec.push_back(items[i]);
        }
    }
    /*
    	cout<< "--------" <<  n <<endl;
    	for(int i=0;i< solution_vec.size();i++)
    		cout << solution_vec[i] << " ";
    	cout << endl;
    	*/
    return solution_vec;
}

int brute_force(struct item* items, int n,int b)
{
    int pn = (int) pow(2, n);
    int maksymalna=0;
    vector<struct item>best_combination;
    vector<struct item>candidate;
    for(int i = 0; i < pn; i++)
    {
        candidate=gen_solution(items, i, n);
        if (check_candidate(candidate,b))
        {
            int temp=evalue_candidate(candidate);
            if(temp>maksymalna)
            {
                maksymalna=temp;
                best_combination=candidate;
            }
        }
    }
    cout <<"wartosci BF: ";
    for(int i=0; i< best_combination.size(); i++)
    {
        cout << best_combination[i].wartosc << " ";
    }
    cout<<endl<<"wagi BF: ";
    for(int i=0; i< best_combination.size(); i++)
    {
        cout << best_combination[i].waga << " ";
    }
    cout << endl;
    return maksymalna;
}

void execute_b(int b)
{
    double suma_wynikow_dynamic=0.0,suma_wynikow_greedy=0.0;
    double suma_czasow_greedy=0.0,suma_czasow_dynamic=0.0;
    double suma_czasow_BF=0.0;
    fstream zapis;
    for (int n=1000;n<100000; n+=8000)
    {
        cout<<n<<endl;
        for (int j =0; j<15; j++)
        {
            struct item* itemy=tab_itemy(n);
            int** K = new_matrix(n,b);
            StartCounter();
            int wynik_dynamic = dynamic(K, b,itemy, n);
            suma_czasow_dynamic+=GetCounter();
            cout<<"dynamic wartosc: "<<wynik_dynamic<<endl;
            suma_wynikow_dynamic+=wynik_dynamic;
            for (int i =0;i<n;i++)
                delete K[i];
            delete[] K;
        //     StartCounter();
           //  int wynik=brute_force(itemy,n,b);
            // suma_czasow_BF+=GetCounter();
             // cout<<"BF wartosc "<<wynik<<endl<<endl<<endl;
           double **part=new_part(n);
            StartCounter();
            int wynik_greedy = greedy(part, b, itemy, n);
            suma_czasow_greedy+=GetCounter();
            suma_wynikow_greedy+=wynik_greedy;
            cout<<"Greedy wartosc: "<< wynik_greedy<<endl<<endl<<endl<<endl;

            for (int i=0;i<3;i++)
            {
                delete part[i];
            }
            delete []part;
        }
         zapis.open("wyniki Knapsack.txt", ios::out | ios::app);
        if(zapis.good() == true)
        {
            zapis<<suma_czasow_dynamic/15.0<<"\t"<<suma_czasow_greedy/15.0<<"\t"<<"wyniki dynamic:\t"<<suma_wynikow_dynamic/15.0<<"wyniki greedy:\t"<<suma_wynikow_greedy/15.0<<"\t"<<n <<endl;

            zapis.close();
        }
        suma_czasow_dynamic=0.0;
        suma_czasow_greedy=0.0;
        suma_wynikow_dynamic=0.0;
        suma_wynikow_greedy=0.0;
    }
}

void execute_n(int n)
{
    double suma_wynikow_dynamic=0.0,suma_wynikow_greedy=0.0;
    double suma_czasow_greedy=0.0,suma_czasow_dynamic=0.0;
    fstream zapis;
    for (int b=100;b<2000; b+=100)
    {
        cout<<b<<endl;
        for (int j =0; j<15; j++)
        {
            struct item* itemy=tab_itemy(n);
            int** K = new_matrix(n,b);
            StartCounter();
            int wynik_dynamic = dynamic(K, b,itemy, n);
            suma_czasow_dynamic+=GetCounter();
            cout<<"dynamic wartosc: "<<wynik_dynamic<<endl;
            suma_wynikow_dynamic+=wynik_dynamic;
            for (int i =0;i<n;i++)
                delete K[i];
            delete[] K;
            double **part=new_part(n);
            StartCounter();
            int wynik_greedy = greedy(part, b, itemy, n);
            suma_czasow_greedy+=GetCounter();
            suma_wynikow_greedy+=wynik_greedy;
            cout<<"Greedy wartosc: "<< wynik_greedy<<endl<<endl<<endl<<endl;

            for (int i=0;i<3;i++)
            {
                delete part[i];
            }
            delete []part;
        }
         zapis.open("wyniki Knapsack.txt", ios::out | ios::app);
        if(zapis.good() == true)
        {
            zapis<<suma_czasow_dynamic/15.0<<"\t"<<suma_czasow_greedy/15.0<<"\t"<<"wyniki dynamic:\t"<<suma_wynikow_dynamic/15.0<<"wyniki greedy:\t"<<suma_wynikow_greedy/15.0<<"\t"<<n <<endl;

            zapis.close();
        }
        suma_czasow_dynamic=0.0;
        suma_czasow_greedy=0.0;
        suma_wynikow_dynamic=0.0;
        suma_wynikow_greedy=0.0;
    }
}

void test(int b)
{
    int n=5;
    struct item *itemy= new item[n];
    struct item IT;
    IT.waga=4;
    IT.wartosc=3;
    itemy[0]=IT;

    IT.waga=1;
    IT.wartosc=5;
    itemy[1]=IT;

    IT.waga=4;
    IT.wartosc=2;
    itemy[2]=IT;

    IT.waga=3;
    IT.wartosc=7;
    itemy[3]=IT;

    IT.waga=12;
    IT.wartosc=42;
    itemy[4]=IT;


    int** K = new_matrix(n,b);
    dynamic(K, b,itemy, n);
    double **part=new_part(n);
    cout<<endl<<"Wartosc greedy: "<<greedy(part,b,itemy,n);
}

int main()
{
    srand(time(NULL));
  //  test(12);
    int b,n=20;
    struct item *itemy=tab_itemy(n);
       StartCounter();
             int wynik=brute_force(itemy,n,b);
             cout<<GetCounter()<<endl;;

  //  b= 80;
  //  execute_b(b);
  // int n =50;
   // execute_n(n);

    return 0;
}
