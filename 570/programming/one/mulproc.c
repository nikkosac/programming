#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void){
    //variable declaration
    char* args[] = { "./testalphabet","./testspecial",NULL };
    int status = 0;
    pid_t child_a, child_b, wpid;

    //first fork
    child_a=fork();
    if (child_a == 0) {
        //prints which prgram is running then runs it via execv()
        printf("Child<%d> is executing testalphabet\n", getpid());
	execv(args[0],args);
    }
    else {
        //second fork
        child_b = fork();
        if (child_b == 0) {
	    //prints which prgram is running then runs it via execv()
	    printf("Child<%d> is executing testspecial\n", getpid());
	    execv(args[1],args);
         }else{
 	    //parent code
	    //prints which child thread has been completed and waits until all child threads are terminated
            while ((wpid = wait(&status)) > 0){
		if(wpid == child_a){
		    printf("Child<%d> is done executing testalphabet see results above\n", wpid);
		}else{
		    printf("Child<%d> is done executing testalspecial see results above\n", wpid);

		}
            }
        }
    }
    return 0;
}