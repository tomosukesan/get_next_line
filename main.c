#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

// int main(int argc, char *argv[])
int main()
{
	int		fd_1, fd_2;
	char	*line;

	fd_1 = open("./test/first_file", O_RDONLY);
	fd_2 = open("./test/42tokyo", O_RDONLY);
	//fd = 0;
	while (1)
	{
		line = get_next_line(fd_1);
		if (line == NULL)
			break;
		printf("%s", line);
		line = get_next_line(fd_2);
		//if (line == NULL)
		//	break;
		printf("%s", line);
		free(line);
	}
	close (fd_1);
	close (fd_2);
	//system("leaks a.out");
	return (0);
}
