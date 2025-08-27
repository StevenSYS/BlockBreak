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
	const unsigned char red, const unsigned char green, const unsigned char blue,
	const enum entity_directions direction,
	const unsigned short width, const unsigned short height,
	const signed short x, const signed short y,
	const signed short speed,
	const char visible
);

void entity_draw(entity_t *entity);

#endif