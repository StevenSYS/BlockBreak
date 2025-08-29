#include "entity.h"

void entity_init(
	entity_t *entity,
	const unsigned char red, const unsigned char green, const unsigned char blue,
	const enum entity_directions direction,
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
		if (entity->direction != ENTITY_DIR_NONE) {
			entity->object.position[
				entity->direction >= ENTITY_DIR_LEFT ? 0 : 1
			] += (
				(int)entity->direction % 2
			) == 0 ? -entity->speed : entity->speed;
		}
		object_draw(entity->object);
	}
	return;
}