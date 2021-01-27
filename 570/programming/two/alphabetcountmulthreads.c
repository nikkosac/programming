#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 
#include "count.h"
#include <dirent.h>
#include <string.h>

//global variable
long alphabet[52];

//mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


//heler function to copy files for each thread
void ChoseArray(char newArray[100][50], char category[100][50],int size){
    int i;
    for(i=0;i<size;i++)
        strcpy(newArray[i], category[i]);
}


//pthread arguments
struct thread_args {
    char files[100][50];
    int size;
    int number;
    int mod;
    int normal;
    long alphabetfreq[52];
};
void *func(void *arg)

{

   int arg_int = (int) arg;   // treats argument as integer

   int x = ....;   // computes something based on 'arg_int', put result in 'x'

   return (void *) x;    // return integer x (pretending it is a "void *")

}

//function for which the threads are created
void* FilesProcessor(void *args){
    pid_t id = pthread_self();
    int offset = 0;
    struct thread_args *curargs = (struct thread_args*) args;
    for(int i = 0; i < 52 ;i++){
	curargs->alphabetfreq[i] = 0;
    }
    // determines the offset for each thread

    if((curargs->mod > 0)  && (curargs->number > 0)){
	if(curargs->number > curargs->mod || curargs->mod == curargs->number){
	    offset = curargs->mod;
	}else{
	    offset = curargs->number;
	}
    }
    //start is where the thread starts its parse

    int start = (curargs->normal * curargs->number) + offset;
    printf("Thread id = %lu starts processing files with index from %d to %d\n",id,
	start, start + curargs->size - 1);

    //processes each of the files and increments each letter in array accordingly
    for(int j = 0; j<curargs->size;j++){
        FILE* fptr;
	fptr = fopen(curargs->files[start+j], "r");
        if (fptr == NULL) {
            printf("Error! opening file\n");
            continue;
        }
        else {
	    printf("Thread id = %lu is currently processing file %s\n",id,curargs->files[start+j]);
    	    int read; 

            //checks files for leters in alphabet and increments corresponding alphabetfreq[] array
	    do {
      		read = fgetc(fptr);
		if(read == EOF){
		    break;
		}
      	   	 if ((read - 65 >=0) && (read - 65 <= 25)) {
            	    curargs->alphabetfreq[read - 65] += 1;
            	    continue;
            	}
          	 if ((read - 97 >=0) && (read - 97 <= 25)) {
           	     curargs->alphabetfreq[read - 97 + 26] += 1;
          	 }
   	    } while(1);	
	fclose(fptr);
        }
    }
    //locks the global letter array variable and increments accordingly

    pthread_mutex_lock(&mutex);
    for(int i = 0; i<52;i++){
        alphabet[i] += curargs->alphabetfreq[i];
    }
    pthread_mutex_unlock(&mutex);
    printf("Thread id = %lu is done !\n",id);
    pthread_exit(0);
}

void alphabetcountmulthreads(char *path, char *filetowrite, long alphabetfreq[], int num_threads)
{
    pthread_t tids;

pthread_attr_t attr;

int f = 100;
int *ret;
pthread_create(&tids, &attr, func,&f);

int pthread_join(&tids, &ret);
printf("%d",ret);
}


