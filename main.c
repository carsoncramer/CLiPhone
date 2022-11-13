#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>


char** format_number(char* number[]){ //maybe just multithread this for no reason in the future
    char prefix[] = "tel://+";
    char* concat = (char*)malloc(sizeof(char) * (8 + 11)); // allocating size of prefix plus number, not including prefixed null char

    for(int i = 0; 1; i++){
        if(i < 7){
            concat[i] = prefix[i];
        }
        else{
            concat[i] = number[1][i - 7];
            if(number[1][i-7] == '\0'){
                break;
            }
        }
    }

    char** output = (char**)malloc(sizeof(char*) * 4);
    output[0] = number[0];
    output[1] = concat;
    output[2] = "-j";
    output[3] = number[2];

    return output;
}


int make_call(char *argv[]){

    pid_t pid = fork();

    if(pid < 0){ //Fork fails
        fprintf(stderr, "Fork Failed");
        exit(1);
    }
    else if(pid == 0){ //Child
        execvp("open", format_number(argv));
        //if this gets hit it means it errored
		fprintf(stderr, "execvp failure, exit status: 1 \n");
		exit(1);
    }
    else{ //parent
        int status;
		if (waitpid(pid, &status, 0) == -1) { //this blocks the parent until the child is finished and then puts the child's exit status into status.
			fprintf(stderr, "Something is wrong with your request, exit status: 1\n");
			return 1;
		}
		if (WIFEXITED(status)) { //if the child returned and gave a status
            fprintf(stderr, "Exited with status: %d", WEXITSTATUS(status));
			return WEXITSTATUS(status);
		}
    }
    return 0;
}

//open tel://+7207759346 --background

int main(int argc, char *argv[]){
    
    return make_call(argv);

}