#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>

/* The first argument of open_file is 'r' or 'w', which stand for read or 
 * write option.
 * */
unsigned int open_file(int option, const char *file_name){
    char path[PATH_MAX];
    unsigned int r_fd = 0;
    if(option == 'r'){
        if(!getcwd(path, PATH_MAX)){
            perror("open_file");
            exit(1);
        }
        else{
            printf("Read file's path is: %s\n", path);
        }
    }
    if(option == 'w'){
        if(!path){

        }
    }
    return r_fd;
}
