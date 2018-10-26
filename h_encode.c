#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include "htable_func.h"
#include "file.h"
int main(const int argc, const char *argv[]){
    const int SIZE = 256;
    unsigned int fd_r = 0, fd_w = 0;
    int array[ASCII_SIZE] = {0};
    char buf[ASCII_SIZE] = {0}; 
    char **h_table;
    uint8_t i = 0;
    node *list, *tree;
    fd_r = open_file('r', argv[1]);
    fd_w = open_file('w', argv[2]);
    while(read(fd_r, buf, ASCII_SIZE)){
        for(i = 0; i < SIZE && buf[i]; ++i){
            if(buf[i])
                char_to_array(buf[i], array);
        }
    }
    list = array_to_list(array);
    if(list){  
        tree = sort_tree(list);
        h_table = tree_to_h_table(tree);
        if(fd_w){
            header_gen((const uint32_t *)array, fd_w);  
            clean_tree(tree);
        }
    }
    close(fd_r);
    close(fd_w);
    return 0;
}
