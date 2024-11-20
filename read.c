#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"common.h"
#include"read.h"

void display_error()
{
    //function print error message

}
int big_to_little(int value)
{
    //function to convert bigendian to little endian
    return  ((value & 0xFF000000) >> 24) |((value & 0x00FF0000) >> 8) |((value & 0x0000FF00) << 8) |((value & 0x000000FF) << 24);
}
void display(Data *data)
{
    //function to display 
    printf("\n-------------------MP3 Reader-------------------------\n\n");
    printf("Artist Name   : %s\n",data->artist);
    printf("Song Name     : %s\n",data->name);
    printf("Album Name    : %s\n",data->album);
    printf("Year          : %s\n",data->year);
    printf("Content Type  : %s\n",data->content_type);
    printf("Composer      : %s\n",data->composer);
    printf("---------------------------------------------------------\n");


}
Status do_reading(Data *data,char tags[][5],File *file)
{
    //function to reaf tags
    fseek(file->fptr,10,SEEK_SET);//skip the 10bit header
    for(int i = 0;i < 6;i++)
    {
        char temp[5];//to store tag
        fread(temp,4,1,file->fptr);//read tag
        
        int size;
        fread(&size,4,1,file->fptr);//read size
        size = big_to_little(size);//convert big endian to little endian
        //printf("%d\n",size);
        //compare the tags and store to struct
        if(strcmp(temp,tags[2]) == 0)
        {
            data->album = (char *)malloc(size);//allocate memory for size number of  times
            fseek(file->fptr,3,SEEK_CUR); //move file pointer 3 position from CUR -for 2flags and 1null
            fread(data->album,(size -1),1,file->fptr); //read size-1 data
            
        }
        else if(strcmp(temp,tags[0]) == 0)
        {
            data->artist = (char *)malloc(size);//allocate memory for size number of  times
            fseek(file->fptr,3,SEEK_CUR); //move file pointer 3 position from CUR -for 2flags and 1null
            fread(data->artist,(size -1),1,file->fptr);//read size-1 data
       
        }
        else if(strcmp(temp,tags[1]) == 0)
        {
            data->name = (char *)malloc(size);//allocate memory for size number of  times
            fseek(file->fptr,3,SEEK_CUR);  //move file pointer 3 position from CUR -for 2flags and 1null
            fread(data->name,(size -1),1,file->fptr);//read size-1 data
      
        }
        else if(strcmp(temp,tags[3]) == 0)
        {
            data->year = (char *)malloc(size);//allocate memory for size number of  times
            fseek(file->fptr,3,SEEK_CUR);  //move file pointer 3 position from CUR -for 2flags and 1null
            fread(data->year,(size -1),1,file->fptr);//read size-1 data
          
        }
        else if(strcmp(temp,tags[4]) == 0)
        {
            data->content_type = (char *)malloc(size);//allocate memory for size number of  times
            fseek(file->fptr,3,SEEK_CUR);  //move file pointer 3 position from CUR -for 2flags and 1null
            fread(data->content_type,(size -1),1,file->fptr);//read size-1 data
        }
        else if(strcmp(temp,tags[5]) == 0)
        {
            
            data->composer = (char *)malloc(size);//allocate memory for size number of  times
            fseek(file->fptr,3,SEEK_CUR);  //move file pointer 3 position from CUR -for 2flags and 1null
            fread(data->composer,(size -1),1,file->fptr);//read size-1 data
           
        }
    }
    return success;

}