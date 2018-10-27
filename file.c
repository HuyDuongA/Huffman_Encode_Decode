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
#define BUFF_LENGTH 2

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
    uint32_t c_count = 0;
    uint8_t ch = 0;
    for(int i = 0; i < ASCII_SIZE; ++i){
        if(array[i])
            c_count++;
    }
    write(fd_w, &c_count, FOUR_BYTE);
    for(int i = 0; i < ASCII_SIZE; ++i){
        if(array[i]){
            write(fd_w, &ch, ONE_BYTE);
            write(fd_w, &array[ch], FOUR_BYTE);
        }
        ++ch;
    }
}

void body_gen(char **h_table, int fd_w, int fd_r){
    lseek(fd_r, 0, SEEK_SET);
    int ch = 0;
    char buf_r[ASCII_SIZE] = {0};
    uint8_t buf_w[BUFF_LENGTH] = {0};
    int buf_bit = 0;
    unsigned int byte_read = 0;
    while((byte_read = read(fd_r, buf_r, ASCII_SIZE))){
        for(unsigned int i = 0; i < byte_read; ++i){
            if(buf_r[i]){
                ch = buf_r[i];
            }
        }
    }
}

void get_c_to_arr(int fd_r, int *array){
    char buf[ASCII_SIZE] = {0};
    unsigned int byte_read = 0;
    while((byte_read = read(fd_r, buf, ASCII_SIZE))){
        for(int i = 0; i < byte_read; ++i){
            if(buf[i])
                char_to_array(buf[i], array);
        }
    }
}


