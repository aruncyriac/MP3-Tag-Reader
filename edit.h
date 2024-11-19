#ifndef EDIT_H
#define EDIT_H
#include"common.h"

Status read_validate(char *argv[],int argc,char *tag,char tags [][5]);
  
Status do_editing(File *file,char *tag);

#endif