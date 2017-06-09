/* Sean Kennedy
 * Final Project
 * CS6029 Fall 2016
 * Dr. Rui Dai
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_LINE 80 //max 80 characters per command

char hist[10][MAX_LINE]; //an array to store history commands
int numCommands = 0;  //keep track of number of commands

//Function to print out history as shown in textbook
void showHist(){
    int i;
    int j = 0;
    int histCount = numCommands;
    for (i = 0; i<10; i++){ //print # and command
       	printf("%d.  ", histCount);
        while (hist[i][j] != '\n' && hist[i][j] != '\0'){
            printf("%c", hist[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        histCount--;
        if (histCount ==  0)
        break;
    }
}

//Reads input and split into tokens
//source code partially provided by osu.edu
void readTok(char in[], char *args[],int *isAmp)
{
    int charInd = 0;    //where to place next char in args
	int length; 		//length of command
    int next;  			//next command

    //read user input
    length = read(STDIN_FILENO, in, MAX_LINE);

    //return error if length < 0
    next = -1;
    if (length == 0)
        exit(0);
    if (length < 0){
        perror("could not read command");
	exit(-1);
    }

    //check each character in in[]
    for (int i = 0; i < length; i++) {
        switch (in[i]){
        case ' ':
        case '\t' :
            if(next != -1){
                args[charInd] = &in[next];
                charInd++;
            }
            in[i] = '\0';
            next = -1;
            break;

        case '\n':
            if (next != -1){
                args[charInd] = &in[next];
                charInd++;
            }
            in[i] = '\0';
            args[charInd] = NULL;
            break;

        case '&': 		// command followed with &, wait for child to terminate
            *isAmp = 1;
            in[i] = '\0';
            break;

        default :
            if (next == -1)
                next = i;
	}
    }
    args[charInd] = NULL;

    //check to see if user inputed the history command and if there is a command history
    if(strcmp(args[0],"history") == 0){
            	if(numCommands>0){
            		showHist();
    		} else{
    			printf("\nNo Commands in history\n");
    			}
    }
    	//Check to see if '!' is inputed
    	//then retrieve appropriate command
    	else if (**args == '!'){
    		int check2 = args[0][1]- '0';
    		int check3 = args[0][2];
    		if(check2 > numCommands){
    		printf("\nCommand not found\n");
    		strcpy(in,"Invalid Command");
    		}else if (check3 != 0){
    				printf("\nInput too large.  History only contains last 10 commands. \n");
    				strcpy(in,"Invalid Command");
    		}	else{
    				if(check2==-15){// If '!!' entered
    					 strcpy(in,hist[0]);

    				}	else if(check2 == 0){
    						printf("Can not enter 0. Enter ! followed by single integer 1-9");
    						strcpy(in,"Invalid Command");
    					}	else if(check2 >= 1){ //Checking for '!n', n >=1
    							strcpy(in,hist[numCommands-check2]);
    						}

    				}
    		}
    //update history
    for (int i = 9; i>0; i--)
    	strcpy(hist[i], hist[i-1]);
        strcpy(hist[0],in);
        numCommands++;
    	if(numCommands>10){
    	numCommands=10;
    	}
}

// Infinite loop for commands. After printing 
// "osh>" gets user input from readTok and
// forks processes to execute commands
int cmdLoop(void){
    char in[MAX_LINE]; 			//array to store user inpute
    char *args[MAX_LINE/2+1];
    int isAmp;             		//is and ampersand in command
    pid_t pid;
    int loops;					//times looped
    int continueLoop = 1;

    while (continueLoop){
	isAmp = 0;
	printf("osh>");
    fflush(stdout);
    readTok(in, args, &isAmp);   //get the input from the user
    pid = fork();

   	if (pid < 0) {  			//when pid < 0 forking has failed
   		printf("Fork failed.\n");
   		exit (1);
 	} 		else if (pid == 0){//if pid ==0
 		 				if (execvp(args[0], args) == -1 && strcmp(in, "history") != 0)  //a non valid command or history command
 		 				{
 		 					printf("Invalid Command (ctrl^c to exit)\n");
 		 				}
    		}	else{
    			loops++;
    				if (isAmp == 0){	//Wait for child process to terminate if '&' follows command
    					loops++;
    					wait(NULL);
    				}

    		}
	}
	return 0;
}

//Only need to initiate loop here. All other functionality in other functions.
int main(void){
cmdLoop();
return 0;
}

