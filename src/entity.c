#include "entity.h"

void entity_init(
	entity_t *entity,
	const unsigned char red, const unsigned char green, const unsigned char blue,
	const unsigned char direction,
	const unsigned short width, const unsigned short height,
	const signed short x, const signed short y,
	const signed short speed,
	const char visible
) {
	entity->direction = direction;
	entity->speed = speed;
	object_init(
		&entity->object,
		red, green, blue,
		width, height,
		x, y,
		visible
	);
	return;
}

void entity_draw(entity_t *entity) {
	if (entity->object.visible) {
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
		object_draw(entity->object);
	}
	return;
}