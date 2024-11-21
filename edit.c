#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"read.h"
#include"common.h"
#include"edit.h"

Status read_validate(char *argv[],int argc,char *tag,char tags [][5])
{
    //function to validate the CLA's
    if(argc == 4)
    {
        if(strstr(argv[2],".mp3") != NULL)
        { //if the file is mp3
            //checking the tag which to be edited
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
            //error handling
            printf("ERROR:File is not Mp3\n");
            return failure;
        }
    }
    else
    {
        //error handling
        return failure;
    }
}
Status do_editing(File *file,char *tag)
{
    //function to do editing
    file->fptr = fopen(file->file_name,"r");//open the given file in read mode
    file->fptr_temp = fopen("temp.mp3","w"); // open a temp file in write mode
    if(file->fptr == NULL && file->fptr_temp == NULL)
    {
        //error handling
        printf("ERROR:File not opened\n");
        return failure;
    }
    else
    {
        //if both the files are open successfully
        char temp[11]; //to store header
        if(fread(temp,10,1,file->fptr) == fwrite(temp,10,1,file->fptr_temp))
        {
            //copying header to the temp file
            printf("INFO:Header copied successfully\n");
            
        }
        else
        {
            //error handling
            printf("ERROR:Failed to copy header\n");
            return failure;
        }
        if(is_found(file) == success)
        {
            //if the tag is edited
            printf("INFO:Data edited sucessfully\n");
        }
        else
        {
            //eroor handling
            return failure;
        }
        if(copy_remaining(file) == success)
        {
            //copying the remaining data
            printf("INFO:Copied remaining data successfully\n");
            return success;
        }
    }
}
Status is_found(File *file)
{
    //function to edit the tag
    int size; //temp variable to store size
    for(int i = 0;i < 6;i++)
    {
        char temp[5]; //temp array to store the tag name
        char n[3] = {'\0','\0','\0'}; //to store flag
        char *str; //to store new data
        fread(temp,4,1,file->fptr);//read tag from the file
        fread(&size,4,1,file->fptr);//read size from the file
        fread(n,3,1,file->fptr); //read flags from the file
        size = big_to_little(size); //conert size to little endians
        if(strcmp(temp,file->tag) == 0)
        {
            //if tag match
            int nsize;
            fseek(file->fptr,size-1,SEEK_CUR);//skip the orginal data
            fwrite(temp,4,1,file->fptr_temp);//write the tag to temp file
            str = (char*)malloc(100); //allocate 100 bit of size
            printf("Enter the new Data : ");
            scanf("%99[^\n]",str); //enter new data
            size = strlen(str); ///find the new length
            nsize = big_to_little(size); //convert the new size in big endians
            fwrite(&nsize,4,1,file->fptr_temp);//write size to temp file
            fwrite(n,3,1,file->fptr_temp);//write flag to temp file
            fwrite(str,size-1,1,file->fptr_temp);//write new data to temp file
            free(str); //free the str
            return success;   
        }
        else
        {
            //if tag not found
            int nsize;
            fwrite(temp,4,1,file->fptr_temp);//write tag to temp file
            nsize = big_to_little(size); //convert the size to big endian
            fwrite(&nsize,4,1,file->fptr_temp);//write size to temp file
            fwrite(n,3,1,file->fptr_temp); //write flag to temp file
            //copy the data to temp
            char ch;
            for(int i = 0;i < size-1;i++)
            {
                if(fread(&ch,1,1,file->fptr))
                {
                    fwrite(&ch,1,1,file->fptr_temp);
                }
            }
        }
    }
    //if tag not found
    return failure;
}
Status copy_remaining(File *file)
{
    int pos = ftell(file->fptr); //store current postion to pos
    int npos; 
    fseek(file->fptr,0,SEEK_END);//finding size of the file
    npos = ftell(file->fptr) - pos; //finding the size of remaining data
    //rewind(file->fptr);
    fseek(file->fptr,pos,SEEK_SET);//reset the file pointer to pos
    char *temp = (char*)malloc(npos+1); //allocate memory for npos bit
    fread(temp,npos,1,file->fptr); //read the remaining data
    fwrite(temp,npos,1,file->fptr_temp);//write the remaining data to temp file
    free(temp); //free the temp
    //closing of file
    fclose(file->fptr);
    fclose(file->fptr_temp);

    //copying to orginal file
    //opening the file
    file->fptr = fopen(file->file_name,"w"); //open original file in write mode
    file->fptr_temp = fopen("temp.mp3","r");//open temp file in read mode
    fseek(file->fptr_temp,0,SEEK_END); //file pointer to end of the file
    pos = ftell(file->fptr_temp); //read the size of the file
    rewind(file->fptr_temp); //move file pointer to the begeining
    temp = (char*)malloc(pos+1); //allocate memory for pos bit
    fread(temp,pos,1,file->fptr_temp); //read from temp.mp3
    fwrite(temp,pos,1,file->fptr); //write to org orginal.mp3
    free(temp); //free the temp
    //closing the file
    fclose(file->fptr);
    fclose(file->fptr_temp);
    return success;
    
}