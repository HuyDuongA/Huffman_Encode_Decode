#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include "htable_func.h"
#include "file.h"

int main(const int argc, const char *argv[]){
    unsigned int fd_r = 0, fd_w = 0, byte_read = 0;
    int array[ASCII_SIZE] = {0}, buf[ASCII_SIZE] = {0}; 
    uint32_t *header;
    char **h_table;
    node *list, *tree;
    do{
        fd_r = open_file('r', argv[1]);
        fd_w = open_file('w', argv[2]);
        byte_read = read(fd_r, buf, ASCII_SIZE);
        for(int i = 0; i < ASCII_SIZE; ++i)
            char_to_array(buf[i], array);
        list = array_to_list(array);
        if(list){  
            tree = sort_tree(list);
            h_table = tree_to_h_table(tree);
            if(fd_w){
                header = header_gen(h_table);  
                clean_tree(tree);
            }
        }
    }
    while(byte_read);
    close(fd_r);
    close(fd_w);
    return 0;
}
