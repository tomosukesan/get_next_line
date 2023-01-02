#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
	unsigned char	*buf;
	ssize_t			result;
	int				i;

	buf = malloc(sizeof(unsigned char) * BUFFER_SIZE);
	result = read(fd, (void *)buf, BUFFER_SIZE);
	while (i < BUFFER_SIZE)
	{
	}
	if (result < 0)
		// ERROR処理
	else if (result = 0)
		// EOFの処理
	else
		// またreadして追加
}

// int main(int argc, char *argv[])
int main()
{
	int		fd;
	char	*line;

	fd = open("./test/first_file", O_RDONLY);
	line = get_next_line(fd);
	// while ((line = get_next_line(fd))> 0)
	while (line != NULL)
	{
		printf("%s\n", line);
		line = get_next_line(fd);
	}
	return (0);
}

/*
// 自作
int main(int argc, char *argv[])
{
	// コマンドラインから値を受け取ることもある
	int fd;
	char *result;
	
	fd = 0;
	result = get_next_line(fd);
	while (result != NULL)
	{
		printf("result: %s\n", result);
		result = get_next_line(fd);
	}
	return (0);
}
*/