#ifndef READ_H
#define READ_H
#include"common.h"
typedef struct
{
    //structure to store the data
    char *artist;
    char *name;
    char *album;
    char *year;
    char *content_type;
    char *composer;
}Data;
Status do_reading(Data *data,char tags[][5],File *file);//function to read the mp3 data
int big_to_little(int size); //function to convert big endines to little endines
void display(Data *data); //function to display data
#endif