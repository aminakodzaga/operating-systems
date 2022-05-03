#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <linux/kernel.h>
#include <sys/sysinfo.h>
#include <libgen.h>
#include <signal.h>
#include <sys/wait.h>

int loop = 1;
#define MAX_LINE 80 

int count = 0;
//The program will generate a list of fortune instructions at random
const char* a[] = {
        "limerick", "zippy", "startrek",
        "freebsd-tips", "osfortune", "linuxcookie",
        "fortunes2", 
};
const size_t FORTUNES = sizeof(a)/sizeof(*a) - 1;

void black() {
    printf("\033[0;36m"); //033 is an escape sequence that controls the cursor and text color on the console, among other things.
}

void yellow() {
    printf("\033[0;37m");
}

void cyan() {
    printf("\033[0;36m");
}

void reset() {
    printf("\033[0m");
}

int main(void) {

    system("clear");

    char input[1024];

    while (loop) {

        prompt();

        fgets(input, 1024, stdin);

        router(input);
    }

    return 0;
}

void prompt() {

    char * name;
    char hostname[HOST_NAME_MAX + 1];

    name = getlogin();

    gethostname(hostname, HOST_NAME_MAX + 1);

    char cwd[PATH_MAX];//The maximum size of file paths that can be used (4096 bytes)

    black();
    printf("%s", hostname);

    yellow();
    printf("@");

    cyan();
    printf("%s", name);

    reset();

    printf(":~$ ");

}
//This is a main function that deals with system calls, inputs, and outputs, and it is used to route user input.
void shell_router(char input[1024]) {

    char function [10] = "";
    int function_counter = 0;

    
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] != ' ' || (int) input[i] == 0) {
            function [function_counter] = input[i];
            function_counter++;
        } else {
            break;
        }
    }

    
    function [strcspn(function, "\n")] = 0;
  
    if (strcmp(function, "copy") == 0) {
        copy(input);
    } else if (strcmp(function, "history") == 0) {
        get_history();
    } else if (strcmp(function, "free") == 0) {
        free_malloc();
    } else if (strcmp(function, "fortune") == 0) {
        fortune();
    } else if(strcmp(function, "custom") == 0){
		  for (int i = 0; i < 150; i++){ 
		    system("sleep 0.01"); 
		    system("clear"); 
		    customCommand(i); 
		  }
		  system("clear");
	  } else if ((int)function [0] != 0) {
        printf("%s: command is not found\n", function);
    }

}
// cp functionality
void copy(char input[]) {
    FILE * f1, * f2;
    char source[50];
    char destination[50];

    printf("Please enter source file name:");
    scanf("%49s", source);
    printf("Please enter destination file name:");
    scanf("%49s", destination);
    //opens the file with the appropriate source and destination, then copies and saves the content from source to destination.
    f1 = fopen(source, "r");
    f2 = fopen(destination, "w");
    if (!f1 || !f2) {
        printf("error");
    }
    char c;
    while ((c = fgetc(f1)) != EOF) { // fgetc delivers an int representation of the character read or EOF to signal an error or the end of the file.
        fputc(c, f2);
    }
    fclose(f1);
    fclose(f2);
}


#define BUFFER_SIZE 50
#define buffer "Shell Command History:\n"
char history[10][BUFFER_SIZE]; 

void ShowHistory() {

    printf("Show shell command history:\n");

    int i;
    int j = 0;
    int historyCount = count;
    for (i = 0; i < 10; i++) {
        printf("%d.  ", historyCount);
        while (history[i][j] != '\n' && history[i][j] != '\0') {
            printf("%c", history[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        historyCount--;
        if (historyCount == 0)
            break;
    }
    printf("\n");
}
//Get the command from the shell, tokenize it, and set the args parameter with this function.
int formatCommand(char inputBuffer[], char * args[], int * flag) {

    int length;
    int i;
    int start;
    int ct = 0;// index that tells us where to place the next parameter into args[]

    length = read(STDIN_FILENO, inputBuffer, MAX_LINE);

    start = -1;
    if (length == 0)
        exit(0); 
    if (length < 0) {
        printf("No, command is not read\n");
        exit(-1); 
    }
    
    for (i = 0; i < length; i++) {
        switch (inputBuffer[i]) {
            case ' ':
            case '\t'://we use this to seperate arguments
                if (start != -1) {
                    args[ct] = & inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';
                start = -1;
                break;

            case '\n'://
                if (start != -1) {
                    args[ct] = & inputBuffer[start];
                    ct++;
                }
                inputBuffer[i] = '\0';
                args[ct] = NULL; // there is no more args
                break;

            default:
                if (start == -1)
                    start = i;
                if (inputBuffer[i] == '&') {
                    * flag = 1;//This flag determines whether the child process is started in the background.
                    inputBuffer[i] = '\0';
                }
        }
    }

    args[ct] = NULL;//if the input line was > 80

    if (strcmp(args[0], "history") == 0) {
        if (count > 0) {

            ShowHistory();
        } else {
            printf("No commands in the history\n");
        }
        return -1;
    } else if (args[0][0] - '!' == 0) {
        int a = args[0][1] - '0';
        int z = args[0][2] - '0';

        if (a > count) {
            printf("No Such Command in the history\n");
            strcpy(inputBuffer, "It is a Wrong command");
        } else if (z != -48) {
            printf("No Such Command in the history. Enter <=!9 \n");
            strcpy(inputBuffer, "Wrong command");
        } else {

            if (a == -15) {//Checking for '!!',ascii value of '!' is 33
                strcpy(inputBuffer, history[0]);
            } else if (a == 0) {
                printf("Enter proper command");
                strcpy(inputBuffer, "Wrong command");
            } else if (a >= 1) {
                strcpy(inputBuffer, history[count - a]);

            }

        }
    }
    for (i = 9; i > 0; i--)//Moving the history components up a notch
        strcpy(history[i], history[i - 1]);

    strcpy(history[0], inputBuffer);
    count++;
    if (count > 10) {
        count = 10;
    }
}

//get history with forking the process 
void get_history() {
    char inputBuffer[MAX_LINE];
    int flag;
    char * args[MAX_LINE / 2 + 1];
    int should_run = 1;

    pid_t pid, tpid;
    int i;

    while (should_run) {
        flag = 0;
        printf("history>");
        fflush(stdout);
        //If statements will check whether the process is child or parent
        if (-1 != formatCommand(inputBuffer, args, & flag)) { 
            pid = fork();

            if (pid < 0) {//if pid is less than 0, forking fails

                printf("Fork failed.\n");
                exit(1);
            } else if (pid == 0) {

                if (execvp(args[0], args) == -1) {//The most common usage of the execvp function is to overlay a process image formed by a call to the fork function.

                    printf("Error executing command\n");
                }

            } 
    
            else {
                i++;
                if (flag == 0) {
                    i++;
                    wait(NULL);
                }
            }
        }
    }
}

//free functionality
void free_malloc() { //The malloc function will ask the heap for a block of memory.
    int * ptr, * ptr1;
    int n, i;

    n = 5;
    printf("Please enter number of elements: %d\n", n);
    ptr = (int * ) malloc(n * sizeof(int));
    ptr1 = (int * ) calloc(n, sizeof(int));

    if (ptr == NULL || ptr1 == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    } else {

        printf("Memory successfully allocated.\n");//malloc() takes a single argument 

        free(ptr);
        printf("Malloc Memory successfully freed.\n");

        printf("\nMemory successfully allocated using calloc.\n");//calloc() needs two arguments (the number of variables to allocate in memory, and the size in bytes of a single variable).

        free(ptr1);
        printf("Calloc Memory successfully freed.\n");//Calloc Mmeory cleaned
    }
}
// Function that returns a random number
int random(int Size) {
    int k;
    k = 0;
    srand((unsigned) time(NULL));
    k = rand() % Size;
    return k;
}
//fortune functionality
void fortune() {
    execlp("/usr/games/fortune", x[random(FORTUNES)], "-l", NULL, NULL);//Print a random fortune from an array.
}

void printline(char *line, int number){
        for(int i = 0; i < number; i++){
                printf(" "); // prints an empty space based on the value of number (space)
        }
        printf("%s\n", line); // prints a "line" of the dog
}

	void customCommand(int spaces){ 
	yellow();

    char *line1 =                               /^-----^\
    char *line2 =                               V  o o  V
    char *line3 =                                |  Y  |
    char *line5 =                                 \ Q /
    char *line5 =                                 / - \
    char *line6 =                                 |    \
    char *line7 =                                 |     \     )
    char *line8 =                                 || (___\====
  
	// prints all segments of the dog using printline() 
	printline(line1, spaces);
	printline(line2, spaces);
	printline(line3, spaces);
    printline(line4, spaces);
    printline(line5, spaces);
    printline(line6, spaces);
    printline(line7, spaces);
    printline(line8, spaces);
    printline(line9, spaces);
    printline(line10, spaces);
    printline(line11, spaces);
    printline(line12, spaces);
	reset();

}
//Fork Bomb - harms a system by making it run out of memory. 
void forkbomb()
{
    char ch;
    printf("Do You want to crash your device (y/n): ");
    scanf("%c", &ch);
//If yes execute bomb
    if(ch=='y' || ch=='Y'){
        printf("Well,that escalated quickly\n");
        while(1){
           fork();   
        } 

    }
//If not thank the user:)
    else if(ch=='n' || ch=='N'){

        system("Thank you for not crashing me\n ");
    
    }
    else{
		printf("Execute abort\n");
	}
}