#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* The first argument of open_file is 'r' or 'w', which stand for read or 
 * write option.
 * */
unsigned int open_file(int option, const char *file_name){
    char path[PATH_MAX] = {0};
    unsigned int ret_fd = 0;
    if(option == 'r'){
        if(!getcwd(path, PATH_MAX)){
            perror("getcwd in open_file");
            exit(1);
        }
        else{
            strcat(path, "/");
            strcat(path, file_name);
            if((ret_fd = open(path, O_RDONLY)) == -1){
                perror(file_name);
                exit(1);
            }
        }
    }
    if(option == 'w'){
        if(!getcwd(path, PATH_MAX)){
            perror("getcwd in open_file");
            exit(1);
        }
        else{
            if(!file_name)
                ret_fd = 1;
            else{
                strcat(path, "/");
                strcat(path, file_name);
                if((ret_fd = creat(path, S_IRUSR | S_IWUSR)) == -1){
                    perror(file_name);
                    exit(1);
                }
            }
        }
    }
    return ret_fd;
}
