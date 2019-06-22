#include <random>
#include <iostream>
#include <time.h>
#include <windows.h>

clock_t start,stop;
double czas;
int ile;

using namespace std;
void quickSort(int *arr, int left, int right,int &counter);
void heapSort(int *arr, int n);
void mergeSort(int *arr, int low, int high);

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
        tablicaA[i]=(i+1)*2;
        tablicaA[ile-i-1]=(i*2)+1;
    }
    return tablicaA;
}
int *new_V(int ile)
{

    int *tablicaV=new int[ile];
    if (!(ile%2))
    {
        for (int i = 0; i < (int) ile/2; i++)
        {
            tablicaV[i] = ile-2-2*i;
        }
        for(int i = (int)ile/2; i<ile; i++)
        {
            tablicaV[i] = 1 + 2*(i- (int)(ile/2));
        }
    }
    else
    {
        for (int i = 0; i < (int) ile/2; i++)
        {
            tablicaV[i] = ile-2-2*i;
        }
        for(int i = (int)ile/2; i<ile; i++)
        {
            tablicaV[i] =  2*(i- (int)(ile/2));
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

void test()
{   int counter=0;
    cout<<"ile elementow w tablicy A: "<<endl;
    cin>>ile;
    int *tablicaA=new_A(ile);

    start= clock();
    quickSort(tablicaA,0,ile-1,counter);
    stop=clock();
    cout<<counter<<endl;
    counter=0;
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"A: " <<czas<<endl;
    delete []tablicaA;

    cout<<"ile elementow w tablicy V: "<<endl;
    cin>>ile;
    int *tablicaV=new_V(ile);



    start= clock();
    quickSort(tablicaV,0,ile-1,counter);
    stop=clock();
    cout<<counter<<endl;
    counter=0;
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"V: " <<czas<<endl;
    delete []tablicaV;

    cout<<"ile elementow w tablicy losowej "<<endl;
    cin>>ile;
    int *tablica_random=new_random(ile);
    start= clock();
    quickSort(tablica_random,0,ile-1,counter);
    stop=clock();
    cout<<counter<<endl;
    counter=0;
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"random: " <<czas<<endl;
    delete []tablica_random;
}
int main()
{
    //TWORZENIE TABLICY

    test();
/*
    cout<<"ile elementow w tablicach rosnacych: "<<endl;
    cin>>ile;

    int *tablica,*tablica_rosnacaQS;
    tablica = new int[ile];
    tablica_rosnacaQS = new int[ile];

    for (int i=0;i<ile;i++){
    tablica[i]=i+1;
    }

    //KOPIOWANIE TABLIC DLA TOZNYCH SORTÓW
     for (int i=0;i<ile;i++){
        tablica_rosnacaQS[i]=tablica[i];
     }


    start= clock();
    quickSort(tablica_rosnacaQS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania quick sort dla tablicy rosnacej: " <<czas<<endl;
    delete [] tablica_rosnacaQS;

    int * tablica_rosnacaHS;
    tablica_rosnacaHS = new int[ile];
    for (int i=0;i<ile;i++){
    tablica_rosnacaHS[i]=tablica[i];
    }

    start= clock();
    heapSort(tablica_rosnacaHS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania heap sort dla tablicy rosnacej: "<<czas<<endl;
    delete [] tablica_rosnacaHS;

    int * tablica_rosnacaMS;
    tablica_rosnacaMS = new int[ile];
    for (int i=0;i<ile;i++){
    tablica_rosnacaMS[i]=tablica[i];
    }

    delete [] tablica;
    start= clock();
    mergeSort(tablica_rosnacaMS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania merge sort dla tablicy rosnacej: " <<czas<<endl;
    delete [] tablica_rosnacaMS;



    //MALEJACE
    cout<<"ile elementow w tablicach malejacych: "<<endl;
    cin>>ile;
    tablica = new int[ile];
    for (int i=0;i<ile;i++){
    tablica[i]=ile-i;
    }

    int *tablica_malejacaQS;
    tablica_malejacaQS = new int[ile];

    for (int i=0;i<ile;i++){
        tablica_malejacaQS[i]=tablica[i];
     }

    start= clock();
    quickSort(tablica_malejacaQS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania quick sort dla tablicy malejacej: " <<czas<<endl;
    delete [] tablica_malejacaQS;

    int *tablica_malejacaHS;
    tablica_malejacaHS = new int[ile];

    for (int i=0;i<ile;i++){
        tablica_malejacaHS[i]=tablica[i];
     }

    start= clock();
    heapSort(tablica_malejacaHS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania heap sort dla tablicy malejacej: "<<czas<<endl;
    delete [] tablica_malejacaHS;

    int *tablica_malejacaMS;
    tablica_malejacaMS = new int[ile];

    for (int i=0;i<ile;i++){
        tablica_malejacaMS[i]=tablica[i];
     }
    delete [] tablica;

    start= clock();
    mergeSort(tablica_malejacaMS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania merge sort dla tablicy malejacej: " <<czas<<endl;
    delete [] tablica_malejacaMS;



    //STALE

    cout<<"ile elementow w tablicach stalych: "<<endl;
    cin>>ile;
    tablica = new int[ile];

    for (int i=0;i<ile;i++){
    tablica[i]=1;
    }
    int *tablica_stalaQS;
    tablica_stalaQS = new int[ile];

    for (int i=0;i<ile;i++){
        tablica_stalaQS[i]=tablica[i];
     }


    start= clock();
    quickSort(tablica_stalaQS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania quick sort dla tablicy stalej: " <<czas<<endl;
    delete [] tablica_stalaQS;

    int *tablica_stalaHS;
    tablica_stalaHS = new int[ile];

    for (int i=0;i<ile;i++){
        tablica_stalaHS[i]=tablica[i];
     }

    start= clock();
    heapSort(tablica_stalaHS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania heap sort dla tablicy stalej: "<<czas<<endl;
    delete [] tablica_stalaHS;

    int *tablica_stalaMS;
    tablica_stalaMS = new int[ile];

    for (int i=0;i<ile;i++){
        tablica_stalaMS[i]=tablica[i];
     }

    start= clock();
    mergeSort(tablica_stalaMS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania merge sort dla tablicy stalej: " <<czas<<endl;
    delete [] tablica_stalaMS;

int counter=0;
    //ROSNACO-MALEJACE
    cout<<"ile elementow w tablicach rosnaco-malejacych: "<<endl;
    cin>>ile;
    int *tablica = new int[ile];

    for (int i=0;i<=ile/2;i++){
        tablica[i]=(i+1)*2;
        tablica[ile-i-1]=(i*2)+1;

    }

    cout<<"siema"<<endl;

    int *tablica_rosmalQS;
    tablica_rosmalQS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_rosmalQS[i]=tablica[i];
     }



    start= clock();
    quickSort(tablica_rosmalQS,0, (ile-1),counter);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania quick sort dla tablicy rosnaco - malejacej: " <<czas<<endl;
    delete [] tablica_rosmalQS;

    cout<<counter<<endl;
    counter=0;

    int *tablica_rosmalHS;
    tablica_rosmalHS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_rosmalHS[i]=tablica[i];
     }



    start= clock();
    heapSort(tablica_rosmalHS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania heap sort dla tablicy rosnaco - malejacej: "<<czas<<endl;
    delete [] tablica_rosmalHS;

    int *tablica_rosmalMS;
    tablica_rosmalMS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_rosmalMS[i]=tablica[i];
     }
    delete [] tablica;



    start= clock();
    mergeSort(tablica_rosmalMS,0,(ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania merge sort dla tablicy rosnaco - malejacej: " <<czas<<endl;
    delete [] tablica_rosmalMS;


    //MALEJACO - ROSNACE
    cout<<"ile elementow w tablicach malejaco - rosnacych: "<<endl;
    cin>>ile;
    tablica = new int[ile];

if (ile%2){
    for (int i=0;i<=ile/2;i++){
    tablica[i]=2*(ile-i);
    tablica[ile-i]=2*(ile-i)+1;
  }
}
else{
    for (int i=0;i<=ile/2;i++){
        tablica[i]=2*(ile-i);
        tablica[ile-i-1]=2*(ile-i)+1;
    }
}


    for(int i =0;i<ile;i++)
    {
        cout<<tablica[i]<<" ";
    }
    int *tablica_malrosQS;
    tablica_malrosQS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_malrosQS[i]=tablica[i];
     }

    start= clock();
    quickSort(tablica_malrosQS,0, (ile-1),counter);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania quick sort dla tablicy malejaco rosnacej: " <<czas<<endl;
    delete [] tablica_malrosQS;

    cout<<counter<<endl;
    counter=0;
    int *tablica_malrosHS;
    tablica_malrosHS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_malrosHS[i]=tablica[i];
     }


    start= clock();
    heapSort(tablica_malrosHS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania heap sort dla tablicy malejaco rosnacej: "<<czas<<endl;
    delete [] tablica_malrosHS;

    int *tablica_malrosMS;
    tablica_malrosMS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_malrosMS[i]=tablica[i];
     }
    delete [] tablica;

    start= clock();
    mergeSort(tablica_malrosMS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania merge sort dla tablicy malejaco rosnacej: " <<czas<<endl;
    delete [] tablica_malrosMS;





*/

    return 0;
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


//QUICK SORT
void quickSort(int *arr, int left, int right,int &counter) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

    //  cout<<pivot<<endl;
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
            quickSort(arr, left, j,counter);
      }
      if (i < right)
      {
            quickSort(arr, i, right,counter);
      }
}


//HEAP SORT

void heapify(int *arr, int n, int i)
{
    int najwiekszy = i; // wez  wyraz jako ojciec
    int l = 2*i + 1; // index lewego bedzie 2 razy wiekszy +1
    int r = 2*i + 2; // prawego 2 razy wiekszy +2

    // sprawdz czy lewy syn jest wiekszy od ojca
    if (l < n && arr[l] > arr[najwiekszy])
        najwiekszy = l;

    // sprawdz czy prawy syn jest wiekszy od ojca
    if (r < n && arr[r] > arr[najwiekszy])
        najwiekszy = r;

    // gdy korzeniem nie jest najwieksza liczba to wykonaj heapify
    if (najwiekszy != i)
    {
        swap(arr[i], arr[najwiekszy]);

        // wywolanie rekurencji heapify
        heapify(arr, n, najwiekszy);
    }
}

void heapSort(int *arr, int n)
{
    // przekszta³æ tablice na stog
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // wyciagaj elementy z drzewa
    for (int i=n-1; i>=0; i--)
    {
        // przenieœ korzeñ na koniec
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

void merge(int *arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int *L,*R;
    /* tworzenie nowych podtablic */
    L=new int[n1],
    R=new int[n2];

    /* kopiowanie danych do L i R */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];


    i = 0; //inicjalizacja indexu pierwszej podtablicy
    j = 0; // -||- drugiej podtablicy
    k = l; // inicjalizacja indexu tablicy powstałej po funkcji merge
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* skopiuj pozostale elementy L */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* skopiuj pozostale elementy R */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
  delete []R;
  delete []L;
}

/*l lewy index,r prawy index */
void mergeSort(int *arr, int l, int r)
{
    if (l < r)
    {

        int m = l+(r-l)/2;

        // sortuje pierwsza i druga polowe
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
