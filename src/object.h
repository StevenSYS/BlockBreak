#ifndef __OBJECT__
#define __OBJECT__

/* Structs */
typedef struct {
	unsigned char color[3];
	unsigned short size[2];
	signed short position[2];
	
	char visible;
} object_t;

/* Functions */
char object_collision(
	object_t *object1,
	object_t *object2
);

void object_init(
	object_t *object,
	const unsigned char red, const unsigned char green, const unsigned char blue,
	const unsigned short width, const unsigned short height,
	const signed short x, const signed short y,
	const char visible
);

void object_draw(object_t *object);

#endif