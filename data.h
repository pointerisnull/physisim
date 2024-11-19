#ifndef DATA_H
#define DATA_H

#include <stdint.h>

typedef struct {
	int16_t x;
	int16_t y;
} Particle;

typedef struct {
	uint16_t startVertex;
	uint16_t endVertex;
	uint16_t sector;
	uint16_t adjacentSector;
	uint8_t isPortal;
	uint8_t type;
	uint8_t flags;
} Segment;


/* reads file data and puts it in byte array */
int openandloaddata(char *filePath, uint16_t *data);
void savedata(uint16_t *data, char* filePath);

#endif 
