#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>

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
void* calcular(void* params);

int main(){
	int rc;
	void *status;
	int num_hilos = 0;
	int* num_hilos_arreglo = malloc(sizeof(int) * num_hilos);
	num_hilos_arreglo[0] = 1;
	num_hilos_arreglo[1] = 2;
	num_hilos_arreglo[2] = 4;
	num_hilos_arreglo[3] = 8;

	suma_total = 0;


	llenar_matrix(matrix1);
	llenar_matrix(matrix2);
	llenar_matrix(matrix3);
	
	for(NUM_HILOS_ACTUAL = num_hilos_arreglo[num_hilos];num_hilos <  1;num_hilos++){
		NUM_HILOS_ACTUAL = num_hilos_arreglo[num_hilos];
		struct timeval begin;
		struct timeval end;
		long double Time;

		struct data data_threads[NUM_HILOS_ACTUAL];
		pthread_t threads[NUM_HILOS_ACTUAL];
		pthread_attr_t attr;
		pthread_mutex_init(&mutex1,NULL);
		pthread_attr_init(&attr);
		//pthread_barrier_init(&barrier, NULL, NUM_HILOS_ACTUAL);
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
		
		gettimeofday(&begin, NULL);
		long t;
		for (t = 0;t < NUM_HILOS_ACTUAL;t++){

			data_threads[t].id=t;
			rc=pthread_create(&threads[t],&attr,calcular,(void*)&data_threads[t]);
		
			//Sale del programa si hay algun error en la creacion del thread
			if (rc){
				printf("ERROR codigo %d \n",rc);
				exit(-1);
			}
		}
		pthread_attr_destroy(&attr);


		//Join de los hilos
		for(t = 0;t < NUM_HILOS_ACTUAL;t++){

			rc=pthread_join(threads[t],&status);
			hilos_ejecutandose--;
			if (rc){
				printf("ERROR,codigo %d \n",rc);
				exit(-1);
			}

			if(DEBUG){
				printf("En la funcion main, ya acabo el hilo %ld con status %ld \n",t,(long)status);
			}
		}


		gettimeofday(&end, NULL);
		Time  = (long double) ( (long double) begin.tv_sec + (long double)begin.tv_usec / 1000000);
		Time = (long double)((long double) end.tv_sec + (long double)end.tv_usec / 1000000) - Time;
		printf("Thread e hilos: %d - %Lfs\n", NUM_HILOS_ACTUAL, Time);
		guardar_tiempo(NUM_HILOS_ACTUAL, Time);
	}

	pthread_mutex_destroy(&mutex1);
	pthread_exit(NULL);
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

void* calcular (void *params){
	struct data* param_data =(struct data *) params;


	long id = param_data->id;

	int lim_inf = id*(N_ROWS/NUM_HILOS_ACTUAL);
	int lim_sup = (id+1)*(N_COLS/NUM_HILOS_ACTUAL);

	double parcial = 0;

	if(DEBUG){
		printf("Hilo %ld, LIM inf %d LIM sup %d \n",id,lim_inf,lim_sup);
	}

	int x,y,z;
	for (x=lim_inf;x < lim_sup;x++)
	{
		for (y = lim_inf;y < lim_sup;y++)
		{
			for(z = 0;z < x;z++){
				parcial+=matrix1[x][z]*matrix2[z][y];
			}
			pthread_mutex_lock(&mutex1);
			matrix3[x][y] = parcial;
			pthread_mutex_unlock(&mutex1);
		}
	}


	//pthread_barrier_wait(&barrier);
	pthread_exit(NULL);
}

void guardar_tiempo(int num_threads, long double time){
	FILE *f = fopen("output_times.txt", "a");
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(f, "%Lf\n", time);
	fclose(f);
}

