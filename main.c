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

    int option_q=0;
    int option_s=0;
    int option_i=0;
    int option_w=0;

    int k;
    int cpt = 0; //total number of options
    for(k=1; k<argc; k++)
    {
        if(strcmp(argv[k], "-i") == 0 || strcmp(argv[k], "--ignore-case") == 0)
        {
            option_i = 1;
            cpt++;
        }
        if(strcmp(argv[k], "--help") == 0)
        {
            //appeler fichier du man
            return 0; //end of the programm now
        }
        if(strcmp(argv[k], "-w") == 0 || strcmp(argv[k], "--ignore-all-space") == 0)
        {
            option_w = 1;
            cpt++;
        }
        if(strcmp(argv[k], "-s") == 0 || strcmp(argv[k], "--report-identical-files") == 0)
        {
            option_s = 1;
            cpt++;
        }
        if(strcmp(argv[k], "-q") == 0  || strcmp(argv[k], "--brief") == 0)
        {
            option_q = 1;
            cpt++;
        }
    }

if(1==option_i)
{

}
if(1==option_q)
{

}
if(1==option_s)
{

}
if(1==option_w)
{

}


 free(file_1);
 free(file_2);
 return 0;
}
