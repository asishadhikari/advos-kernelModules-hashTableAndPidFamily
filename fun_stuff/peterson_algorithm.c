#include <pthread.h>
#include <stdio.h>

int turn ;
int flag[2]; 

int val = 0;


void thread_entry_point(void* t){
	do{
		int* tid_p = (int*)t;
		int tid = *tid_p; //tid is 0 or 1
		
		//set flag for self
		flag[tid] = 1;
		//set turn for other
		turn = tid==1 ? 0 : 1; 
		
		int other_thread = tid==1? 0:1;
		while(turn!=tid&&flag[other_thread]); //busy waiting 
		//critical section
		if (tid==1){
			val++;
		}else{
			val--;
		}
		printf("Value is %d for thread %d\n",val,tid);

		//exit critical section
		flag[tid]=0;

			
	}while(1);

}


int main(){
	pthread_t threads[2];
	int zero = 0;
	int one = 1;
	pthread_create(&threads[0],NULL,thread_entry_point,&zero);
	pthread_create(&threads[1],NULL,thread_entry_point,&one);
	pthread_join(threads[0],NULL);
	pthread_join(threads[1],NULL);


	return 0;
}