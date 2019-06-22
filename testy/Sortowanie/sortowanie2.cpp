

#include <random>
#include <iostream>
#include <time.h>
#include <windows.h>

clock_t start,stop;
double czas;
int ile;

using namespace std;
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


int*new_A(int ile)
{
   int *tablicaA = new int[ile];
    for (int i=0;i<=ile/2;i++)
    {
        tablicaA[i]=i*2+1;
        tablicaA[ile-i]=(i*2);
    }
    return tablicaA;
}

int *new_V(int ile)
{
    cout<<"siema";
    int *tablicaV=new int[ile];
    cout<<"nara";
    if (!(ile%2))
    {
        for (int i = 0; i < (int) ile/2; i++)
        {
            tablicaV[i] = ile-1-2*i;
        }
        for(int i = (int)ile/2; i<ile; i++)
        {
            tablicaV[i] = 2 + 2*(i- (int)(ile/2));
        }
    }
    else
    {
        for (int i = 0; i <= (int) ile/2; i++)
        {
            tablicaV[i] = ile-2*i;
        }
        for(int i = (int)ile/2+1; i<ile; i++)
        {
            tablicaV[i] =  2*(i-(int)(ile/2));
        }
    }


    return tablicaV;
}


int*new_random(int ile)
{
    int *tablica_random=new int[ile];
    for (int i =0;i<ile;i++)
    {
        tablica_random[i]=i+1;
    }
    shuffle(tablica_random,ile);
    return tablica_random;
}


void test1()
{
    int* tablica=new_random(100);
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


    for (int n=99999;n<=100001;n++)
    {

        cout<<"-----"<<n<<"-----"<<endl;
        int *tablicaA=new_A(n);
        start= clock();
        quickSort(tablicaA,0,n-1);
        stop=clock();
        czas=(double)(stop-start)/CLOCKS_PER_SEC;
        cout<<"A: " <<czas<<endl;


        int *tablicaV=new_V(n);
        start= clock();
        quickSort(tablicaV,0,n-1);
        stop=clock();
        czas=(double)(stop-start)/CLOCKS_PER_SEC;
        cout<<"V: " <<czas<<endl;



        int *tablica_random=new_random(n);
        start= clock();
        quickSort(tablica_random,0,n-1);
        stop=clock();
        czas=(double)(stop-start)/CLOCKS_PER_SEC;
        cout<<"random: " <<czas<<endl;


    }
}

int main()
{
   // test1();
    test2();
    int *tablica=new_V(10);
    print_arr(tablica,10);
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
    //    cout<<endl;
    //    print_arr(arr,j+1);
        quickSort(arr, left, j);
      }

      if (i < right)
      {
     //   cout<<endl;
     //   print_arr(arr,right+1);
        quickSort(arr, i, right);
      }

}

