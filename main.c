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

    //Index of file by default
    int index_file_1 = 1;
    int index_file_2 = 2;
    int i;

    //Get the option of function
    for(i = 1 ; i < argc ; i++)
    {
        if(argv[i][0] == '-')
        {
            printf("%s\n",argv[i]);
        }
        // Index of file 2
        else if(index_file_1 != 1)
        {
            index_file_2 = i;
            printf("index file2 :%d\n",index_file_2);
        }
        // Index of file 1
        else
        {
            index_file_1 = i;
            printf("index file1 : %d\n",index_file_1);
        }
    }

    t_file* file_1 = file_create(argv[index_file_1]);

    t_file* file_2 = file_create(argv[index_file_2]);


    //printf("Line 3 : \n%s\n",get_line(file_1,2));

    //file_print(file_1);

    int option_q=0; //report if diff
    int option_s=0; //report identical file
    int option_i=0; //ignore different case
    int option_w=0; // ignore all space

    int k;
    for(k=1; k<argc; k++)
    {
        if(strcmp(argv[k], "-i") == 0 || strcmp(argv[k], "--ignore-case") == 0)
        {
            option_i = 1;
        }
        if(strcmp(argv[k], "--help") == 0)
        {
            //appeler fichier du man
            return 0; //end of the programm now
        }
        if(strcmp(argv[k], "-w") == 0 || strcmp(argv[k], "--ignore-all-space") == 0)
        {
            option_w = 1;
        }
        if(strcmp(argv[k], "-s") == 0 || strcmp(argv[k], "--report-identical-files") == 0)
        {
            option_s = 1;
        }
        if(strcmp(argv[k], "-q") == 0  || strcmp(argv[k], "--brief") == 0)
        {
            option_q = 1;
        }
    }

    if(1==option_i)
    {
        file_1 = to_lower_case(file_1);
        file_2 = to_lower_case(file_2);
    }
    if(1==option_q)
    {
        if(1==is_file_different(file_1,file_2))
            printf("different");
    }
    if(1==option_s)
    {
        if(is_file_different(file_1,file_2))
            printf("same");
    }
    if(1==option_w)
    {
        file_1=ignore_blank(file_1);
        file_2=ignore_blank(file_2);
    }

    if(0 == option_s && 0==option_q)
    {

        int max_nb_line;
        if(file_1->nb_line<file_2->nb_line)
            max_nb_line = file_2->nb_line;
        else
            max_nb_line = file_1->nb_line;

        for(i=0; i<max_nb_line; i++)
        {
            int j;
            for(j=0; j<file_2->nb_line; j++)
            {
                char * line1;
                if(i<=max_nb_line) //si le nombre de ligne du fichier 1 est moins important que dans le fichier 2
                {
                    char * line1 = (char *)malloc(sizeof(char)*file_1->size_line[i]);
                    line1 = get_line(file_1,i);
                }
                else
                    line1 ="";//pour ne pas avoir de line1 pas initialisé si le fichier 1 contient moins de ligne que le 2
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
                free(line1);
                free(line2);
            }
        }
    }
    free(file_1);
    free(file_2);
    return 0;
}
