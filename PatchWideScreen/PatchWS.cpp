#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isPatchFocusOff = 0;
int isPatchDitherEffectOff = 0;
int isPatchFixBloomOffset = 0;

void patchELF(FILE* fp) {

}

void reverse_patchELF(FILE* fp) {

}

void patchISO(FILE* fp) {

}

void reverse_patchISO(FILE* fp) {

}

int main(int argc, char * argv[]) {
	if (argc > 3) {
		printf("usage: patchws [-r] [iso]\n");
		printf("If iso is not provided, ELF file named as 'SLPS_255.44' is supposed to be patched\n");
		return -1;
	}

	if (argc == 3 && strcmp(argv[1], "-r") != 0) {
		printf("unknow option\n");
		printf("usage: patchws [-r] [iso]\n");
		return -1;
	}

	FILE *fp, *fout;


	if (argc == 1) {
		if ((fp = fopen("SLPS_255.44", "rb+")) == 0) {
			printf("error: SLPS_255.44 is not on the same directory.\n");
			exit(-1);
		}
		// patch SLPS_255.44
	}
	else if (argc == 2) {
		if (strcmp(argv[1], "-r") == 0) {
			// patch SLPS_255.44 reversely
			if ((fp = fopen("SLPS_255.44", "rb+")) == 0) {
				printf("error: SLPS_255.44 is not on the same directory.\n");
				exit(-1);
			}
			// pat
		}
		else {
			// patch ISO file
			if ((fp = fopen(argv[1], "rb+")) == 0) {
				printf("error: SLPS_255.44 is not on the same directory.\n");
				exit(-1);
			}
		}
	}
	else {
		// patch ISO file reversely
		if ((fp = fopen(argv[2], "rb+")) == 0) {
			printf("error: SLPS_255.44 is not on the same directory.\n");
			exit(-1);
		}
	}

	fclose(fp);
}