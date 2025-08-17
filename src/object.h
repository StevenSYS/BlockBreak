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
	object_t object1,
	object_t object2
);

void object_init(
	object_t *object,
	unsigned char red, unsigned char green,	unsigned char blue,
	unsigned short width, unsigned short height,
	signed short x, signed short y,
	char visible
);

void object_draw(object_t object);

#endif