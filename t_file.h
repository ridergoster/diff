typedef struct s_file
{
	char** lines;
	unsigned int nb_line;
	int* size_line;
} t_file;


t_file* file_create(char* file_name);

void file_print(t_file* file);

char* get_line(t_file* file,int index);

t_file * get_lcs(t_file* file_1, t_file* file_2);

t_file * to_lower_case(t_file* file);

int is_file_different(t_file * file1, t_file * file2);

t_file * ignore_blank(t_file * file);

t_file* str_onespace (t_file* file);
t_file* str_onetab(t_file* file);

int file_compare(t_file* file_1, t_file* file_2);
int file_compare2(t_file* file_1, t_file* file_2);
