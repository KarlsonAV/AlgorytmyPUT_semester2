#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

using namespace std;

typedef struct list {
    int val;
    struct list *next;
} list;

int c = 0;

void Adjacency_Matrix(int **AM, int n, int m) {
    int i, x, y;
    
    i = m;
    while (i) {
	x = rand()%n;
	y = rand()%n;
	if ( AM[x][y] != 1) {
	    AM[x][y] = 1;
	    i--;
	}
    }
}

void Adjacency_List(list **CL, int n, int **AM, list *last) {
    list *nowy;
    
    for(int x = 0; x < n; x++) { 
	for(int y = 0; y < n; y++) {
	    if (AM[x][y]) {
		if (CL[x] == NULL) {
		    CL[x] = new list;
		    last = CL[x]; 
		    last->val = y; 
		}
		else {
		    nowy = new list;
		    nowy->val = y;
		    last->next = nowy;
		    last = nowy;
		}
	    }
	}
    }
}

void Arc_List(int **VL, int **AM, int n) {
    int i = 0;
    
    for(int x = 0; x < n; x++) {
	for(int y = 0; y < n; y++) {
	    if(AM[x][y]) {
		VL[0][i] = x;
		VL[1][i] = y;
		i++;
	    }
	}
    }
}

void Topological_Sort(int *in, int *out, bool *visited, int n, int v, list **CL) {
	list *consequent = CL[v];
	
	visited[v] = 1; 
	in[v] = ++c;
	while (consequent != NULL) { 
		if (visited[consequent->val] == 0) 
		    Topological_Sort(in, out, visited, n, consequent->val, CL);
		consequent = consequent->next;
	}
	out[v] = ++c;
}


void Task(int n, float d) {

    int i, j, m, vertex_count;
    clock_t tStart;
    m = n*n*d;

    int **AM = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
	AM[i] = (int*) malloc(n * sizeof(int*));
    
    Adjacency_Matrix(AM, n, m);
    
    list **CL = new list*[n];
    list *last;
    
    Adjacency_List(CL, n, AM, last);
    
    int **VL = (int**) malloc (2 * sizeof(int*));
    VL[0] = (int*) malloc (m * sizeof(int*));
    VL[1] = (int*) malloc (m * sizeof(int*));
    
    Arc_List(VL, AM, n);
    
    bool *visited = new bool[n];
    int *in = new int[n];
    int *out = new int[n];
        

    tStart = clock();
    for (i = 0; i < n; i++)
	if (visited[i] == 0) 
	    Topological_Sort(in, out, visited, n, i, CL);

    printf("Czas obliczania etykiet czasowych - %.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    
    vertex_count = 0;
    tStart = clock();
    for (i = 0; i < m; i++) 
	if ((in[VL[1][i]] < in[VL[0][i]]) && (in[VL[0][i]] < out[VL[0][i]]) && (out[VL[0][i]] < out[VL[1][i]])) 
	    vertex_count++;

    printf("Czas zliczania łukow powrotnych dla listy lukow - %.3f\n",(double)(clock() - tStart) / CLOCKS_PER_SEC*1000);

    vertex_count = 0;
    tStart = clock();
    for(i = 0; i < n; i++) {
	last = CL[i];
	while(last != NULL) { 
	    if((in[last->val] < in[i]) && (in[i] < out[i]) && (out[i] < out[last->val]))
		vertex_count++; 
	    last = last->next;
	}
    } 
    printf("Czas zliczania łukow powrotnych dla listy następnikow - %.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    
    tStart = clock();
    vertex_count = 0;
    for(i = 0; i < n; i++) { 
	for(j = 0; j < n; j++) { 
	    if (AM[i][j] == 1) {
		if((in[j] < in[i]) && (in[i] < out[i]) && (out[i] < out[j]))
		     vertex_count++; 
	    }
	} 
    }

    printf("Czas zliczania łukow powrotnych dla macierzy sąsiedstwa - %.3f\n",(double)(clock() - tStart)/CLOCKS_PER_SEC*1000);
    printf("Liczba łukow powrotnych - %d\n", vertex_count);
    
    c = 0;
}

int main() {

    for (int n = 1000; n <= 10000; n += 1000) {
        cout << "----------\n----------" << endl;
        for (float d = 0.2; d < 0.5; d += d) {
            cout << "For n = " << n << ", d = " << d << endl;
            Task(n, d);
            cout << "----------\n----------" << endl;
        }
    }

    
}