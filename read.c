#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"common.h"
#include"read.h"

void display_error()
{

}
int big_to_little(int value)
{
    return  ((value & 0xFF000000) >> 24) |((value & 0x00FF0000) >> 8) |((value & 0x0000FF00) << 8) |((value & 0x000000FF) << 24);
}
void display(Data *data)
{
    printf("\n-------------------MP3 Reader-------------------------\n\n");
    printf("Artist Name : %s\n",data->artist);
    printf("Song Name : %s\n",data->name);
    printf("Album Name : %s\n",data->album);
    printf("Year : %s\n",data->year);
    printf("Content Type : %s\n",data->content_type);
    printf("Composer : %s\n",data->composer);
    printf("---------------------------------------------------------\n");


}
Status do_reading(Data *data,char tags[][5],File *file)
{
    fseek(file->fptr,10,SEEK_SET);
    for(int i = 0;i < 6;i++)
    {
        char temp[5];
        fread(temp,4,1,file->fptr);
        //printf("%s\n",temp);
        int size;
        fread(&size,4,1,file->fptr);
        size = big_to_little(size);
        //printf("%d\n",size);
        if(strcmp(temp,tags[2]) == 0)
        {
            data->album = (char *)malloc(size);
            fseek(file->fptr,3,SEEK_CUR);
            fread(data->album,(size -1),1,file->fptr);
            //printf("%s\n",data->album);
        }
        else if(strcmp(temp,tags[0]) == 0)
        {
            data->artist = (char *)malloc(size);
            fseek(file->fptr,3,SEEK_CUR);
            fread(data->artist,(size -1),1,file->fptr);
            //printf("%s\n",data->artist);
        }
        else if(strcmp(temp,tags[1]) == 0)
        {
            data->name = (char *)malloc(size);
            fseek(file->fptr,3,SEEK_CUR);
            fread(data->name,(size -1),1,file->fptr);
            //printf("%s\n",data->name);
        }
        else if(strcmp(temp,tags[3]) == 0)
        {
            data->year = (char *)malloc(size);
            fseek(file->fptr,3,SEEK_CUR);
            fread(data->year,(size -1),1,file->fptr);
            //printf("%s\n",data->year);
        }
        else if(strcmp(temp,tags[4]) == 0)
        {
            data->content_type = (char *)malloc(size);
            fseek(file->fptr,3,SEEK_CUR);
            fread(data->content_type,(size -1),1,file->fptr);
            //printf("%d\n",ftell(file->fptr));
        }
        else if(strcmp(temp,tags[5]) == 0)
        {
            printf("%s\n",temp);
            printf("%d\n",size);
            data->composer = (char *)malloc(size);
            fseek(file->fptr,3,SEEK_CUR);
            fread(data->composer,(size -1),1,file->fptr);
            //printf("%d %d %s\n",ftell(file->fptr),fread(data->composer,1,(size-1),file->fptr),data->composer);
        }
    }
    //display(data);
    return success;

}