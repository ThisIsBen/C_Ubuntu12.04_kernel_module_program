#include <stdio.h>
	void read_module_response(char * target_file)
	{
		int c;
		FILE *file;
		file = fopen(target_file, "r");
		if (file) 
		{
			while ((c = getc(file)) != EOF)
				putchar(c);
			fclose(file);
		}
		else
		{
			printf("file doesn't exist!\n");
		}
	}
	int main()
	{
		char *target_file="/proc/ps_list";
		read_module_response(target_file);
		//printf("hello ben!\n");

		return 0;
	}