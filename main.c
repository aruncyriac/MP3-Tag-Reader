#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"read.h"
#include"common.h"

int main(int argc,char *argv[])
{
    char tags[6][5] = {"TPE1","TIT2","TALB","TYER","TCON","COMM"};
    Operation op;
    File file;
    Data *data = (Data *)malloc(sizeof(Data));
    if(op == read)
    {
        if(argc > 2)
        {
            file.file_name = argv[2];
            file.fptr = fopen(file.file_name,"r");
            if(file.fptr == NULL)
            {
                printf("ERROR:FILE NOT OPENED");
                return 0;
            }
            if(do_reading(data,tags,&file) == success)
            {
                display(data);
            }
        }
    }
    else if(op == write)
    {
        //write data
    }
    else 
    {
        display_error();
        return 0;
    }
    free(data->album);
    free(data->artist);
    free(data->name);
    free(data->year);
    free(data->content_type);
    free(data->composer);
    free(data);

}
Operation check_operation(char *argv)
{
    if(strcmp(argv,"-r") == 0)
    {
        return read;
    }
    if(strcmp(argv,"-w") == 0)
    {
        return write;
    }
    if(strcmp(argv,"-h") == 0)
    {
        return help;
    }
    return help;
}
