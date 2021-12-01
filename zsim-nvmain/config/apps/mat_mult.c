#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>
#include "../../misc/hooks/zsim_hooks.h"

#define DEBUG 0
#define N_ROWS 100
#define N_COLS 100


int NUM_HILOS_ACTUAL = 0;
int hilos_ejecutandose = 0;

double matrix1[N_ROWS][N_COLS];
double matrix2[N_ROWS][N_COLS];
double matrix3[N_ROWS][N_COLS];
double suma_total;
pthread_mutex_t mutex1;
pthread_barrier_t barrier;

struct data{
	long id;
	int rows;
	int cols;
};

void guardar_tiempo(int num_threads, long double time);
void imprimir_matrix(double matrix[][N_COLS]);
void llenar_matrix(double matrix[][N_COLS]);
void calcular();

int main(){
	llenar_matrix(matrix1);
	llenar_matrix(matrix2);
	llenar_matrix(matrix3);
	calcular();	
}


void imprimir_matrix(double mat[][N_COLS]){
	printf("Imprimiendo matriz...\n");
	int x,y;
	for(x = 0;x < N_ROWS;x++){
		for( y = 0;y < N_COLS;y++){
			printf("%lf \t",matrix1[x][y]);
		}
	}
	printf("\n");
}

void llenar_matrix(double mat[][N_COLS]){
	int x,y;
	for(x = 0;x < N_ROWS;x++){
		for(y = 0;y < N_COLS;y++){
			mat[x][y] = y*3+2*(rand()%15);
		}
	}
}

void calcular (){

	zsim_roi_photonic_switch_on();
	int x,y,z,parcial;
	parcial = 0;
	for (x=0;x < N_ROWS;x++)
	{
		for (y = 0;y < N_COLS;y++)
		{
			for(z = 0;z < x;z++){
				parcial+=matrix1[x][z]*matrix2[z][y];
			}
			matrix3[x][y] = parcial;
		}
	}
}
