#include <random>
#include <iostream>
#include <time.h>
#include <windows.h>

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


void quickSort(int *arr, int left, int right);

void print_arr(int*array,int n)
{
    for ( int i =0;i<n;i++)
    {
        cout<<array[i]<<" ";
    }
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


void new_A(int ile,int *tablicaA)
{
    for (int i=0;i<=ile/2;i++)
    {
        tablicaA[i]=i*2+1;
        tablicaA[ile-i]=(i*2);
    }
}

void new_V(int n,int *tablicaV)
{
    if (!(n%2))
    {
        for (int i = 0; i < (int) n/2; i++)
        {
            tablicaV[i] = n-2*i;
        }
        for(int i = (int)n/2; i<n; i++)
        {
            tablicaV[i] = 1 + 2*(i- (int)(n/2));
        }
    }
    else
    {
        for (int i = 0; i <= (int) n/2; i++)
        {
            tablicaV[i] = n-2*i;
        }
        for(int i = (int)n/2+1; i<n; i++)
        {
            tablicaV[i] =  2*(i-(int)(n/2));
        }
    }
}


void new_random(int ile,int *tablica_random)
{
    for (int i =0;i<ile;i++)
    {
        tablica_random[i]=i+1;
    }
    shuffle(tablica_random,ile);
}


void test1()
{
    int* tablica=new int[100];
    new_random(100,tablica);
    for (int i=0;i<100;i++)
    {
        cout<<tablica[i]<<" ";
    }
    quickSort(tablica,0,99);
    cout<<endl;
    for (int i=0;i<100;i++)
    {
        cout<<tablica[i]<<" ";
    }
}

void test2()
{
double czas;
    for (int n = 99999; n <=100001;n++)
    {
		int *tablicaA = new int [n];
		int *tablicaV = new int [n];
		int *tablica_random = new int [n];
        cout<<"-----"<<n<<"-----"<<endl;
        new_A(n,tablicaA);
        StartCounter();
        quickSort(tablicaA,0,n-1);
        czas=GetCounter();
        cout<<"A: " <<czas<<endl;


        new_V(n,tablicaV);
        StartCounter();
        quickSort(tablicaV,0,n-1);
        czas=GetCounter();
        cout<<"V: " <<czas<<endl;


        new_random(n,tablica_random);
        StartCounter();
        quickSort(tablica_random,0,n-1);
        czas=GetCounter();
        cout<<"random: " <<czas<<endl;

    }
}

int main()
{
    srand(time(NULL));
 //   test1();
   test2();
/*
 int *tablicaA=new int[30];
 new_A(30,tablica);
 quickSort(tablica,0,30);
 cout<<endl<<endl;

 int *tablicaV=new int[30];
 new_V(30,tablicaV);
 quickSort(tablicaV,0,29);
*/
 return 0;
}




void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void quickSort(int *arr, int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

    //  cout<<endl<<pivot<<endl;
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  swap(&arr[j],&arr[i]);
                  i++;
                  j--;
            }
      };

      if (left < j)
      {
      //  cout<<endl;
      //  print_arr(arr,j+1);
        quickSort(arr, left, j);
      }

      if (i < right)
      {
      //  cout<<endl;
    //    print_arr(arr,right+1);
        quickSort(arr, i, right);
      }

}

