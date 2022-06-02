#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define smin 10
#define smax 1000
#define wmin 100
#define wmax 10000
#define BILLION  1000000000L;

int s = 0;
int w = 1;
int ws = 2;
int maks = 0;
float xgh1 = 0;
float xgh2 = 0;
float xgh3 = 0;
float xgh4 = 0;

void swap(int *x, int *y){
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

int max(int x, int y) {
    
    if (x >= y)
	return x;
    return y;
}

void sort_smin(int **p, int m, int n) {
    int i = m, j = n, piv;
    
    piv = p[i][s];
    do {
	while(p[i][s] < piv) i++;
	while(p[j][s] > piv) j--;
	if(i <= j) 
	    swap(p[i++], p[j--]);
    } while(i < j);
    if(m < j) 
	sort_smin(p, m, j);
    if(i < n) 
	sort_smin(p, i, n);
}


void sort_wmax(int **p, int m, int n) {
    int i = m, j = n, piv;
    
    piv = p[i][w];
    do {
	while(p[i][w] < piv) i++;
	while(p[j][w] > piv) j--;
	if(i <= j) 
	    swap(p[i++], p[j--]);
    } while(i < j);
    if(m < j) 
	sort_wmax(p, m, j);
    if(i < n) 
	sort_wmax(p, i, n);
}


void sort_wsmax(int **p, int m, int n) {
    int i = m, j = n;
    int piv;
       
    piv = p[i][ws];
    do {
	while(p[i][ws] < piv) i++;
	while(p[j][ws] > piv) j--;
	if(i <= j) 
	    swap(p[i++], p[j--]);
    } while(i < j);
    if(m < j) 
	sort_wsmax(p, m, j);
    if(i < n) 
	sort_wsmax(p, i, n);
}
	
void DP(int **p, int n, int b) { //Dynamic programming
    int i, j, x, y;
    
    x = b + 1;
    y = n + 1;
    
    int **array = (int**) malloc (x * sizeof(int*));
    for (i = 0; i < x; i++) 
	array[i] = (int*) malloc (y * sizeof(int*));
    
    for (i = 1; i < x; i++) {
	for (j = 1; j < y; j++) {
	    if (p[j-1][s] > i) { 
		array[i][j] = array[i][j-1]; 
		continue;
	    }
			
	    array[i][j] = max(array[i][j-1], array[i-p[j-1][s]][j-1] + p[j-1][w]);
	}
    }
    i = b, j = n;
    while (j) { 
	if(array[i][j] == array[i][j-1]) {
	} 
	else {
	    i -= p[j-1][s];
	}
	j--;
    }
    printf("Value of backpack with Dynamic Programming: %d\n", array[b][n]);
    maks = array[b][n];
    
    for (i = 0; i < x; i++) 
	free(array[i]);
    free(array);
}

void BF1(int **p, int n, int b) {
    int i, j, ssum, wsum, wwmax = 0, ssmax = 0;
    
    for (i = 1; i < (1 << n); i++) {
	ssum = wsum = 0;
	for (j = 0; j < n; j++) {
	    if((i >> j) & 1) { 
		ssum += p[j][s];
		wsum += p[j][w]; 
	    } 
	}
	if((wsum > wwmax) && (ssum <= b)) { 
	    wwmax = wsum; 
	    ssmax = i; 
	}
    }
    printf("Value of backpack with BF1: %d\n", wwmax);
}

int BF2(int n, int ssum, int wsum, int b, int **p) {
    
    if(wsum > maks) 
	maks = wsum;
    if(n < 0) 
	return 0;
    if(ssum + p[n][s] <= b) { 
	BF2(n - 1, ssum + p[n][s], wsum + p[n][w], b, p); 
	if (wsum > maks)
	    maks = wsum;
    }
    BF2(n - 1, ssum, wsum, b, p);
    if(wsum > maks) 
	maks = wsum;
}

void GH1(int **p, int n, int b) {
    int wsum, i, j = b;
	
    for (i = 0; i < n; i++) {
	if (p[i][s] <= j) { 
	    j -= p[i][s]; 
	    wsum += p[i][w];
	}
    }	
    printf("Value of backpack with GH1: %d\n", wsum); 
    xgh1 = ((float)(maks-wsum)/maks)*100;
    printf("Loss Error of GH1: %.2f%%\n", xgh1);
}

void GH2(int **p, int n, int b) {
    int wsum, i, j = b;
	
    sort_smin(p, 0, n-1);
    for (i = 0; i < n; i++) {
	if (p[i][s] <= j) {
	j -= p[i][s]; 
	wsum += p[i][w];
	}
    }	
    printf("Value of backpack with GH2: %d\n", wsum); 
    xgh2 = ((float)(maks-wsum)/maks)*100;
    printf("Loss Error of GH2: %.2f%%\n", xgh2);
}

void GH3(int **p, int n, int b) {
    int wsum, i, j = b;
    
    sort_wmax(p, 0, n-1);
    for (i = n - 1; i >= 0; i--) {
	if (p[i][s] <= j) { 
	    j -= p[i][s]; 
	    wsum += p[i][w];
	}
    }	
    printf("Value of backpack with GH3: %d\n", wsum); 
    xgh3 = ((float)(maks-wsum)/maks)*100;
    printf("Loss Error of GH3: %.2f%%\n", xgh3);
}

void GH4(int **p, int n, int b) {
    int wsum, i, j = b;
    
    sort_wsmax(p, 0, n - 1);
    for (i = n - 1; i >= 0; i--) {
	if (p[i][s] <= j) { 
	    j -= p[i][s]; 
	    wsum += p[i][w];
	}
    }	
    printf("Value of backpack with GH4: %d\n", wsum); 
    xgh4 = ((float)(maks-wsum)/maks)*100;
    printf("Loss Error of GH4: %.2f%%\n", xgh4);
}

int main() {
    int n, b = 0, i;
    float d;
    struct timespec start, stop;
    double accum;
    char c[40];
    
    printf("Input quantity of packages (n): ");
    scanf("%d", &n);
    
    printf("Input b percentage of a backpack as fraction (for instance 0.5): ");
    scanf("%f", &d);
    
    srand(time(NULL));
    
    int **p = (int**) malloc (n * sizeof(int*));
    for (i = 0; i < n; i++) { 
	p[i] = (int*) malloc (n * ws * sizeof(int*));
	p[i][s] = rand()%(smax - smin) + smin;
	b += p[i][s];
	p[i][w] = rand()%(wmax - wmin) + wmin;
	p[i][ws] = (int) p[i][w]/p[i][s];
    }
    
    b = b*d;
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    DP(p, n, b);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
    printf("Time for Dynamic Programming : %.5f\n", accum * 1000);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    BF1(p, n, b);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
    printf("Time for BF1 : %.5f\n", accum * 1000);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    BF2(n - 1, 0, 0, b, p);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
    printf("Value of backpack with BF2: %d\n", maks);
    printf("Time for BF2 : %.5f\n", accum * 1000);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    GH1(p, n, b);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
    printf("Time for GH1 : %.5f\n", accum * 1000);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    GH2(p, n, b);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
    printf("Time for GH2 : %.5f\n", accum * 1000);
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    GH3(p, n, b);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
    printf("Time for GH3 : %.5f\n", accum * 1000);
    
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    GH4(p, n, b);
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);
    accum = ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec )/(double)BILLION;
    printf("Time for GH4 : %.5f\n", accum * 1000);
    
    return 0;
}