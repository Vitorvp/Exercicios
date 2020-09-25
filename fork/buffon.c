#include <time.h> /* for timing the code */
#include <stdlib.h> /*for random numbers */
#include <stdio.h> /* for writing to files */
#include <math.h> /* for exponentials and logs */
#include <unistd.h> /* for fork() and sleep */
#include <sys/wait.h> /* for wait function */

	FILE *arq;
	FILE *hit_p;
	FILE *hit_f;

	int pai, filho, i = 0;
	int numLogPoints = 9;

/* log Pi aproximation on these iterations */
	long log_points[] = { 10, 100, 1000, 10000, 100000,
	1000000, 10000000, 100000000, 1000000000};

	int calc();

double realRandon(void){
    int a = rand();
    int b = rand();
    if(a>b)
       return (double)b/a;
    else
        return (double)a/b;
}

int main(int argc, char **argv){

	/* time store locations */
	clock_t startTime, endTime;

	/* start time count */
	startTime = clock();

	pid_t pid = fork();

	if(pid==0){
		printf("Sou o Processo FILHO PID[%ld], meu pai é o PID[%ld]\n\n", (long) getpid(), (long) getppid());
		printf("Executando o programa...\n");
		sleep(1);
		calc(pid);
		exit(EXIT_SUCCESS);
	}

	else if(pid>0){
		printf("Sou o Processo PAI PID[%ld], meu filho é o PID[%ld]\n", (long) getpid(), (long) pid);
		
		int status;
		calc(pid);
  		wait(&status);

		printf("PAI:\tFILHO finalizou com status %d\n", status);

		hit_p = fopen("Hits_PAI.txt","r");
		hit_f = fopen("Hits_FILHO.txt","r");

		while (i < numLogPoints)
        {
            fscanf(hit_p,"%d",&pai);
			fscanf(hit_f,"%d",&filho);

			int total_hits = pai + filho;

			/* elapsed time */
			endTime = clock();
				
				printf("NThrows: %11d Hits: %11d Pi Aprox.: %1.7f\n",
				log_points[i],
				total_hits,
				(2.0*log_points[i])/total_hits);

			i++;
        }
		printf("Tempo total de processamento: %8.2f s.\n", ((double)(endTime-startTime))/CLOCKS_PER_SEC); 
		printf("PAI:\tFinalizado\n");
		exit(EXIT_SUCCESS);
	}
	else{
		printf("Fork() Falhou!\n");
		return 1;
	}
	return 0;
}

int calc(long pid)
{
	if(pid>0){
		arq = fopen("Hits_PAI.txt", "wt");
	}
	if(pid==0){
		arq = fopen("Hits_FILHO.txt", "wt");
	}

	float theta, distance;

	/* simulate throws of a 1 unit needle on a sheet with one */
	/* unit distant parallel lines and acumulate the number of */
	/* hits (i.e. needle crossing/touching a line) */
	long i=1;
	long hits = 0;
	int logIndex = 0;

	srand((unsigned) time(NULL));

	while (logIndex < numLogPoints) {
		/* set next log point */
		long nextLogPoint = log_points[logIndex] / 2;
		logIndex++;

		/* iterate */
		for (;i<=nextLogPoint;i++) {
			/* get a sample from a U(0,PI) */
			theta = realRandon() * M_PI;

			/* get a sample from a U(0,0.5) */
			distance = 0.5 * realRandon();

			/* see if it falls on the hit area */
			if (distance <= 0.5 * (sin(theta))){
				hits++;
			}
		}
				fprintf(arq, "%11d \n", hits);
	}
	fclose(arq);
	return(0);
}
