#include "entity.h"

void entity_init(
	entity_t *entity,
	unsigned char red, unsigned char green, unsigned char blue,
	unsigned char direction,
	unsigned short width, unsigned short height,
	signed short x, signed short y,
	signed short speed,
	char visible
) {
	entity->object.color[0] = red;
	entity->object.color[1] = green;
	entity->object.color[2] = blue;
	entity->direction = direction;
	entity->object.size[0] = width;
	entity->object.size[1] = height;
	entity->object.position[0] = x;
	entity->object.position[1] = y;
	entity->speed = speed;
	entity->object.visible = visible;
	return;
}

char entity_draw(entity_t *entity) {
	switch (entity->direction) {
		case ENTITY_DIR_UP:
			entity->object.position[1] -= entity->speed;
			break;
		case ENTITY_DIR_DOWN:
			entity->object.position[1] += entity->speed;
			break;
		case ENTITY_DIR_LEFT:
			entity->object.position[0] -= entity->speed;
			break;
		case ENTITY_DIR_RIGHT:
			entity->object.position[0] += entity->speed;
			break;
		default:
			break;
	}
	
	return object_draw(&entity->object);
}