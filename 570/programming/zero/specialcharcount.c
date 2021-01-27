/*
 * specialcharcount.c - this file implements the specialcharcount function.
 */

#include <stdlib.h>
#include <stdio.h> 
#include "count.h"

void specialcharcount(char *path, char *filetowrite, long charfreq[])
{
    //opens directory
    DIR* dr = opendir(path);
    struct dirent* de;
    char files[100][50] = {"\0"};
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    {
        printf("Could not open current directory");
        return;
    }
    //copies files ending in .txt into files[]
    int count = 0;
    while ((de = readdir(dr)) > 0) {
        char check[strlen(de->d_name)];
        memcpy(check, de->d_name + (strlen(de->d_name) - 4), 5);
        if (strcmp(check,".txt") == 0) {
            strcpy(files[count], de->d_name);
	    count++;
        }
    }
    //opens files
    int j = 0;
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
            int ascii;
            //test characters for speacial character and increments corresponding charfreq[]
            do {
      		ascii = fgetc(fptr);
		if(ascii == EOF){
		    break;
		}
                if (ascii == 44) {
                    charfreq[0] += 1;
                    continue;
                }
                if (ascii == 46) {
                    charfreq[1] += 1;
                    continue;
                }
                if (ascii == 58) {
                    charfreq[2] += 1;
                    continue;
                }
                if (ascii == 59) {
                    charfreq[3] += 1;
                    continue;
                }
                if (ascii == 33) {
                    charfreq[4] += 1;
                    continue;
                }

   	    } while(1);	
        j++;
        }
    }
    //opens output files and writes
    FILE* fptr;
    fptr = fopen(filetowrite, "w");
    fprintf(fptr, ",");
    fprintf(fptr, "->");
    fprintf(fptr, "%d", charfreq[0]);
    fprintf(fptr, "\n", "");

    fprintf(fptr, ".");
    fprintf(fptr, "->");
    fprintf(fptr, "%d", charfreq[1]);
    fprintf(fptr, "\n", "");

    fprintf(fptr, ":");
    fprintf(fptr, "->");
    fprintf(fptr, "%d", charfreq[2]);
    fprintf(fptr, "\n", "");

    fprintf(fptr, ";");
    fprintf(fptr, "->");
    fprintf(fptr, "%d", charfreq[3]);
    fprintf(fptr, "\n", "");

    fprintf(fptr, "!");
    fprintf(fptr, "->");
    fprintf(fptr, "%d", charfreq[4]);
    fprintf(fptr, "\n", "");
}

