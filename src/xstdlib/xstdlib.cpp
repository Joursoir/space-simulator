#include <stdio.h>

#include "xstdlib.hpp"

char *xfread(const char *path, const char *mode)
{
	char *source = 0;
	size_t file_size, bytes_read;
	FILE *file;

	file = fopen(path, mode);
	if(!file)
		return 0;

	do {
		if(fseek(file, 0, SEEK_END) < 0)
			break;

		file_size = ftell(file);
		if(file_size < 0)
			break;

		if(fseek(file, 0, SEEK_SET) < 0)
			break;

		source = new char[file_size + 1];
		bytes_read = fread(source, 1, file_size, file);
		if(bytes_read != file_size) {
			delete[] source;
			source = 0;
		}
		source[file_size] = '\0';
	} while(0);

	fclose(file);
	return source;
}

