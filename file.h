#ifndef FILE_H
#define FILE_H
int open_file(int , const char *);
void header_gen(const uint32_t *, int);
void body_gen(char **, int, int);
void get_c_to_arr(int , int *);

#endif
