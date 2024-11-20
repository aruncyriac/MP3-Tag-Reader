#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"read.h"
#include"common.h"
#include"edit.h"

int main(int argc,char *argv[])
{
    char tags[6][5] = {"TPE1","TIT2","TALB","TYER","TCON","COMM"};//2d array to store tag names
    char tag[5]; //to store a tag name
    Operation op; //enum to store operation type
    File file; //structure to store file pointer file name
    Data *data = (Data *)malloc(sizeof(Data)); //structrue pointer to store tag data
    //error handling
    if(argc == 1)
    {
        display_error();
        return 0;
    }
    op = check_operation(argv[1]); //check opertaion type from command line argument
    if(op == read)
    {
        //if option selected is read
        if(argc > 2)
        {
            //if passed two command line arguments
            file.file_name = argv[2];//copy argv[2] to file name
            //errror handling
            if(strstr(file.file_name,".mp3") == NULL)
            {
                printf("ERROR:Invalid file format\n");
                return 0;
            }
            file.fptr = fopen(file.file_name,"r");//open file
            //errror handling
            if(file.fptr == NULL)
            {
                printf("ERROR:FILE NOT OPENED");
                display_error();//display error message
                return 0;
            }
            if(do_reading(data,tags,&file) == success)
            {
                //if reading is success
                display(data); //dispaly data
                fclose(file.fptr);//close the file
                return 0;
            }
        }
        else
        {
            //error handling
            printf("ERROR:Enter the file name\n\n");
            display_error();
            return 0;
        }
    }
    else if(op == write)
    {
        if(argc > 1) //checking CLA has more than one argument
        {
            if(read_validate(argv,argc,tag,tags) == success) //validate the file
            {
                file.file_name = argv[2]; //copy the file name
                file.tag = tag; //copy the tag name
                
                if(do_editing(&file,tag) == success) //editing is successfull
                {
                    printf("INFO:Tag %s edited successfull\n",tag);
                    return 0;
                }
                else
                {
                    //error handling
                    printf("ERROR:Failed to edit\n");
                    return 0;
                }
            }
            else
            {
                //error handling 
                printf("ERROR:Invalid input for -w\n");
                display_error();
            }
        }
        else
        {
            //error handling 
            printf("ERROR:Invalid opereation\n");
            display_error();
        }
    }
    else 
    {
        //error handling 
        display_error();
        return 0;
    }
    //freeing all dynamically allocated memory
    free(data->album);
    free(data->artist);
    free(data->name);
    free(data->year);
    free(data->content_type);
    free(data->composer);
    free(data);

}
//function to check operation type
Operation check_operation(char *argv)
{
    if(strcmp(argv,"-r") == 0)//checking argument for read
    {
        return read;
    }
    if(strcmp(argv,"-w") == 0)//checking argument for write
    {
        return write;
    }
    if(strcmp(argv,"-h") == 0)//checking argument for help
    {
        return help;
    }
    return help;
}
