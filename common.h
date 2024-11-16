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
    FILE *fptr;
}File;

    


Operation check_operation(char *argv);
void display_error();
#endif