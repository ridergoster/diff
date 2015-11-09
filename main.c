#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"

int main(int argc, char** argv)
{

    t_file* file = file_create(argv[1]);

    file_print(file);

}
