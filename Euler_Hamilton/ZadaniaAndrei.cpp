#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int nr = 0, CH = 0, found = 0;
double timeUsed;
clock_t timeStart, timeEnd;


void nullify(int **AM, int n);
void dfs(int n, int v, bool* visited, int **AM);
int Check_deg(int **AM, int n, int x);


// Create Adjacency matrix
void create_AM(int **AM, int n, int m) { 
    int x, y, h, i, all_visited;
    bool *visit = new bool[n];

    i = m;
    while(i) { 
	y = rand()%n;
	x = rand()%n;
	if(AM[x][y] != 1 && x != y) {
	    AM[x][y] = AM[y][x] = 1;
	    i--;
	} 
    }
    
	for(x = 0; x < n - 1; x++) {
	    h = Check_deg(AM, n, x);
	    if (h%2) {
		y = rand()%(n - x - 1) + x + 1;
		if (AM[x][y]) {
		    AM[x][y] = 0;
		    AM[y][x] = 0;
		    i--;
		} 
		else {
		    AM[x][y] = 1;
		    AM[y][x] = 1;
		    i++;
		}
	    }
	}
	
    all_visited = 1;
    
    dfs(n, 0, visit, AM);
    
    for(x=0; x < n - 1; x++) {
	if (!visit[x]) { 
	    all_visited = 0; 
	    break;
	}
    }
    if (all_visited == 0) {
	nullify(AM, n);
	create_AM(AM, n, m);
    }
}

// Check degree
int Check_deg(int **AM, int n, int x) {
    
    int j = 0;
    for (int i = 0; i < n; i++) {
	if (AM[x][i] == 1)
	    j++;
    }

    return j;
}

// Dfs
void dfs(int n, int v, bool* visited, int **AM) {
    
    visited[v] = 1;  
    for (int x = 0; x < n; x++) {
	if (AM[v][x] && !visited[x]) {
	    dfs(n, x, visited, AM);
	}
    }
}

// Erase connection in a graph
void nullify(int **AM, int n) {
    
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++)  {
	    AM[i][j] = 0;
	}
    }
}


// Copy Graph
void copy(int **AM, int **AM_cp, int n) {
    
    for (int i = 0; i < n; i++) {
	for (int j = 0; j < n; j++)  {
	    AM_cp[i][j] = AM[i][j];
	}
    }
}

// Find Euler cycle
void Euler(int** AM, int n, int v) {
    
    for (int x = 0; x < n; x++) {
	if (AM[v][x]) {
	    AM[v][x] = 0;
	    AM[x][v] = 0;
	    Euler(AM, n, x);
	    }
    }
}

// Find Hamilton cycle
int Hamilton(int n, int v, int* path, bool* visited, int** AM) {

    path[nr++] = v;
    if (nr != n) {
	visited[v] = 1;
	for (int x = 0; x < n; x++)
	    if (AM[v][x] && !visited[x])
		Hamilton(n, x, path, visited, AM);
	visited[v] = 0;
    } 
    else if (AM[v][0]) {
	if (!found) {
	    timeEnd = clock();
	    timeUsed = (double)(timeEnd-timeStart)/CLOCKS_PER_SEC;
	    printf("Czas poszukiwania pojedynczego cyklu Hamiltona: %.3f\n", timeUsed * 1000);
	    found = 1;
	}
	CH++;
    }
    nr--;
    
    return CH/2;
}



int main() {
    int n, m, i, x;
    float d;
    srand(time(0));
    printf("Input n: ");
    scanf("%d", &n);
    printf("Input d: ");
    scanf("%f", &d);
    m = 0.5 * d * n * (n-1);
    
    int **AM = (int**) malloc (n * sizeof(int*));
    for (i = 0; i < n; i++)
	AM[i] = (int*) malloc (n * sizeof(int*));   
    
    int **AM_cp = (int**) malloc (n * sizeof(int*));
    for (i = 0; i < n; i++)
	AM_cp[i] = (int*) malloc (n * sizeof(int*));
    
    bool *visited = new bool[n];
    int *path = new int[n];
    
    create_AM(AM, n, m);
    copy(AM, AM_cp, n);
    timeStart = clock();
    Euler(AM_cp, n, 0);
    timeEnd = clock();
    timeUsed = (double)(timeEnd-timeStart)/CLOCKS_PER_SEC;


    printf("Czas poszukiwania cyklu Eulera: %.3f\n", timeUsed * 1000);
    timeStart = clock();
    printf("Liczba wszystkich cykli Hamiltona: %d\n", Hamilton(n, 0, path, visited, AM));
    timeEnd = clock();
    timeUsed = (double)(timeEnd-timeStart)/CLOCKS_PER_SEC;
    printf("Czas poszukiwania wszystkich cykli Hamiltona: %.3f\n", timeUsed * 1000);
   
    return 0;
}