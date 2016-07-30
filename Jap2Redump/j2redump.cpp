#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	if (argc != 2 && argc != 3) {
		printf("usage: j2redump [-r] iso\n");
		return -1;
	}
	
	if (argc == 3 && strcmp(argv[1], "-r") != 0) {
		printf("unknow option\n");
		printf("usage: j2redump [-r] iso\n");
		return -1;
	}


	size_t size = 0x50000;
	size_t size1 = 0x10000;
	long long offset = 0xA6730000;
	long long offset1 = 0xA6770000;
	FILE *fp, *fout;

	if (argc == 2) {
		// fill data in two blocks
		// 0xA6730000 - 0xA673FFFF  
		// 0xA6770000 - 0xA677FFFF
		// but it is easier to fill data in range 0xA6730000 - 0xA677FFFF, which is read from external file
		if ((fp = fopen("diff.patch", "r")) == 0) {
			printf("open diff.patch failed!\n");
			exit(-1);
		}

		if ((fout = fopen(argv[1], "rb+")) == 0) {
			printf("open iso failed!\n");
			exit(-1);
		}
		void* patch = malloc(size);
		fread(patch, size, 1, fp);
		
		_fseeki64(fout, offset, SEEK_SET);
		fwrite(patch, size, 1, fout);
		free(patch);
		fclose(fp);
	} else {
		if ((fout = fopen(argv[2], "rb+")) == 0) {
			printf("open iso failed!\n");
			exit(-1);
		}

		// fill 0 in two blocks
		// 0xA6730000 - 0xA673FFFF  
		// 0xA6770000 - 0xA677FFFF 
		_fseeki64(fout, offset, SEEK_SET);
		int zero = 0;
		size_t len = size1 / sizeof(int);
		for (int i = 0; i < len; i++) {
			fwrite(&zero, sizeof(int), 1, fout);
		}
		_fseeki64(fout, offset1, SEEK_SET);
		for (int i = 0; i < len; i++) {
			fwrite(&zero, sizeof(int), 1, fout);
		}
	}
	fclose(fout);
	printf("patch succeed!\n");
}