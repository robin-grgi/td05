#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h> 
#include <string.h>

#include "util.h"

void list(char *);
void printFileinfo(char *);


int main(int argc, char *argv[]) {
    if(argc == 1){
        list("./");
    } else if( argc > 1){
        list(argv[1]);
    }
    return 0;
}

void list(char *fileName) {
    if(is_dir(fileName)) {
        DIR *dir = opendir(fileName);
        printf("%s\n", get_basename(fileName));
        struct dirent *dirEntry;
        while((dirEntry = readdir(dir)) != NULL) {
            printFileinfo(dirEntry->d_name);
        }
        printf("\n\n");
        rewinddir(dir);
        while((dirEntry = readdir(dir)) != NULL){
            
            if(dirEntry->d_type == DT_DIR && !is_dot_dir(dirEntry->d_name)){//la fonction is_dir ne retourne toujours faux :/
                char buffer[1024];
                snprintf(buffer, sizeof(buffer), "%s/%s", fileName, dirEntry->d_name);
                list(buffer);
            }
        }
        closedir(dir);
    } else {
        printFileinfo(fileName);
    }
}

void printFileinfo(char *fileName) {
    printf("%s\t", get_basename(fileName));
}