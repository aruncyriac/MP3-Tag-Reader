#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"read.h"
#include"common.h"
#include"edit.h"

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
     printf("%s\n",file->file_name);
    file->fptr = fopen(file->file_name,"r");
    file->fptr_temp = fopen("temp","w");
    printf("hi1\n");
    if(file->fptr == NULL && file->fptr_temp == NULL)
    {
        printf("ERROR:File not opened\n");
        return failure;
    }
    else
    {
        char temp[11];
        printf("hi\n");
        
        printf("hi2\n");
        if(fread(temp,10,1,file->fptr) == fwrite(temp,10,1,file->fptr_temp))
        {
            printf("INFO:Header copied successfully\n");
            
        }
        else
        {
             printf("hi\n");
            printf("ERROR:Failed to copy header\n");
            return failure;
        }
        if(is_found(file) == success)
        {
            
            return success;
        }
    }
}
Status is_found(File *file)
{
    
    //char temp[5];
    int size;
    for(int i = 0;i < 1;i++)
    {
        char temp[5];
        fread(temp,4,1,file->fptr);
        printf("%c\n",temp[3]);
        
        fread(&size,4,1,file->fptr);
        
        fseek(file->fptr,3,SEEK_CUR);
        
        size = big_to_little(size);
        printf("%d\n",size);
        
        if(strcmp(temp,file->tag) == 0)
        {
            printf("%s %s\n",temp,file->tag);
        }
    }
    return success;
}