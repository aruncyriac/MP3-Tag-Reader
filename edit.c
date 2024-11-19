#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"read.h"
#include"common.h"

Status read_validate(char *argv[],int argc,char *tag,char tags [][5])
{
    if(argc == 4)
    {
        if(strstr(argv[2],".mp3") != NULL)
        {
            if(strcmp(argv[3],"-t") == 0)
            {
                strcpy(tag, tags[1]);
            }
            else if(strcmp(argv[3],"-a") == 0)
            {
                strcpy(tag, tags[0]);
            }
            else if(strcmp(argv[3],"-A") == 0)
            {
                strcpy(tag, tags[2]);
            }
            else if(strcmp(argv[3],"-y") == 0)
            {
                strcpy(tag, tags[3]);
            }
            else if(strcmp(argv[3],"-c") == 0)
            {
                strcpy(tag, tags[4]);
            }
            else if(strcmp(argv[3],"-C") == 0)
            {
                strcpy(tag, tags[5]);
            }
            else
            {
                return failure;
            }
            //printf("%s\n",tag);
            return success;
        }
        else
        {
            printf("ERROR:File is not Mp3\n");
            return failure;
        }
    }
    else
    {
        return failure;
    }
}
Status do_editing(File *file,char *tag)
{
    
}