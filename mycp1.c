#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "util.h"


int main(int argc, char const *argv[])
{
    if(argc < 3){
        fprintf(stderr, "not enough args !\n");
        return 1;
    } else if(argc == 3) {
        char *buffer = (char *) malloc(1024 * sizeof(char));
        int readValue;
        int fdSource = open(argv[1], O_RDONLY);
        int fdDest = open(argv[2], O_WRONLY | O_CREAT);
        while((readValue = read(fdSource, buffer, 1024))){
            write(fdDest, buffer, readValue);
        }
        close(fdSource);
        close(fdDest);
        free(buffer);
    } else {
        for(int i = 1 ; i < argc - 1 ; i++){
            char *buffer = (char *) malloc(1024 * sizeof(char));
            int readValue;
            int fdSource = open(argv[i], O_RDONLY);
            char *fullPathDest = (char *) malloc(1024 * sizeof(char));
            strcat(fullPathDest, argv[argc-1]);
            strcat(fullPathDest, "/");
            strcat(fullPathDest, get_basename(argv[i]));
            int fdDest = open(fullPathDest, O_WRONLY | O_CREAT);
            while((readValue = read(fdSource, buffer, 1024)) != 0){
                write(fdDest, buffer, readValue);
            }
            close(fdSource);
            close(fdDest);
            free(fullPathDest);
            free(buffer);
        }
    }
    return 0;
}
