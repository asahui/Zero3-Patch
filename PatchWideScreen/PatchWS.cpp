#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isWideScreen = 0;
int isFixFMV = 0;
int isPatchFocusOff = 0;
int isPatchFixBloomOffset = 0;
int isDitherEffectOff = 0;
int isDisableDarkFilter = 0;
int isDisableAllBloom = 0;
int isDisableOverBloom = 0;

unsigned int offset_elf = 0x249F0000;
unsigned int offset_ws = 0x22106C;
unsigned int offset_fmv_fix1 = 0x269148;
unsigned int offset_fmv_fix2 = 0x113808;
unsigned int offset_focus_effect = 0x5706C;
unsigned int offset_bloom_offset = 0x266008;
unsigned int offset_dither_effect = 0x57024;
unsigned int offset_dark_filter = 0x5709c;
unsigned int offset_all_bloom = 0x57164;
unsigned int offset_over_bloom_cutscene = 0x57100;
unsigned int offset_over_bloom_gameplay = 0x265ffc;

// offset: 0x24C1106C
// ELF offset:0x22106C
unsigned char ws_off[4] = {
	0x00, 0x00, 0x80, 0x3F
};

unsigned char ws_on[4] = {
	0x00, 0x00, 0x40, 0x3F
};

///////////////////////////
// offset: 0x24C59148
// ELF offset:0x269148
unsigned char fmv_fix1_before[4] = {
	0x00, 0x00, 0x80, 0x3F
};

unsigned char fmv_fix1_after[4] = {
	0x33, 0x33, 0x33, 0x3E
};

///////////////////////////
// offset: 0x24B03808
// ELF offset: 0x113808
unsigned char fmv_fix2_before[72] = {
	0x00, 0x00, 0xE0, 0xC5, 0x90, 0xAA, 0x09, 0x0C, 0x44, 0x00, 0xA0, 0xE7, 0xB0, 0x00, 0xAF, 0x8F,
	0x2D, 0x20, 0x00, 0x02, 0xB4, 0x00, 0xAE, 0x8F, 0x00, 0x00, 0x8F, 0x44, 0x00, 0x08, 0x8E, 0x44,
	0x20, 0x00, 0x80, 0x46, 0xFE, 0xFF, 0xEF, 0x25, 0x60, 0x08, 0x80, 0x46, 0x2C, 0x00, 0xAF, 0xAF,
	0x30, 0x00, 0xAE, 0xAF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xB5, 0x00, 0x46,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

unsigned char fmv_fix2_after[72] = {
	0x90, 0xAA, 0x09, 0x0C, 0x00, 0x00, 0xE1, 0xC5, 0xB0, 0x00, 0xAF, 0x8F, 0x2D, 0x20, 0x00, 0x02,
	0xB4, 0x00, 0xAE, 0x8F, 0x00, 0x00, 0x8F, 0x44, 0x20, 0x00, 0x80, 0x46, 0xFE, 0xFF, 0xEF, 0x25,
	0x42, 0x00, 0x01, 0x46, 0x44, 0x00, 0xA1, 0xE7, 0x2C, 0x00, 0xAF, 0xAF, 0x30, 0x00, 0xAE, 0xAF,
	0x40, 0x3F, 0x01, 0x3C, 0x00, 0x08, 0x81, 0x44, 0x82, 0xB5, 0x01, 0x46, 0x83, 0xB5, 0x00, 0x46,
	0x00, 0x08, 0x8E, 0x44, 0x60, 0x08, 0x80, 0x46
};


///////////////////////////
// offset: 0x24A4706C
// ELF offset: 0x5706C
unsigned char focus_effect_on[4] = {
	0xEE, 0x58, 0x05, 0x0C
};

unsigned char focus_effect_off[4] = {
	0x00, 0x00, 0x00, 0x00
};

///////////////////////////
// offset: 0x24C56008
// ELF offset: 0x266008
unsigned char bloom_offset_fix_before[8] = {
	0x00, 0x00, 0xA0, 0x43, 0x00, 0x00, 0x60, 0x43
};

unsigned char bloom_offset_fix_after[8] = {
	0x00, 0x00, 0xA3, 0x43, 0x00, 0x00, 0x66, 0x43
};

///////////////////////////
//Dither + Ghost post-process Effect Off
// offset: 0x24A47024
// ELF offset: 0x57024
unsigned char dither_on[4] = {
	0x54, 0x59, 0x05, 0x0C
};

unsigned char dither_off[4] = {
	0x00, 0x00, 0x00, 0x00
};

///////////////////////////
//Disable dark filter (cutscene)
// offset: 0x24A4709C
// ELF offset: 0x5709c
unsigned char dark_filter_on[4] = {
	0x4C, 0x59, 0x05, 0x0C
};

unsigned char dark_filter_off[4] = {
	0x00, 0x00, 0x00, 0x00
};

///////////////////////////
//Disable all bloom (speedup, but makes the game seem dull)
// offset: 0x24A47164
// ELF offset: 0x57164
unsigned char all_bloom_on[4] = {
	0x42, 0x59, 0x05, 0x0C
};

unsigned char all_bloom_off[4] = {
	0x00, 0x00, 0x00, 0x00
};

///////////////////////////
//Disable overbloom (cutscene)
//Decrease overbloom (gameplay)
// offset: 0x24A47100
// ELF offset: 0x57100
unsigned char overbloom1_on[4] = {
	0xF4, 0x58, 0x05, 0x0C
};

unsigned char overbloom1_off[4] = {
	0x00, 0x00, 0x00, 0x00
};

// offset: 0x24C55FFC
// ELF offset: 0x265ffc
unsigned char overbloom2_on[4] = {
	0x00, 0x00, 0x80, 0x3F
};

unsigned char overbloom2_off[4] = {
	0x00, 0x00, 0x40, 0x3F
};


void patch(FILE* fp, unsigned int base_offset) {
	if (isWideScreen) {
		fseek(fp, base_offset + offset_ws, SEEK_SET);
		fwrite(ws_on, 4, 1, fp);
	}
	else {
		fseek(fp, base_offset + offset_ws, SEEK_SET);
		fwrite(ws_off, 4, 1, fp);
	}

	if (isFixFMV) {
		fseek(fp, base_offset + offset_fmv_fix1, SEEK_SET);
		fwrite(fmv_fix1_after, 4, 1, fp);
		fseek(fp, base_offset + offset_fmv_fix2, SEEK_SET);
		fwrite(fmv_fix2_after, 72, 1, fp);
	}
	else {
		fseek(fp, base_offset + offset_fmv_fix1, SEEK_SET);
		fwrite(fmv_fix1_before, 4, 1, fp);
		fseek(fp, base_offset + offset_fmv_fix2, SEEK_SET);
		fwrite(fmv_fix2_before, 72, 1, fp);
	}

	if (isPatchFocusOff) {
		fseek(fp, base_offset + offset_focus_effect, SEEK_SET);
		fwrite(focus_effect_off, 4, 1, fp);
	}
	else {
		fseek(fp, base_offset + offset_focus_effect, SEEK_SET);
		fwrite(focus_effect_on, 4, 1, fp);
	}

	if (isPatchFixBloomOffset) {
		fseek(fp, base_offset + offset_bloom_offset, SEEK_SET);
		fwrite(bloom_offset_fix_after, 8, 1, fp);
	}
	else {
		fseek(fp, base_offset + offset_bloom_offset, SEEK_SET);
		fwrite(bloom_offset_fix_before, 8, 1, fp);
	}

	if (isDitherEffectOff) {
		fseek(fp, base_offset + offset_dither_effect, SEEK_SET);
		fwrite(dither_off, 4, 1, fp);
	}
	else {
		fseek(fp, base_offset + offset_dither_effect, SEEK_SET);
		fwrite(dither_on, 4, 1, fp);
	}

	if (isDisableDarkFilter) {
		fseek(fp, base_offset + offset_dark_filter, SEEK_SET);
		fwrite(dark_filter_off, 4, 1, fp);
	}
	else {
		fseek(fp, base_offset + offset_dark_filter, SEEK_SET);
		fwrite(dark_filter_on, 4, 1, fp);
	}

	if (isDisableAllBloom) {
		fseek(fp, base_offset + offset_all_bloom, SEEK_SET);
		fwrite(all_bloom_off, 4, 1, fp);
	}
	else {
		fseek(fp, base_offset + offset_all_bloom, SEEK_SET);
		fwrite(all_bloom_on, 4, 1, fp);
	}

	if (isDisableOverBloom) {
		fseek(fp, base_offset + offset_over_bloom_cutscene, SEEK_SET);
		fwrite(overbloom1_off, 4, 1, fp);
		fseek(fp, base_offset + offset_over_bloom_gameplay, SEEK_SET);
		fwrite(overbloom2_off, 4, 1, fp);
	}
	else {
		fseek(fp, base_offset + offset_over_bloom_cutscene, SEEK_SET);
		fwrite(overbloom1_on, 4, 1, fp);
		fseek(fp, base_offset + offset_over_bloom_gameplay, SEEK_SET);
		fwrite(overbloom2_on, 4, 1, fp);
	}
}

void patch_ELF(FILE* fp) {
	patch(fp, 0);
}


void patch_ISO(FILE* fp) {
	patch(fp, offset_elf);
}


void check_opt(char *opt) {
	if (strstr(opt, "0") != NULL) {
		printf("wide screen on\n");
		isWideScreen = 1;
	}
	if (strstr(opt, "1") != NULL) {
		printf("fix FMV\n");
		isFixFMV = 1;
	}
	if (strstr(opt, "2") != NULL) {
		printf("focus effect off\n");
		isPatchFocusOff = 1;
	}
	if (strstr(opt, "3") != NULL) {
		printf("fix bloom offset\n");
		isPatchFixBloomOffset = 1;
	}
	if (strstr(opt, "4") != NULL) {
		printf("dither + ghost post-process effect off\n");
		isDitherEffectOff = 1;
	}
	if (strstr(opt, "5") != NULL) {
		printf("disable dark filter\n");
		isDisableDarkFilter = 1;
	}
	if (strstr(opt, "6") != NULL) {
		printf("disable all bloom\n");
		isDisableAllBloom = 1;
	}
	if (strstr(opt, "7") != NULL) {
		printf("disable over bloom\n");
		isDisableOverBloom = 1;
	}
}

int main(int argc, char * argv[]) {
	if (argc > 3) {
		printf("usage: patchws [-r|1|2|3|4|5|6|7] [iso]\n");
		printf("If iso is not provided, ELF file named as 'SLPS_255.44' is supposed to be patched\n");
		return -1;
	}

	FILE *fp;
	if (argc == 1) {
		if ((fp = fopen("SLPS_255.44", "rb+")) == 0) {
			printf("error: SLPS_255.44 is not on the same directory.\n");
			exit(-1);
		}
		// patch SLPS_255.44
		patch_ELF(fp);
	} else if (argc == 2) {
		if (argv[1][0] == '-') {
			// check options
			check_opt(argv[1]);
			if ((fp = fopen("SLPS_255.44", "rb+")) == 0) {
				printf("error: SLPS_255.44 is not on the same directory.\n");
				exit(-1);
			}
			// patch SLPS_255.44
			patch_ELF(fp);
		}
		else {
			if ((fp = fopen(argv[1], "rb+")) == 0) {
				printf("error: could not open iso.\n");
				exit(-1);
			}
			// patch ISO file
			patch_ISO(fp);
		}
	} else {
		// check options
		check_opt(argv[1]);
		if ((fp = fopen("SLPS_255.44", "rb+")) == 0) {
			printf("error: could not open iso.\n");
			exit(-1);
		}
		// patch SLPS_255.44
		patch_ISO(fp);
	}

	fclose(fp);
}