#ifndef COMMON_H
#define COMMON_H
typedef enum
{
    success,
    failure,
}Status;
typedef enum
{
    read,
    write,
    help,
}Operation;
typedef struct 
{
    char *file_name;
    char *tag;
    FILE *fptr;
    FILE *fptr_temp;
}File;
//function to check operation type
Operation check_operation(char *argv);
//function to display error message
void display_error();
#endif