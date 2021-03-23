/*Guzel Noori
2/3/2021
Lab 2 - Operating Systems*/

//include packages and dependents
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINES 3000
static char soe[MAX_LINES];

//function to read through the lines and find prime numbers
static int findPrimeNum(int i, const char * inputFile){

    FILE * textFile = fopen(inputFile, "r");
    //Error hadling for the incorrrect text file
    if(textFile == NULL){
        printf("File does not exist. Check the repository for the correct name of the file.\n");
        return -1;
    }

    int row = 0;
    char * line = NULL;
    size_t lineSize = 0;

    while(getline(&line, &lineSize, textFile) > 0){
        if(row++ == i){
            i += 4;

            const int number = atoi(line);

            if((number >= 2) && (number < MAX_LINES) && (soe[number])){
                //printing primes numbers line by line
                printf("%d\n", number);
            }
        }
    }
    fclose(textFile);
    free(line);

    return 0;
}

int main(const int argc, char * argv[]){
    
    pid_t pids[4];
    const char * inputFile = argv[1];
    int p;
    char fileName[100];
  
    printf("Enter file name that contains list of numbers (Example fileName.txt):\n");
    scanf("%s", fileName);
    inputFile = fileName;

    memset(soe, 1, sizeof(char)*MAX_LINES);
    
    printf("The following is the list of prime numbers from the ");
    printf("%s", fileName);
    printf(" text file \n");

    for (int p = 2; p * p < MAX_LINES; p++) {
        if (soe[p] == 1) {
            for (int l = p * 2; l < MAX_LINES; l += p)
                soe[l] = 0;
        }
    }
    memset(pids, 0, sizeof(pid_t)*4);

    for(p=0; p < 4; p++){
        //Creating processes
        pids[p] = fork();
        //Process Error Handling
        if(pids[p] == -1){
            perror("fork");
            break;
        //printing prime numbers
        }else if(pids[p] == 0){
            findPrimeNum(p, inputFile);
            exit(0);
        }
    }
    //process wait session
    for(p=0; p < 4; p++){
        waitpid(pids[p], NULL, 0);
    }
    return 0;
}
