#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"

int main(int argc, char** argv)
{
    if(argc < 2){
        printf("ERROR FILE");
        return 1;
    }

    t_file* file = file_create(argv[1]);
    
    printf("Line 3 : \n%s\n",get_line(file,2));

    file_print(file);

}
