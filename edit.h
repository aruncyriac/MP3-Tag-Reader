#ifndef EDIT_H
#define EDIT_H
#include"common.h"

Status read_validate(char *argv[],int argc,char *tag,char tags [][5]); //function to validate the CLA's 
Status do_editing(File *file,char *tag); //function to editing
Status is_found(File *file); //function to find tag
Status copy_remaining(File *file);//function to copy the remaining data to file

#endif