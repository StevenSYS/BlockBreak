#ifndef __ENTITY__
#define __ENTITY__

#include "object.h"

/* Enums */
enum entity_directions {
	ENTITY_DIR_UP,
	ENTITY_DIR_DOWN,
	ENTITY_DIR_LEFT,
	ENTITY_DIR_RIGHT,
	ENTITY_DIR_NONE
};

/* Structs */
typedef struct {
	unsigned char direction;
	signed short speed;
	object_t object;
} entity_t;

/* Functions */
void entity_init(
	entity_t *entity,
	unsigned char red, unsigned char green, unsigned char blue,
	unsigned char direction,
	unsigned short width, unsigned short height,
	signed short x, signed short y,
	signed short speed,
	char visible
);

void entity_draw(entity_t *entity);

#endif