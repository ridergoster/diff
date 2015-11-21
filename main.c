#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"
#include <string.h>

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        printf("ERROR FILE");
        return 1;
    }

    //Init variable
    int index_file_1 = 0;
    int index_file_2 = 2;
    int i = 0;
    int j = 0;
    int option_q=0; //report if diff
    int option_s=0; //report identical file
    int option_i=0; //ignore different case
    int option_w=0; // ignore all space

    //Get the option of function
    for(i = 1 ; i < argc ; i++)
    {
        //Param is an option
        if(argv[i][0] == '-')
        {
          // if param is ignore case
          if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--ignore-case") == 0)
          {
              option_i = 1;
          }
          // if param is man help
          if(strcmp(argv[i], "--help") == 0)
          {
              //print the man help
              return 0; //end of the programm now
          }
          // if param is ignore space
          if(strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--ignore-all-space") == 0)
          {
              option_w = 1;
          }
          // if param is report same file
          if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--report-identical-files") == 0)
          {
              option_s = 1;
          }
          // if param is report brief result
          if(strcmp(argv[i], "-q") == 0  || strcmp(argv[i], "--brief") == 0)
          {
              option_q = 1;
          }
        }
        // Get the index of file 2
        else if(index_file_1 != 0)
        {
            index_file_2 = i;
        }
        // Get the index of file 1
        else
        {
            index_file_1 = i;
        }
    }

    // We create the two file to compare
    t_file* file_1 = file_create(argv[index_file_1]);
    t_file* file_2 = file_create(argv[index_file_2]);

    // We do modification on file depending of option
    if(1==option_i)
    {
        printf("we lower\n");
        file_1 = to_lower_case(file_1);
        file_2 = to_lower_case(file_2);

    }
    if(1==option_q)
    {
        if(is_file_different(file_1,file_2))
            printf("different\n");
    }
    if(1==option_s)
    {
        if(!is_file_different(file_1,file_2))
            printf("same\n");
    }
    if(1==option_w)
    {
        file_1=ignore_blank(file_1);
        file_2=ignore_blank(file_2);
    }


    /*

    A REVOIR

    if(0 == option_s && 0==option_q)
    {

        int max_nb_line;
        if(file_1->nb_line<file_2->nb_line)
            max_nb_line = file_2->nb_line;
        else
            max_nb_line = file_1->nb_line;

        for(i=0; i<max_nb_line; i++)
        {
            for(j=0; j<file_2->nb_line; j++)
            {
                char * line1;
                if(i<=max_nb_line) //si le nombre de ligne du fichier 1 est moins important que dans le fichier 2
                {
                    char * line1 = (char *)malloc(sizeof(char)*file_1->size_line[i]);
                    line1 = get_line(file_1,i);
                }
                else
                    line1 ="";//pour ne pas avoir de line1 pas initialis� si le fichier 1 contient moins de ligne que le 2
                char * line2 = (char *)malloc(sizeof(char)*file_2->size_line[j]);
                line2 = get_line(file_2,j);
                if(strcmp(line1,line2)==0)
                {
                    printf("= %s\n", line1);
                }
                if(strcmp(line1,line2))
                {
                    if(strcmp(line1,"")!=0)
                        printf("< %s\n", line1);
                    printf("> %s\n", line2);
                }
                //free(line1);
                //free(line2);
            }
        }
    }

    */

    file_compare(file_1,file_2);
    free(file_1);
    free(file_2);
    return 0;
}
