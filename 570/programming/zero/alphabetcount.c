#include <stdio.h> 
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>

void alphabetlettercount(char* path, char* filetowrite, long alphabetfreq[])
{
    DIR* dr = opendir(path);
    struct dirent* de;
    char files[100][50] = {"\0"}; 
    //opens directory
    if (dr == NULL)
    {
        printf("Could not open current directory");
        return;
    }
    //copies files into files array if end in .txt
    int count = 0;
    while ((de = readdir(dr)) > 0) {
        char check[strlen(de->d_name)];
        memcpy(check, de->d_name + (strlen(de->d_name) - 4), 5);
        if (strcmp(check,".txt") == 0) {
            strcpy(files[count], de->d_name);
	    count++;
        }
    }
    int j = 0;
    //opens files
    while (j<100 && files[j] != "\0") {
	char* fDest;
        fDest = malloc(strlen(path) + 1 + 4);
        strcpy(fDest, path);
        strcat(fDest, "/");
        strcat(fDest, files[j]);
        FILE* fptr;
        if ((fptr = fopen(fDest, "r")) == NULL) {
            printf("Error! opening file");
            return;
        }
        else {
    	    int read; 
            //checks files for leters in alphabet and increments corresponding alphabetfreq[] array
	    do {
      		read = fgetc(fptr);
		if(read == EOF){
		    break;
		}
      	   	 if ((read - 65 >=0) && (read - 65 <= 25)) {
            		alphabetfreq[read - 65] += 1;
            	 	continue;
            	}
          	 if ((read - 97 >=0) && (read - 97 <= 25)) {
           	 alphabetfreq[read - 97 + 26] += 1;
          	 }
   	    } while(1);	   
 	fclose (fptr);
        }
        j++;
    }
    FILE* fptr;
    fptr = fopen(filetowrite, "w");
    if(fptr == NULL){
	printf("could not open file");
    }
    //prints upper case letters
    char let = 'A';
    char str[2] = "\0"; /* gives {\0, \0} */
    for (int i = 0; i < 26; i++) {
	str[0] = let;
	fprintf(fptr, str);
        fprintf(fptr, "->");
        fprintf(fptr, "%d", alphabetfreq[i]);
	printf("%l", alphabetfreq[i]);
	printf(fptr, "\n", "");
        let++;
    }
    //prints lower case letters
    let = 'a';
    for (int i = 0; i < 26; i++) {
	str[0] = let;
	fprintf(fptr, str);
        fprintf(fptr, "->");
        fprintf(fptr, "%d", alphabetfreq[i + 26]);
	printf("%l", alphabetfreq[i + 26]);
	fprintf(fptr, "\n", "");
        let++;
    }
}
