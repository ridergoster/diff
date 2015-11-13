#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"

int main(int argc, char** argv)
{
    if(argc < 3){
        printf("ERROR FILE");
        return 1;
    }

    //Index of file by default
    int index_file_1 = 1;
    int index_file_2 = 2;
    int i;

    //Get the option of function
    for(i = 1 ; i < argc ; i++){
      if(argv[i][0] == '-'){
        printf("%s\n",argv[i]);
      }
      // Index of file 2
      else if(index_file_1 != 1){
        index_file_2 = i;
        printf("index file2 :%d\n",index_file_2);
      }
      // Index of file 1
      else{
        index_file_1 = i;
        printf("index file1 : %d\n",index_file_1);
      }
    }

    t_file* file_1 = file_create(argv[index_file_1]);

    t_file* file_2 = file_create(argv[index_file_2]);

    //printf("Line 3 : \n%s\n",get_line(file_1,2));

    //file_print(file_1);

}
