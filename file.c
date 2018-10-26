#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "htable_func.h"
#define FOUR_BYTE 4
#define ONE_BYTE 1
#define ERR_CODE -1

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

void header_gen(const uint32_t *array, int fd_w){
    const uint8_t SIZE = 255;
    uint32_t c_count = 0;
    for(int i = 0; i < ASCII_SIZE; ++i){
        if(array[i])
            c_count++;
    }
    write(fd_w, &c_count, FOUR_BYTE);
    for(uint8_t i = 0; i <= SIZE; ++i){
        if(array[i]){
            write(fd_w, &i, ONE_BYTE);
            write(fd_w, &array[i], FOUR_BYTE);
        }
    }
}
