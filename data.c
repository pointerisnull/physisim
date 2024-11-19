#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include "data.h"

uint16_t readTwoBytes(const uint8_t *data, int offset) {
	uint16_t read;
	memcpy(&read, data+offset, sizeof(uint16_t));
	return read;
}

uint32_t readFourBytes(const uint8_t *data, int offset) {
	uint32_t read;
	memcpy(&read, data+offset, sizeof(uint32_t));
	return read;
}

int openandloaddata(char *filePath, uint16_t *data) {
	//char *filePath = "files/save.cfworld";
	printf("\n*DATA.C*\nFile: %s ", filePath);
	FILE *fp = fopen(filePath, "rb");
	if(fp == NULL) {
		printf(" not found!\n");
		return 1;
	}
	/* find file size in bytes */
	fseek(fp, 0, SEEK_END);
	size_t length = ftell(fp);
	/* reset file cursor, and store all bytes in buffer */
	fseek(fp, 0, SEEK_SET);

  //uint16_t data;
  fread(data, sizeof(uint16_t), length, fp);
  
  fclose(fp);

	printf("%ld bytes loaded into RAM!\n\n", length);
	return 0;
}

void savedata(uint16_t *data, char* filePath) {

	FILE *fp = fopen(filePath, "wb");
	if(fp == NULL) {
		printf("could not save!\n");
	}

  fwrite(*data, sizeof(uint16_t), 1, fp);

  fclose(fp);
}
