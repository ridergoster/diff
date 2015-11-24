/* ManPage Full

                "-i  --ignore-case  Consider upper- and lower-case to be the same.",
                "-w  --ignore-all-space  Ignore all white space.",
                "-b  --ignore-space-change  Ignore changes in the amount of white space.",
                "-B  --ignore-blank-lines  Ignore changes whose lines are all blank.",
                "-I RE  --ignore-matching-lines=RE  Ignore changes whose lines all match RE.",
                #if HAVE_SETMODE
                "--binary  Read and write data in binary mode.",
                #endif
                "-a  --text  Treat all files as text.\n",
                "-c  -C NUM  --context[=NUM]  Output NUM (default 2) lines of copied context.",
                "-u  -U NUM  --unified[=NUM]  Output NUM (default 2) lines of unified context.",
                "  -NUM  Use NUM context lines.",
                "  -L LABEL  --label LABEL  Use LABEL instead of file name.",
                "  -p  --show-c-function  Show which C function each change is in.",
                "  -F RE  --show-function-line=RE  Show the most recent line matching RE.",
                "-q  --brief  Output only whether files differ.",
                "-e  --ed  Output an ed script.",
                "-n  --rcs  Output an RCS format diff.",
                "-y  --side-by-side  Output in two columns.",
                "  -w NUM  --width=NUM  Output at most NUM (default 130) characters per line.",
                "  --left-column  Output only the left column of common lines.",
                "  --suppress-common-lines  Do not output common lines.",
                "-DNAME  --ifdef=NAME  Output merged file to show `#ifdef NAME' diffs.",
                "--GTYPE-group-format=GFMT  Similar, but format GTYPE input groups with GFMT.",
                "--line-format=LFMT  Similar, but format all input lines with LFMT.",
                "--LTYPE-line-format=LFMT  Similar, but format LTYPE input lines with LFMT.",
                "  LTYPE is `old', `new', or `unchanged'.  GTYPE is LTYPE or `changed'.",
                "  GFMT may contain:",
                "    %<  lines from FILE1",
                "    %>  lines from FILE2",
                "    %=  lines common to FILE1 and FILE2",
                "    %[-][WIDTH][.[PREC]]{doxX}LETTER  printf-style spec for LETTER",
                "      LETTERs are as follows for new group, lower case for old group:",
                "        F  first line number",
                "        L  last line number",
                "        N  number of lines = L-F+1",
                "        E  F-1",
                "        M  L+1",
                "  LFMT may contain:",
                "    %L  contents of line",
                "    %l  contents of line, excluding any trailing newline",
                "    %[-][WIDTH][.[PREC]]{doxX}n  printf-style spec for input line number",
                "  Either GFMT or LFMT may contain:",
                "    %%  %",
                "    %c'C'  the single character C",
                "    %c'\\OOO'  the character with octal code OOO\n",
                "-l  --paginate  Pass the output through `pr' to paginate it.",
                "-t  --expand-tabs  Expand tabs to spaces in output.",
                "-T  --initial-tab  Make tabs line up by prepending a tab.\n",
                "-r  --recursive  Recursively compare any subdirectories found.",
                "-N  --new-file  Treat absent files as empty.",
                "-P  --unidirectional-new-file  Treat absent first files as empty.",
                "-s  --report-identical-files  Report when two files are the same.",
                "-x PAT  --exclude=PAT  Exclude files that match PAT.",
                "-X FILE  --exclude-from=FILE  Exclude files that match any pattern in FILE.",
                "-S FILE  --starting-file=FILE  Start with FILE when comparing directories.\n",
                "--horizon-lines=NUM  Keep NUM lines of the common prefix and suffix.",
                "-d  --minimal  Try hard to find a smaller set of changes.",
                "-H  --speed-large-files  Assume large files and many scattered small changes.\n",
                "-v  --version  Output version info.",
                "--help  Output this help.",
                0
                };

End ManPage */


#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"
#include <string.h>



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

static void version()
{
    printf("\n version: v0alpha \n");
}


int main(int argc, char** argv)
{
    //Init variable
    int index_file_1 = 0;
    int index_file_2 = 2;
    int i = 0;
    int j = 0;
    int option_q=0; //report if diff
    int option_s=0; //report identical file
    int option_i=0; //ignore different case
    int option_w=0; // ignore all space
    int option_h=0; // show help
    int option_v=0; // show version

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
                option_h = 1;
            }
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
    // +20151123 fgn except for --help & -h & -v
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


    if(0 == option_s && 0==option_q)
    {
        //printf("size 1:%d size 2:%d \n",file_1->nb_line,file_2->nb_line );
        //get_lcs(file_1,file_2);
        file_compare(file_1,file_2);
        //file_print(file_1);
    }

    free(file_1);
    free(file_2);
    return 0;
}
