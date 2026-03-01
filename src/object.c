#include "impl.h"
#include "object.h"

char object_collision(
	object_t *object1,
	object_t *object2
) {
	return (
		((object1->position[0] + object1->size[0]) >= object2->position[0]) &&
		(object1->position[0] <= (object2->position[0] + object2->size[0])) &&
		((object1->position[1] + object1->size[1]) >= object2->position[1]) &&
		(object1->position[1] <= (object2->position[1] + object2->size[1]))
	);
}

void object_init(
	object_t *object,
	const unsigned char red, const unsigned char green, unsigned char blue,
	const unsigned short width, const unsigned short height,
	const signed short x, const signed short y,
	const char visible
) {
	object->color[0] = red;
	object->color[1] = green;
	object->color[2] = blue;
	object->size[0] = width;
	object->size[1] = height;
	object->position[0] = x;
	object->position[1] = y;
	object->visible = visible;
	return;
}

void object_draw(object_t *object) {
	if (object->visible) {
		impl_setColor(object->color[0], object->color[1], object->color[2]);
		impl_drawFillRect(
			object->position[0],
			object->position[1],
			object->size[0],
			object->size[1]
		);
	}
	return;
}