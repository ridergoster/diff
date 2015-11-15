#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"
#include <ctype.h>

// Create a t_file object from a .txt file
t_file* file_create(char* file_name)
{

    // Alloc memory for the file
    t_file* file = (t_file*)malloc(sizeof(t_file));

    // init variable
    FILE* f_file;
    int nb_line = 1;
    int char_ascii = 0;
    int nb_char = 0;
    int i;

    // if file is readable -> we can work !
    if ((f_file = fopen(file_name,"r")))
    {

        // get the number of line
        while((char_ascii=fgetc(f_file))!= EOF)
        {
            if(char_ascii==10)
                nb_line++;
        }

        // alloc the number of line
        file->size_line = (int*)malloc(sizeof(int)*nb_line);

        // Initialize the number of line in t_file
        file->nb_line = nb_line;

        // Initialize the size of each line at 0 in t_file
        for(i = 0; i < nb_line; i++)
        {
            file->size_line[i] = 0;
        }

        // Got back to init
        fseek(f_file,0,SEEK_SET);
        nb_char = 0;
        nb_line = 0;

        // Get the size of each line in t_file
        while((char_ascii=fgetc(f_file))!= EOF)
        {
            nb_char++;
            file->size_line[nb_line] = nb_char;
            if(char_ascii==10)
            {
                nb_line++;
                nb_char = 0;
            }
        }

        // Alloc the number of line in the lines object
        char** lines = (char **)malloc(sizeof(char*)*(nb_line+1));

        int i;
        // Alloc each line in the lines object
        for(i = 0 ; i < nb_line+1 ; i++)
        {
            char* line = (char *)malloc(sizeof(char)*file->size_line[i]*(nb_line+1));
            lines[i] = &line[i*file->size_line[i]];
        }

        // Put the lines object in the t_file
        file->lines = lines;

        // Got back to init
        fseek(f_file,0,SEEK_SET);
        nb_char = 0;
        nb_line = 0;

        // Get the every char of the txt in the t_file
        while((char_ascii=fgetc(f_file))!= EOF)
        {
            file->lines[nb_line][nb_char] = char_ascii;
            nb_char++;
            if(char_ascii==10)
            {
                nb_char = 0;
                nb_line++;
            }
        }

        // Work is done, close the file !
        fclose(f_file);
    }
    // return the t_file created
    return file;
}

//Print the t_file
void file_print(t_file* file)
{
    //init variable
    int i = 0;
    int j = 0;
    printf("\n------- PRINT FILE -------\n\n");
    //Print each line
    for(; i < file->nb_line; i++)
    {
        //Print each char
        for(j=0; j < file->size_line[i]; j++)
        {
            printf("%c",file->lines[i][j]);
        }
    }
    printf("\n------- END FILE -------\n");
}

t_file * to_lower_case(t_file* file)
{
    if(file)
    {
        int i;
        for(; i < file->nb_line; i++)
        {
            int j;
            for(j=0; j < file->size_line[i]; j++)
            {
                file->lines[i][j] = tolower(file->lines[i][j]);
            }
        }
    }
return file;
}

int is_file_different(t_file * file1, t_file * file2)
{
    if(file1 && file2)
    {
        //compare the number of line
        if(file1->nb_line!=file2->nb_line)
            return 1;
        //compare the number of char for a line
        int z,y;
        for(z=0;z<file1->nb_line;z++)
            for(y=0;file2->nb_line;y++)
            {
                if(file1->size_line[z]!=file2->size_line[y])
                    return 1;
            }

        int i;
        for(i=0; i < file1->nb_line; i++)
        {
            int j;
            for(j=0; j < file1->size_line[i]; j++)
            {
                if(file1->lines[i][j]!= file2->lines[i][j])
                {
                    return 1;
                }
            }
        }
    }
return 0;
}

t_file* ignore_blank(t_file * file)
{
    t_file* new_file;
    if (file != NULL)
    {
        new_file = file;
        if (new_file != NULL)
        {
            int i;
            for(; i < file->nb_line; i++)
            {
                int j;
                for(j=0; j < file->size_line[i]; j++)
                {
                    if((file->lines[i][j]=' '))
                        new_file->lines[i][j]=file->lines[i][j];
                }
            }
        }
     }
  return new_file;
}


//Return a line of file at index
char* get_line(t_file* file,int index)
{
    return file->lines[index];
}
