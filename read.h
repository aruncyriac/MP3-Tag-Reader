#ifndef READ_H
#define READ_H
#include"common.h"
typedef struct
{
    char *artist;
    char *name;
    char *album;
    char *year;
    char *content_type;
    char *composer;
}Data;
Status do_reading(Data *data,char tags[][5],File *file);
int big_to_little(int size);
void display(Data *data);
#endif