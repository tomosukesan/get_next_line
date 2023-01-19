#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

// int main(int argc, char *argv[])
int main()
{
	int		fd;
	char	*line;

	fd = open("./test/first_file", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s", line);
		free(line);
	}
	close (fd);
	printf("%d\n", FOPEN_MAX);
	//system("leaks a.out");
	return (0);
}
