#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <time.h>
#include <random>
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


void shuffle(int *array, size_t n)
{
	for (int i = n - 1; i > 0; i--) {
		int t = rand() % (i + 1);
		int tmp = array[i];
		array[i] = array[t];
		array[t] = tmp;
	}
}

struct node{
	string imie;
	string nazwisko;
	int index;
	node *next;
};

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
	string* imiona;
	string* nazwiska;
	int* indeksy;
	int length;
};

data_batch readFromFile(const char* fileName){
	int n = countNumberOfLines("dane.txt");
	string* imiona = new string[n];
	string* nazwiska = new string[n];
	int* indeksy = new int[n];

	char* line=NULL;
	size_t read; size_t len;
	string delimiter = ";";
	FILE* fp;
	fp = fopen("dane.txt", "r");
	int i = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		string l = string(line);
		int pos = 0;
		pos = l.find(delimiter);
		imiona[i] = l.substr(0, pos);
		l.erase(0, pos + 1);
		pos = l.find(delimiter);
		nazwiska[i] = l.substr(0, pos);
		l.erase(0, pos + 1);
		indeksy[i] = stoi(l.substr(0, l.length() -1));
		i++;
    }
    fclose(fp);
    data_batch ret;
    ret.imiona = imiona;
    ret.nazwiska = nazwiska;
    ret.indeksy = indeksy;
    ret.length = n;
    return ret;
}

void dodaj(node *&head,string name,string nazwisk, int number) {
	if (!head || head->index > number) {
		node *p = new node;
		p->index = number;
		p->imie= name;
		p->nazwisko = nazwisk;
		p->next = head;
		head = p;
	}	//na pocz¹tku
	else {
		node* curr = head;
		while (curr->next) {
			if (curr->next->index > number) break;
			curr = curr->next;
		}
		node *p = new node;
		p->index = number;
		p->imie= name;
		p->nazwisko = nazwisk;
		p->next = curr->next;
		curr->next = p;
	}	//w œrodku lub na koñcu
}

node* createList(data_batch data) {
	node* head = NULL;
	for(int i=0; i < data.length; i++) {
    dodaj(head,data.imiona[i],data.nazwiska[i],data.indeksy[i]);
	}
	//delete[] data.imiona;
	//delete[] data.indeksy;
	//delete[] data.nazwiska;

	return head;
}



bool isEmpty(node *head)
{
    if (head == NULL)//sprawdz czy lista jest pusta
       return true;
    else
        return false;
}


char menu()
{
    char wybor;

    cout<< "MENU"<<endl;
    cout<<"1. dodaj element"<<endl;
    cout<<"2. usun element"<<endl;
    cout<<"3. pokaz liste"<<endl;
    cout<<"4. wyjdz"<<endl;

    cin >> wybor;
    return wybor;
}

node* wyszukaj(node* current, int ind) {
	while(current != NULL){
		if(current -> index == ind)
			return current;
		current = current->next;
	}
}

void usun(node *&head, int ind) {
	if (head -> index == ind){
		head = head -> next;
		return;
	}
	node* current = head;
	while(current != NULL){
		if (current -> next -> index == ind){
			node* temp = current->next;
			current -> next = current -> next -> next;
			delete temp;
			return;
		}
		current = current -> next;
	}
}

void usun_liste(node* head){
    if (head -> next){
        node* current = head->next;
        delete head;
        usun_liste(current);
    }
    return;
}

void pokaz_liste(node *current)
{
    if(isEmpty(current))
        cout<<"lista jest pusta"<<endl;
    else
    {
        cout<<"lista zawiera: "<<endl;
        while(current != NULL)
        {
            cout << current->imie << " " << current->nazwisko << " " << current -> index << endl;
            current = current -> next;
        }
    }
}


int main(){
    //-----------------Tworzenie losowej kolejnosci indeksow --------------------------------


    int liczba_elementow = countNumberOfLines("dane.txt");
    data_batch data = readFromFile("dane.txt");
    int *losowa;
    losowa = new int[liczba_elementow];
 //

    for (int i=0;i<liczba_elementow;i++){
        losowa[i]=data.indeksy[i];
    }
    shuffle(losowa,liczba_elementow);

    //----------------------TWORZENIE LISTY-----------------------------------------------------


    const char * plik = "dane.txt";
	StartCounter();
	node* head = createList(readFromFile(plik));
    double czas = GetCounter();
    cout <<"czas tworzenia listy dla " << liczba_elementow<<" elementow wynosi: "<< (double)czas<<endl;
    //---------------------sredni czas szukania elementu w liscie ------------------

    StartCounter();
    for (int i=0;i<liczba_elementow;i++)
    {
        wyszukaj(head, losowa[i]);
    }
    czas = GetCounter();
    cout<<"czas szukania wszystkich elementow w kolejnosci losowej dla listy posortowanej "<<liczba_elementow<<" elementow wynosi: " << czas/(double)liczba_elementow<<endl;

    //-----------------------------------USUWANIE LISTY--------------------------
    StartCounter();
    for (int i=0;i<liczba_elementow;i++)
    {
        usun(head, losowa[i]);
    }
    czas=GetCounter();
    cout<<"czas usuwania wszystkich elementow w kolejnosci losowej dla listy posortowanej "<<liczba_elementow<<" elementow wynosi: " << czas<<endl;

    //delete[] losowa;
    //
    }

     char wybor;
     string imie;
     string nazwisko;
     int index;

    do{
       wybor = menu();
         switch(wybor)
        {
             case '1': cout<< "podaj imie: ";
                       cin >> imie;
                       cin>>nazwisko;
                       cin>>index;
                       dodaj(head,imie,nazwisko,index);
                       break;
             case '2':cout<<"podaj index: ";
                      int indeks;
                      cin>>indeks;
                      usun(head,indeks);
                         break;
             case '3': pokaz_liste(head);
                         break;
             default:  cout<< "zamykanie programu"<<endl;
         }
     }while(wybor != '4');


   /* fstream zapis;

    zapis.open("wyniki.txt", ios::out | ios::app);
    if(zapis.good() == true)
    {
        zapis<<liczba_elementow<<endl;
        zapis<<"T S U "<<suma_tworzenia/licznik<<"\t"<<suma_szukania/licznik<<"\t"<<suma_usuwania/licznik<<"\t"<<endl;
        zapis.close();
    }
*/




return 0;
}
