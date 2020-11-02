#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <inttypes.h>
#include <stdbool.h>

int pizza = 1;
int slice = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *eating (void *);
void *deliver (void *);

int main(int argc, char *argv[]){
	int students = atoi(argv[1]);
	int count=0;
	pthread_t sthreads[students];
	pthread_t delivery;
	printf("Number of students: %d\n",students);
	while(pizza < 13){
	//pthread_mutex_lock(&mutex);
	if( students > 1 && students < 6 ){
	//pthread_mutex_lock(&mutex);
	for(count=0; count<students;count++){
		if(slice == 8){
		//pthread_mutex_lock(&mutex);
		slice=1;
		pthread_create(&delivery,NULL,deliver,NULL);
		//pthread_mutex_unlock(&mutex);
	}
	else{
		//pthread_mutex_lock(&mutex);
		pthread_create(&sthreads[count],NULL,eating,(void *)(intptr_t)count);
		slice++;
		//pthread_mutex_unlock(&mutex);
	}
		}
	//pthread_mutex_unlock(&mutex);	
	}
	else{
	printf("Error please enter a number between 1-10 next time.\n");
	exit(0);
	}
	//pthread_mutex_unlock(&mutex);
	}
	if( students > 1 && students < 6){
	for(count=0; count<students;count++){
		pthread_join(sthreads[count],NULL);
	}
	}
	pthread_join(delivery,NULL);
	return(0);	
}

void *eating (void *arg){
    int studentid = (int)(intptr_t)arg;
	//pthread_mutex_lock(&mutex);
    printf("Student %d is eating a slice of pizza %d\n",studentid+1,pizza);
	
	sleep(rand() % 3);
	
	//pthread_mutex_unlock(&mutex);
	
}

void *deliver (void *arg){
	int studentid = (int)(intptr_t)arg;
	//pthread_mutex_lock(&mutex);
	pizza++;
	printf("Student %d ordered pizza %d \n",studentid+1, pizza);
	printf("pizza %d is delivered \n", pizza);
	//sleep(rand() % 3);
	//pthread_mutex_unlock(&mutex);

}