//  printf("i:%d j:%d k:%d\n",i,j,k);

  if(strcmp(get_line(file_2,i),get_line(file_1,j)) == 0){
  printf("succes:%d i:%d j:%d k:%d badline:%d\n",l,i,j,k,bad_line);

    // Aucune erreur avant- on est donc bien parti ! ouf
    if(l == 0){
      k = j+1;
    }

    // i == j hmm... On est au même indice des 2 cotés, mais il faut pas être comme k !
    else if(i == j && j != k){
      printf("%d,%dc%d,%d\n",j-bad_line,j,i-bad_line,i);
      print_line_file(file_1,1,j-bad_line-1,j);
      printf("---\n");
      print_line_file(file_2,2,i-bad_line-1,i);
      k = j+1;
      l = 0;
    }

    else if(i == j && j == k){
      printf("%da%d,%d\n",j,i-bad_line+1,i);
      print_line_file(file_2,2,i-bad_line,i);
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
    // Finito... OUF !
    bad_line = 0;
    break;
  }
  else{
    // Mince... Pas identique :/
    l++;
  }
//
if(l > 0){
  bad_line++;
//  printf("pas de ligne trouvé... bd:%d\n",bad_line);
}
