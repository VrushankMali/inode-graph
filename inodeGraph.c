#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void listdir(const char *name, int indent, FILE *infile)
{
	int i=0;
	int count=0;
	struct stat pr;
	DIR *dir;
	struct dirent *entry;

	if(!(dir = opendir(name)))
	{
		return;
	}

	while((entry = readdir(dir)) != NULL)
	{
		if(entry->d_type == DT_DIR)
		{
			char path[1024];

			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			{
				continue;
			}

			strcpy(path, name);
			strcat(path, "/");
			strcat(path, entry->d_name);
			
			fprintf(infile, "q%d -> q%d;\n", i-1, count);
			fprintf(infile, "\tq%d [ label = \"File path: %s\\\\n\n", count, name);
			fprintf(infile, "\t\tFile size: %lld\\n\n", (long long) pr.st_size);
			fprintf(infile, "\t\tBlocks allocated: %lld\\n\n", (long long) pr.st_blocks);
			fprintf(infile, "\t\tI-node number: %ld\\n\n", (long) pr.st_ino);
			fprintf(infile, "\t\tNumber of links: %ld\\n\n", (long) pr.st_nlink);
			fprintf(infile, "\"\t]\n\n");
			
			listdir(path, indent + 2, infile);
			count++;
			i++;
		}
		count++;
		i++;
	}
	closedir(dir);
}

int main(int argc, char *argv[])
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
