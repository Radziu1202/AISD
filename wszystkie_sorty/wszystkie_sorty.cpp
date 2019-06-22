#include <random>
#include <iostream>
#include <time.h>
#include <windows.h>

clock_t start,stop;
long double czas;
int ile;

using namespace std;
void quickSort(int *arr, int left, int right);
void sortowanie_babelkowe(int *tab,int n);
void insertionSort(int *arr, int n);
void shellSort(int *arr, int n);
void selectionSort(int *arr, int n);
void heapSort(int *arr, int n);
void countingSort(int *arr,int zakres,int n);
void mergeSort(int *arr, int low, int high);

int main()
{
    int tablica[9]={45,56,11,47,92,20,8,61,39};
    heapSort(tablica,9);
    // shellSort(tablica,12);

    /*
    //TWORZENIE TABLICY


    cout<<"ile elementow w tablicy"<<endl;
    cin>>ile;
    int *tablica;
    tablica = new int[ile];

    int zakres;
    cout<<"podaj zakres od 0 do:";
    cin>>zakres;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1,zakres);
for (int i=0;i<ile;i++){
        int losowa = distribution(generator);
        tablica[i]= losowa;
    }

    int *tablica_QS;
    tablica_QS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_QS[i]=tablica[i];
        cout<<tablica_QS[i]<<" ";
    }

    start= clock();
    quickSort(tablica_QS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania quick sort: " <<czas<<endl;
     for (int i=0;i<ile;i++){
        cout<<tablica_QS[i]<<" ";
    }
    delete [] tablica_QS;

   /* int *tablica_BS;
    tablica_BS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_BS[i]=tablica[i];
    }
    start= clock();
    sortowanie_babelkowe(tablica_BS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania babelkowego: "<<czas<<endl;
    delete [] tablica_BS;

    int *tablica_InsS;
    tablica_InsS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_InsS[i]=tablica[i];
    }
    start= clock();
    insertionSort(tablica_InsS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas insertionSort: "<<czas<<endl;
    delete [] tablica_InsS;

    int *tablica_ShS;
    tablica_ShS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_ShS[i]=tablica[i];
    }
    start= clock();
    shellSort(tablica_ShS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania shell sort: "<<czas<<endl;
    delete [] tablica_ShS;
*/




    /*int *tablica_SS;
    tablica_SS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_SS[i]=tablica[i];
    }
    start= clock();
    selectionSort(tablica_SS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas selection sort: "<<czas<<endl;
    delete [] tablica_SS;

    int *tablica_HS;
    tablica_HS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_HS[i]=tablica[i];
    }
    start= clock();
    heapSort(tablica_HS,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania heap sort: "<<czas<<endl;
    delete [] tablica_HS;

    int *tablica_CS;
    tablica_CS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_CS[i]=tablica[i];
    }

    start= clock();
    countingSort(tablica_CS,zakres,ile);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania counting sort: " <<czas<<endl;
    delete [] tablica_CS;

    int *tablica_MS;
    tablica_MS = new int[ile];
    for (int i=0;i<ile;i++){
        tablica_MS[i]=tablica[i];
    }
    delete [] tablica;
    start= clock();
    mergeSort(tablica_MS,0, (ile-1));
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"czas sortowania merge sort: " <<czas<<endl;
    delete [] tablica_MS;*/
    return 0;
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


//QUICK SORT
void quickSort(int *arr, int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

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
            quickSort(arr, left, j);
      if (i < right)
            quickSort(arr, i, right);
}



//BUBBLE SORT

void sortowanie_babelkowe(int *arr,int n)
{
   int i, j,counter=0;
   for (i = 0; i < n-1; i++)
  {

       // Last i elements are already in place
       for (j = 0; j < n-i-1; j++)
       {
           counter++;
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
       }
  }
  cout<<"counter: "<<counter;
}

//COUNTING SORT

void countingSort(int* lista, int zakres_do, int n){
  int dlugosc = zakres_do + 1;
  int *zlicz;
  zlicz = new int[dlugosc];
  for(int i = 0; i < dlugosc; i++)
    zlicz[i] = 0;
  for(int i = 0; i < n; i++)
    zlicz[lista[i]]++;
  int x = 0;
  for(int i = 0; i < dlugosc; i++)
    for(int j = 0; j < zlicz[i]; j++)
      lista[x++] = i;
}


//INSERTION SORT

void insertionSort(int *arr, int n)
{
   int i, zastepcza, j;
   for (i = 1; i < n; i++)
   {
       zastepcza = arr[i];
       j = i-1;


       while (j >= 0 && arr[j] > zastepcza)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = zastepcza;
   }
}


// SHELL SORT

void shellSort(int *arr, int n)
{
//zaczynamy z możliwie jak najwiekszym gap i potem go zmniejszamy dwukrotnie
    for (int gap = 4; gap >1; gap/=2)

    {//zaczynamy od elementu o indeksie równym gap
        for (int i = gap; i < n; i++)
        {//porównujemy wyrazy
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
                }
            arr[j] = temp;
        }
        for (int i=0;i<n;i++)
    {

        cout<<arr[i]<<" ";
    }
    cout<<endl;
    }

}


//SELECTION SORT


void selectionSort(int *arr, int n)
{
    int i, j, min_idx;

    // sprawdzaj po kolei kazdy wyraz zeby znalezc najmniejszy
    for (i = 0; i < n-1; i++)
    {
        // znajdz najmniejszy element w tablicy
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        swap(&arr[min_idx], &arr[i]);
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
    // przekształć tablice na stog
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i =0;i<n;i++)
        cout<<arr[i]<<" ";
    // wyciągaj elementy z drzewa
    for (int i=n-1; i>=0; i--)
    {
        // przenieś korzeń na koniec
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
    /* stworz podtablice */
    L=new int[n1];
    R=new int[n2];

    /* skopiuj odpowiednie elementy do tablicy L i R (lewej i prawej) */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
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

    /* skopiuj pozostałe elementy L jesli jakies zostały*/
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* skopiuj pozostałe elementy R jesli jakies zostały */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
  delete []R;
  delete []L;
}

/* l to pierwszy index a r ostatni */
void mergeSort(int *arr, int l, int r)
{
    if (l < r)
    {

        int m = l+(r-l)/2;

        // sortowanie pierwszej połowy i drugiej
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
