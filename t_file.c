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
        printf("%s",get_line(file,i));
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

void print_line_file(t_file* file, int nbfile, int start, int end){
  char file_sign = (nbfile==1)?'<':'>';
  int i;
  for(i = start; i < end ; i++){
    printf("%c ",file_sign);
    printf("%s",get_line(file,i));
  }
}
//Comparse two file
int file_compare(t_file* file_1, t_file* file_2){

  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int bad_line = 0;
  int change = 0;
  for(i = 0 ; i < file_2->nb_line ; i++){

    for(j = k ; j < file_1->nb_line ; j++){
  //Ò  printf("i:%d j:%d k:%d\n",i,j,k);

      if(strcmp(get_line(file_2,i),get_line(file_1,j)) == 0){
      //  printf("finder\n");
        // Aucune erreur avant- on est donc bien parti ! ouf
        if(l == 0){
          k = j+1;
        }

        // i == j hmm... On est au même indice des 2 cotés, mais il faut pas être comme k !
        else if(i == j && j != k){
          if(bad_line < 2){
            printf("%dc%d\n",j,i);
            print_line_file(file_1,1,j-1,j);
            printf("---\n");
            print_line_file(file_2,2,i-1,i);
          }
          else{
            printf("%d,%dc%d,%d\n",j-bad_line,j,i-bad_line,i);
            print_line_file(file_1,1,j-bad_line-1,j);
            printf("---\n");
            print_line_file(file_2,2,i-bad_line-1,i);
          }
          k = j+1;
          l = 0;
        }

        else if(i == j && j == k){
          printf("%da%d,%d\n",j,i-bad_line+1,i);
          print_line_file(file_2,2,i-bad_line,i);
          k = j+1;
          l = 0;
        }
        // i == 0 ca alors on est au début du fichier !
        else if(i == 0){

          if(j > 1){
            printf("1,%dd0\n",j);
            print_line_file(file_1,1,0,j);
          }
          else{
            printf("1d0\n");
            print_line_file(file_1,1,0,1);
          }

          k = j+1;
          l = 0;
        }

        // On est plus au début... Mais k y est toujours... Bizarre !
        else if(i > 0 && k == 0){
          if(j > i){
            printf("%d,%dc%d,%d\n",j-i,j,1,i);
            print_line_file(file_1,1,j-i-1,j);
            printf("---\n");
            print_line_file(file_2,2,0,i);
          }
          else if(i > 1){
            printf("0a1,%d\n",i);
            print_line_file(file_2,2,0,i);
          }
          else{
            printf("0a1\n");
            print_line_file(file_2,2,0,1);
          }

          k = j+1;
          l = 0;
        }

        // j est au même endroit que k ?!
        else if (j == k && bad_line == 0){

          printf("%da%d,%d\n",j,i-bad_line,i);
          print_line_file(file_2,2,i-bad_line-1,i);
          k = j+1;
          l = 0;
        }
        else if (j == k){
          if(bad_line > 1){

          }
          else{

            printf("%dc%d,%d\n",j,i-bad_line,i);
            print_line_file(file_2,2,i-bad_line-1,i);

          }
          // printf("%da%d,%d\n",j,i-bad_line,i);
          // print_line_file(file_2,2,i-bad_line,i);
          k = j+1;
          l = 0;
        }

        else if(i == k){

          if(bad_line >= 1){
            if(bad_line == 1){
              printf("%d,%dc%d\n",j-bad_line,j,i);
              print_line_file(file_1,1,j-bad_line-1,j);
              printf("---\n");
              print_line_file(file_2,2,i-1,i);
            }
            else{
              printf("%d,%dc%d,%d\n",j-bad_line,j,i-bad_line,i);
              print_line_file(file_1,1,j-bad_line-1,j);
              printf("---\n");
              print_line_file(file_2,2,i-bad_line-1,i);
            }
          }
          else{
            printf("%dd%d\n",j,i);
            print_line_file(file_1,1,j-1,j);
          }

          k = j+1;
          l = 0;
        }

        else if(bad_line > 0){
          printf("%d,%dc%d,%d\n",k+1,j,k,i);
          print_line_file(file_1,1,k,j);
          printf("---\n");
          print_line_file(file_2,2,k-1,i);
        }
        // Finito... OUF !
        bad_line = 0;
        break;
      }
      else{
        // Mince... Pas identique :/
        l++;
      }
    }
    if(l > 0){
      bad_line++;
    //  printf("pas de ligne trouvé... bd:%d\n",bad_line);
    }

  }
  return 0;
}
