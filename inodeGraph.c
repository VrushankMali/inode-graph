#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void listdir(const char *fname, int acc, FILE *infile);

int main(int args[], char *argv[])
{
        char *fname;
        fname = malloc(50);
        strcat(fname, argv[1]);

        FILE *infile;
        infile = fopen("Filenode.gv", "w");

        fprintf(infile, "digraph inode_graph{\n");
        fprintf(infile, "\trankdir=LR\n");
        fprintf(infile, "\tnode [shape=oval];\n");

        listdir(fname, 0, infile);

        fprintf(infile, "}");

        fclose(infile);
        return 0;
}

void listdir(const char *fname, int acc, FILE *infile)
{
	int i=0;
	int count=0;
	struct stat ss;
	DIR *dir;
	struct dirent *entry;

	if(!(dir = opendir(fname)))
	{
		return;
	}

	while((entry = readdir(dir)) != NULL)
	{
		if(entry->d_type == DT_DIR)
		{
			char path[1000];

			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			{
				continue;
			}

			strcpy(path, fname);
			strcat(path, "/");
			strcat(path, entry->d_name);
			
			fprintf(infile, "\tq%d -> q%d;\n", i-1, count);
			fprintf(infile, "\tq%d [ label = \"File path: %s\\n\n", count, fname);
			fprintf(infile, "\t\tFile size: %lld\\n\n", (long long) ss.st_size);
			fprintf(infile, "\t\tBlocks allocated: %lld\\n\n", (long long) ss.st_blocks);
			fprintf(infile, "\t\tI-node number: %ld\\n\n", (long) ss.st_ino);
			fprintf(infile, "\t\tNumber of links: %ld\\n\n", (long) ss.st_nlink);
			fprintf(infile, "\"\t]\n\n");
			
			listdir(path, acc + 2, infile);
			count++;
			i++;
		}
		count++;
		i++;
	}
	closedir(dir);
}
