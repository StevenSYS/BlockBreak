#include "entity.h"

void entity_init(
	entity_t *entity,
	unsigned char red,
	unsigned char green,
	unsigned char blue,
	enum entity_directions direction,
	unsigned short width,
	unsigned short height,
	signed short x,
	signed short y,
	signed short speed,
	char visible
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
		object_draw(&entity->object);
	}
	return;
}