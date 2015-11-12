typedef struct s_file
{
	char** lines;
	unsigned int nb_line;
	int* size_line;
} t_file;


t_file* file_create(char* file_name);

void file_print(t_file* file);
char* get_line(t_file* f_file,int index);


/*

TO DO
//int file_compare(t_file* file_1, t_file* file_2);

*/
