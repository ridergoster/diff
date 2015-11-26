#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"
#include <string.h>


// function for help
static void usage ()
{
    static char const * const option_help[] =
    {
        "-q  --brief  Output only whether files differ.",
        "-s  --report-identical-files  Report when two files are the same.",
        "-i  --ignore-case  Consider upper- and lower-case to be the same.",
        "-w  --ignore-all-space  Ignore all white space.",
        "--help  Output this help.",
        "-v  --version  Output version info.",
        0
    };

    char const * const *p = option_help;

    printf ("Usage: %s [OPTION]... FILE1 FILE2\n\n", "diff");
    for (p = option_help;  *p;  p++)
        printf ("  %s\n", *p);
}

// function for version
static void version()
{
    printf("\n version: v0alpha \n");
}

// main of the project
int main(int argc, char** argv)
{
    //Init variable
    int index_file_1 = 0;
    int index_file_2 = 2;
    int i = 0;
    int option_q=0; //report brief
    int option_s=0; //report identical file
    int option_i=0; //ignore different case
    int option_w=0; //ignore all space
    int option_h=0; //show help
    int option_v=0; //show version
    int option_b=0; //ignore space change
    int option_E=0; //ignore tabulation
    //Get the option of function
    for(i = 1 ; i < argc ; i++)
    {
        //Param is an option starting with '-'
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
                option_h = 1;
            }
            // if param is version
            if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0)
            {
                option_v = 1;
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
            // if param is ignore space change
            if(strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--ignore-space-change") == 0)
      			{
      				option_b = 1;
      			}
            // if param is ignore tabulation
      			if(strcmp(argv[i], "-E") == 0 || strcmp(argv[i], "--ignore-tab-expansion") == 0)
      			{
      				option_E = 1;
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

    // exit for --help -h -v & error in param
    if (option_h)
    {
        usage();
        version();
        return 0;
    }
    else if (option_v)
    {
        version();
        return 0;
    }
    else if(argc < 3)
    {
        printf("/!\\ ERROR /!\\ \n ");
        usage();
        return 1;
    }
    // We create the two file to show
    t_file* file_1 = file_create(argv[index_file_1]);
    t_file* file_2 = file_create(argv[index_file_2]);

    // We create the two file to compare
    t_file* file_1_modif = file_create(argv[index_file_1]);
    t_file* file_2_modif = file_create(argv[index_file_2]);

    // We do modification on file depending of option
    if(1==option_i)
    {
        file_1_modif = to_lower_case(file_1_modif);
        file_2_modif = to_lower_case(file_2_modif);
    }
    if(1==option_w)
    {
        file_1_modif=ignore_blank(file_1_modif);
        file_2_modif=ignore_blank(file_2_modif);
    }
    if(1==option_b)
    {
        file_1_modif=str_onespace(file_1_modif);
        file_2_modif=str_onespace(file_2_modif);
    }
     if(1==option_E)
    {
        file_1_modif=str_onetab(file_1_modif);
        file_2_modif=str_onetab(file_2_modif);
    }

    // We do a boolean comparaison or a detail show
    if(1==option_q)
    {
        if(is_file_different(file_1_modif,file_2_modif))
        {
          printf("Files %s and %s differ\n",argv[index_file_1],argv[index_file_2]);
          return 1;
        }
        else
        {
          return 0;
        }
    }
    else if(1==option_s)
    {
        if(!is_file_different(file_1_modif,file_2_modif))
        {
          printf("Files %s and %s are identical\n",argv[index_file_1],argv[index_file_2]);
          return 0;
        }
        else
        {
          file_compare(file_1_modif,file_2_modif,file_1,file_2);
          return 1;
        }
    }
    else
    {
        file_compare(file_1_modif,file_2_modif,file_1,file_2);
        if(!is_file_different(file_1_modif,file_2_modif))
          return 0;
        else
          return 1;
    }

    free(file_1);
    free(file_2);
    free(file_1_modif);
    free(file_2_modif);

    return 2;
}
