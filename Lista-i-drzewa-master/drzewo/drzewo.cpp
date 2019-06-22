#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <time.h>
#include <random>
#include <stdio.h>
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

char menu()
{
    char wybor;

    cout<< "MENU"<<endl;
    cout<<"1. dodaj element"<<endl;
    cout<<"2. usun element"<<endl;
    cout<<"3. pokaz drzewo"<<endl;
    cout<<"4. wyjdz"<<endl;

    cin >> wybor;
    return wybor;
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
	ssize_t read; size_t len;
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




//-------------------DRZEWO BST----------------------------------------------

struct tree {
		int pole_index;
		string imie;
		string nazwisko;
		struct tree *left;
		struct tree *right;
	};

	tree *insert(tree *root, string imie,string nazwisko,int index) {
        if (!root) {
			tree *temp = new tree;
			temp->imie = imie;
			temp->nazwisko = nazwisko;
			temp-> pole_index = index;
			temp->left = NULL;
			temp->right = NULL;
			return temp;
        }
		if (root->pole_index > index) root->left = insert(root->left, imie,nazwisko,index);
		else if (root->pole_index < index) root->right = insert(root->right, imie,nazwisko,index);
		return root;
	}



	tree* createTree(data_batch data) {
	tree* root = NULL;
    shuffle(data.indeksy,data.length);
	for(int i=0; i < data.length; i++) {

        root = insert(root,data.imiona[i] ,data.nazwiska[i], data.indeksy[i]);

	}
	return root;

}




	tree *search(tree *root, int index) {
		tree *ptr = root;
		while (ptr) {
			if (index > ptr->pole_index) ptr = ptr->right;
			else if (index < ptr->pole_index) ptr = ptr->left;
			else break;
		}
		return ptr;
	}


	bool isEmpty(tree* root){
        if (root=NULL)
            return true;
        else
            return false;
	}

    void show_tree(tree *current){
        if (isEmpty(current))
            cout<<"drzewo jest puste";
        if(current->right) show_tree(current -> right);
        cout << current->imie << " "<< current->nazwisko<<" " << current->pole_index << endl;
        if(current-> left) show_tree(current -> left);
        return;
    }

    void print_tree_graph(tree* head){
    if(head->left) cout << head -> pole_index << "->" << head ->left->pole_index <<'\n';
    if(head->right) cout << head -> pole_index << "->" << head ->right->pole_index <<'\n';
    if(head->left) print_tree_graph(head->left);
    if(head->right)print_tree_graph(head->right);
    return;
}


	void del_tree(tree *root) {
		if (root) {
			del_tree(root->left);
			del_tree(root->right);
			delete root;
		}
	}


	tree* minValueNode(tree* node)
{
    tree* current = node;

    /* ZNAJDOWANIE LISCIA NAJBARDZIEJ NA LEWO */
    while (current->left != NULL)
        current = current->left;

    return current;
}


	tree* deleteNode(tree* root, int key )
{
    // GDY NIE MA NIC W DRZEWIE
    if (root == NULL) return root;

    // JESLI INDEX JEST MNIEJSZY NIZ INDEX KORZENIA TO WRZUCAJ NA LEWO
    if (key < root->pole_index)
        root->left = deleteNode(root->left, key);

    // JESLI INDEX JEST WIEKSZY NIZ INDEX KORZENIA TO WRZUCAJ NA PRAWO
    else if (key > root->pole_index)
        root->right = deleteNode(root->right, key);

    // JESLI INDEXY SA TAKIE SAME :
    else
    {
        // BEZ DZIECI LUB Z JEDNYM DZIECKIEM
        if (root->left == NULL)
        {
            tree *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            tree *temp = root->left;
            free(root);
            return temp;
        }

        // KORZEN Z DWÓJK¥ DZIEDZI POSEGREGUJ (NJMNIEJSZE W PRAWYM PODDRZEWIE)
        tree* temp = minValueNode(root->right);

        root->pole_index = temp->pole_index;


        root->right = deleteNode(root->right, temp->pole_index);
    }
    return root;
}


	//----------------Drzewo AVL----------------
tree *AVL(int *A, int l, int r) {
	int m = (l + r) / 2;
	tree *root = new tree;
	root->pole_index = A[m];
	root->left = NULL;
	root->right = NULL;
	if (m-1-l>=0) root->left = AVL(A, l, m-1);
	if (r-m-1>=0) root->right = AVL(A, m+1, r);
	return(root);
}


int main(){

    //---------------------------TWORZENIE LOSOWEJ KOLEJNOSCI--------------------------
    int liczba_elementow = countNumberOfLines("dane.txt");
    data_batch data = readFromFile("dane.txt");
    const char* plik = "dane.txt";
    int *losowa;
    losowa = new int[liczba_elementow];
  //
    double licznik=0;
    double suma_tworzenia=0;
    double suma_usuwania=0;
    double suma_szukania=0;
    double suma_szukaniaBBST=0;

  //  for (int j =0;j<50;j++){
//
  //   licznik++;
    for (int i=0;i<liczba_elementow;i++){
        losowa[i]=data.indeksy[i];
    }
    shuffle(losowa,liczba_elementow);



    //-------------------------CZAS TWORZENIA DRZEWA------------------------
    double czas;
    StartCounter();
    tree* root=createTree(readFromFile(plik));
    czas =GetCounter();
    suma_tworzenia+=czas;
    cout<<"tworzenie:  "<<liczba_elementow<< " elementow :  "<<czas <<endl;


    //--------------------------SREDNI CZAS SZUKANIA ELEMENT PO ELEMENCIE----------------

    StartCounter();
	for (int i=0;i<liczba_elementow;i++){
    search(root, losowa[i]);

    }
    czas =GetCounter();
    cout<<"szukanie "<<liczba_elementow<<" elementow : " << czas/(double)liczba_elementow<<endl;
    suma_szukania=(czas/(double)liczba_elementow);
  //  ----------------------------SREDNI CZAS USUWANIA ELEMENT PO ELEMENCIE---------

     StartCounter();
    for (int i=0;i<liczba_elementow;i++){
    deleteNode(root,losowa[i]);
    }
    czas =GetCounter();
    cout<<"usuwanie "<<liczba_elementow<<" elementow : " << czas<<endl;

    suma_usuwania=czas;
    show_tree(root);
    //---------------------TWORZENIE DRZEWA BBST-----------------------


    tree* rootAVL=AVL(data.indeksy,0,liczba_elementow-1);

    //------------------SREDNI CZAS SZUKANIA W BBST ELEMENT PO ELEMENCIE--------

     StartCounter();
	for (int i=0;i<liczba_elementow;i++)
        {
        search(rootAVL, losowa[i]);
        }
	czas =GetCounter();
    cout<<"szukanie dla BBST "<<liczba_elementow<<" elementow : " << czas/(double)liczba_elementow<<endl;
    suma_szukaniaBBST=(czas/(double)liczba_elementow);
    cout<<licznik<<endl;




char wybor;
     string imie;
     string nazwisko;
     int index;
    do{
       wybor = menu();
         switch(wybor)
        {
             case '1': cout<< "podaj imie nazwisko i indeks: ";
                       cin >> imie;
                       cin>>nazwisko;
                       cin>>index;
                       insert(root,imie,nazwisko,index);
                       break;
             case '2':cout<<"podaj index: ";
                      cin>>index;
                      deleteNode(root,index);
                         break;
             case '3': show_tree(root);
                         break;
             default:  cout<< "zamykanie programu"<<endl;
         }
     }while(wybor != '4');

/*fstream zapis;

    zapis.open("wyniki.txt", ios::out | ios::app);
    if(zapis.good() == true)
    {
        zapis<<liczba_elementow<<endl;
        zapis<<"  "<<suma_tworzenia/licznik<<"\t"<<suma_szukania/licznik<<"\t"<<suma_usuwania/licznik<<"\t"<<suma_szukaniaBBST/licznik<<endl;
        zapis.close();
    }
*/
     return 0;
}
