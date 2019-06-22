#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include <time.h>
#include <random>
#include <stdio.h>
#include <iostream>
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



	string line;
	size_t read; size_t len;
	string delimiter = ";";
	fstream fp;
	fp.open("dane.txt");
	int i = 0;
	while (getline(fp,line)) {
		string l = line;
		int pos = 0;
		pos = l.find(delimiter);
		imiona[i] = l.substr(0, pos);
		l.erase(0, pos + 1);
		pos = l.find(delimiter);
		nazwiska[i] = l.substr(0, pos);
		l.erase(0, pos + 1);
		stringstream geek(l);
		 int x = 0;
		 geek >> x;
		indeksy[i] = x;
		//cout<<indeksy[i]<<endl;
		i++;
    }
    fp.close();
    data_batch ret;
    ret.imiona = imiona;
    ret.nazwiska = nazwiska;
    ret.indeksy = indeksy;
    ret.length = n;
    return ret;
}

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



tree* createTree(data_batch data)
{
	tree* root = NULL;
 //   shuffle(data.indeksy,data.length);
	for(int i=0; i < data.length; i++) {

        root = insert(root,data.imiona[i] ,data.nazwiska[i], data.indeksy[i]);
   //     cout<<data.indeksy[i]<<endl;

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

        // KORZEN Z DWÓJKi DZIECI POSEGREGUJ (NAJMNIEJSZE W PRAWYM PODDRZEWIE)
        tree* temp = minValueNode(root->right);

        root->pole_index = temp->pole_index;


        root->right = deleteNode(root->right, temp->pole_index);
    }
    return root;
}


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

void DFS_inorder(struct tree* node)
{
    if (node == NULL)
        return;
    DFS_inorder(node->left);

    cout << node->pole_index << " ";

    DFS_inorder(node->right);
}

void DFS_preorder(struct tree* node)
{
    if (node == NULL)
        return;

    cout << node->pole_index << " ";
    DFS_preorder(node->left);
    DFS_preorder(node->right);
}
void DFS_postorder(struct tree* node)
{
    if (node == NULL)
        return;

    DFS_postorder(node->left);
    DFS_postorder(node->right);
    cout << node->pole_index << " ";

}


int main()
{
    int liczba_elementow = countNumberOfLines("dane.txt");
    data_batch data = readFromFile("dane.txt");
    const char* plik = "dane.txt";

    tree* root=createTree(readFromFile(plik));

    cout<<endl<<"in order: ";
    DFS_inorder(root);
    cout<<endl<<"DFS pre-order ";
    DFS_preorder(root);
    cout<<endl<<"DFS post-order ";
    DFS_postorder(root);

}
