#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"
#include <ctype.h>
#include <string.h>

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
        file->size_line = calloc(nb_line,sizeof(int));

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
        char** lines = calloc((nb_line+1),sizeof(char*));

        int i;
        // Alloc each line in the lines object
        for(i = 0 ; i < nb_line+1 ; i++)
        {
            char* line = calloc(file->size_line[i]*(nb_line+1),sizeof(char));
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

t_file* get_lcs(t_file* file_1, t_file* file_2)
{
    // 1 On initialise la matrice pour trouver le LCS
    int size_x = file_1->nb_line;
    int size_y = file_2->nb_line;
    int i;
    int j;
    int lcs_matrix[size_x+1][size_y+1];

    // printf("\nINITIALIZE LCS MATRIX ON ZERO\n-------------------------\n");

    for(i=0 ; i <= size_x ; i++)
    {
        for (j = 0; j <= size_y; j++)
        {
            lcs_matrix[i][j] = 0;
            // printf("%d ",lcs_matrix[i][j]);
        }
        // printf("\n");
    }
    // printf("-------------------------\nEND OF INITIALIZE\n\n");
    //
    //
    // printf("GET THE LCS MATRIX OPERATE\n-------------------------\n");
    //
    // for(j = 0; j <= size_y ; j++) {
    //   printf("%d ",lcs_matrix[0][j]);
    // }
    //
    // 2 On calcule la matrice pour le LCS
    for(i = 1 ; i <= size_x ; i++)
    {

        // printf("\n%d ",lcs_matrix[i][0]);

        for(j = 1 ; j <= size_y ; j++)
        {
            if(strcmp(get_line(file_1,i-1),get_line(file_2,j-1)) == 0)
            {
                lcs_matrix[i][j] = (lcs_matrix[i-1][j-1]) + 1;
                // printf("%d ",lcs_matrix[i][j]);
            }
            else if(lcs_matrix[i][j-1] > lcs_matrix[i-1][j])
            {

                lcs_matrix[i][j] = lcs_matrix[i][j-1];
                // printf("%d ",lcs_matrix[i][j]);
            }
            else
            {
                lcs_matrix[i][j] = lcs_matrix[i-1][j];
                // printf("%d ",lcs_matrix[i][j]);
            }
        }
    }
    // printf("\n-------------------------\nEND OF LCS\n\n");
    // printf("i:%d j:%d szmax:%d\n",i,j,lcs_matrix[i-1][j-1]);
    int size = lcs_matrix[i-1][j-1];
    int k = size - 1;
    int prc[k];
    for(i = i-1 ; i > 0 ; i--)
    {

        for(j = j-1 ; j > 0 ; j--)
        {
            if(lcs_matrix[i][j] == lcs_matrix[i-1][j])
            {
                j++;
                break;
            }
            else if(lcs_matrix[i][j] == lcs_matrix[i][j-1])
            {
                continue;
            }
            else
            {
                prc[k--] = i-1;
                break;
            }
        }
    }
    char** lcs_string = calloc(size, sizeof(char*));

    for(i=0 ; i < size ; i++)
    {
        char* lcs_line = calloc(file_1->size_line[prc[i]]*size, sizeof(char));
        lcs_string[i] = get_line(file_1,prc[i]);
    }
    t_file* lcs = (t_file*)malloc(sizeof(t_file));
    lcs->lines = lcs_string;
    lcs->nb_line = size;
    //
    // printf("HELLO && size = %d\n",size);
    // for(i = 0 ; i < size ; i++)
    //   printf("%d: %s",i,lcs->lines[i]);

    return lcs;
}
//Print the t_file
void file_print(t_file* file)
{
    //init variable
    int i = 0;
    printf("\n------- PRINT FILE -------\n");
    //Print each line
    for(; i < file->nb_line; i++)
    {
        //Print each char
        printf("%s",get_line(file,i));
    }
    printf("\n------- END FILE -------\n");
}

t_file * to_lower_case(t_file* file)
{
    if(file)
    {
        int i;
        for(i=0; i < file->nb_line; i++)
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
        for(z=0; z<file1->nb_line; z++) {
          if(file1->size_line[z]!=file2->size_line[z])
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
            int j;

            for(i=0; i < file->nb_line; i++)
            {
                int y=0;
                for(j=0; j < file->size_line[i]; j++)
                {

                    if((file->lines[i][j]!=' ')&&(file->lines[i][j]!='\t'))
                    {
                        new_file->lines[i][y]=file->lines[i][j];
                        y++;
                    }
                }
                new_file->lines[i][y]='\0';
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

void print_line_file(t_file* file, int num_file, int start, int end)
{
    char file_sign = (num_file==1)?'<':'>';
    int i;
    for(i = start; i < end ; i++)
    {
        printf("%c ",file_sign);
        printf("%s",get_line(file,i));
    }
}

//Comparse two file

int file_compare(t_file* file_1, t_file* file_2)
{

    t_file* lcs = get_lcs(file_1, file_2);
    int index_lcs = 0;
    int index_lcs_1 = 0;
    int index_lcs_2 = 0;
    int index_file_1 = 0;
    int index_file_2 = 0;

    for(index_lcs = 0 ; index_lcs < lcs->nb_line ; index_lcs++)
    {

        char * line_1 = get_line(file_1,index_file_1);
        char * line_2 = get_line(file_2,index_file_2);
        char * line_lcs = get_line(lcs,index_lcs);

        index_lcs_1 = index_file_1;
        index_lcs_2 = index_file_2;
        // Fichier 1 egal à lcs, mais pas Fichier 2 : on ajoute
        if(strcmp(line_1,line_lcs) == 0 && strcmp(line_2,line_lcs) != 0)
        {
            while(strcmp(line_2,line_lcs) != 0)
            {
                index_lcs_2++;
                line_2 = get_line(file_2,index_lcs_2);
            }
            if(index_lcs_2 == index_file_2+1)
                printf("%da%d\n",index_file_1,index_lcs_2);
            else
                printf("%da%d,%d\n",index_file_1,index_file_2+1,index_lcs_2);
            print_line_file(file_2,2,index_file_2,index_lcs_2);
        }

        // Fichier 2 egal à lcs, mais pas Fichier 1 : on supprime
        else if(strcmp(line_1,line_lcs) != 0 && strcmp(line_2,line_lcs) == 0)
        {
            while(strcmp(line_1,line_lcs) != 0)
            {
                index_lcs_1++;
                line_1 = get_line(file_1,index_lcs_1);
            }

            if(index_lcs_1 == index_file_1+1)
                printf("%dd%d\n",index_lcs_1,index_file_2);
            else
                printf("%d,%dd%d\n",index_file_1+1,index_lcs_1,index_file_2);
            print_line_file(file_1,1,index_file_1,index_lcs_1);
        }

        // Fichier 1 et 2 différent de lcs : on échange
        else if(strcmp(line_1,line_lcs) != 0 && strcmp(line_2,line_lcs) != 0)
        {
            while(strcmp(line_1,line_lcs) != 0)
            {
                index_lcs_1++;
                line_1 = get_line(file_1,index_lcs_1);
            }
            while(strcmp(line_2,line_lcs) != 0)
            {
                index_lcs_2++;
                line_2 = get_line(file_2,index_lcs_2);
            }
            if(index_lcs_1 == index_file_1+1 && index_lcs_2 == index_file_2+1)
                printf("%dc%d\n",index_lcs_1,index_lcs_2);
            else if (index_lcs_1 == index_file_1+1)
                printf("%dc%d,%d\n",index_lcs_1,index_file_2+1,index_lcs_2);
            else if (index_lcs_2 == index_file_2+1)
                printf("%d,%dc%d\n",index_file_1+1,index_lcs_1,index_lcs_2);
            else
                printf("%d,%dc%d,%d\n",index_file_1+1,index_lcs_1,index_file_2+1,index_lcs_2);
            print_line_file(file_1,1,index_file_1,index_lcs_1);
            printf("---\n");
            print_line_file(file_2,2,index_file_2,index_lcs_2);
        }
        // Fichier 1 et Fichier 2 sont egal à lcs : On a rien à faire ! good
        //On ajoute l'index lcs et on passe au suivant
        index_file_1 = index_lcs_1+1;
        index_file_2 = index_lcs_2+1;
    }
    // Il peut rester des lignes après le LCS
    //Si on est à la fin des deux fichier. C'est fini !
    if(index_file_2 > file_2->nb_line-1 && index_file_1 > file_1->nb_line-1)
    {
        return 0;
    }
    // Si fichier 2 est fini mais pas fichier 1 : on supprime
    else if(index_file_2 > file_2->nb_line-1)
    {
        if(index_file_1 == file_1->nb_line-1)
            printf("%dd%d\n",index_file_1+1,index_file_2);
        else
            printf("%d,%dd%d\n",index_file_1+1,file_1->nb_line,index_file_2);
        print_line_file(file_1,1,index_file_1,file_1->nb_line);
    }
    // Si fichier 1 est fini mais pas fichier 2 : on ajoute
    else if(index_file_1 > file_1->nb_line-1)
    {
        if(index_file_2 == file_2->nb_line-1)
            printf("%dd%d\n",index_file_1,index_file_2+1);
        else
            printf("%d,%dd%d\n",index_file_1,index_file_2+1,file_2->nb_line);
        print_line_file(file_2,2,index_file_2,file_2->nb_line);
    }
    // Les deux fichier sont pas fini. On échange tout ce qui reste
    else
    {
        if(index_file_2 == file_2->nb_line-1 && index_file_1 == file_1->nb_line-1)
            printf("%dc%d\n",index_file_1+1,index_file_2+1);
        else if (index_file_1 == file_1->nb_line-1)
            printf("%dc%d,%d\n",index_file_1+1,index_file_2+1,file_2->nb_line);
        else if (index_file_2 == file_2->nb_line-1)
            printf("%d,%dc%d\n",index_file_1+1,file_1->nb_line-1,index_file_2+1);
        else
            printf("%d,%dc%d,%d\n",index_file_1+1,file_1->nb_line,index_file_2+1,file_2->nb_line);
        print_line_file(file_1,1,index_file_1,file_1->nb_line);
        printf("---\n");
        print_line_file(file_2,2,index_file_2,file_2->nb_line);
    }
    return 0;
}
t_file* str_onespace(t_file* file)
{
    t_file* new_file;
    if (file != NULL)
    {
        int i;
        int j;
        int space = 0; //number of space
        new_file = file;
        if (new_file != NULL)
        {
            int y;
            for(i=0; i < file->nb_line; i++)
            {
                y = 0;
                for (j=0; j< file->size_line[i]; j++)
                {
                    if (file->lines[i][j] == 32 && space == 0)
                    {
                        new_file->lines[i][y] = file->lines[i][j];
                        y++;
                        space = 1;
                    } else if (file->lines[i][j] == 32 && space == 1) {
                        continue;
                    } else {
                        // si caractere non espace ou space egal 1
                        new_file->lines[i][y] = file->lines[i][j];
                        y++;
                        space = 0;
                    }
                }
                new_file->lines[i][y] = '\0';
            }
        }
    }
    return new_file;
}

t_file* str_onetab(t_file* file)
{
    t_file* new_file;
    if (file != NULL)
    {
        int i;
        int j;
        int space = 0; //number of space
        new_file = file;
        if (new_file != NULL)
        {
            int y=0;
            for(i=0; i < file->nb_line; i++)
            {
                for (j=0; j< file->size_line[i]; j++)
                {
                    if (file->lines[i][j] == 9 && space == 0)
                    {
                        new_file->lines[i][y] = file->lines[i][j];
                        y++;
                        space = 1;
                    } else if (file->lines[i][j] == 9 && space == 1) {
                        continue;
                    } else {
                        // si caractere non espace ou space egal 1
                        new_file->lines[i][y] = file->lines[i][j];
                        y++;
                        space = 0;
                    }
                }
                new_file->lines[i][y] = '\0';
            }
        }
    }
    return new_file; //we return the string tweaked
}
