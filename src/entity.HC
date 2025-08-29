#include "object.HC"

/* Enum - entity_directions */
#define ENTITY_DIR_UP 0
#define ENTITY_DIR_DOWN 1
#define ENTITY_DIR_LEFT 2
#define ENTITY_DIR_RIGHT 3
#define ENTITY_DIR_NONE 4
/* Enum End */

class entity_t {
	U8 direction;
	I16 speed;
	object_t object;
};

U0 entity_init(
	entity_t *entity,
	U8 color,
	U8 direction,
	U16 width, U16 height,
	I16 x, I16 y,
	I16 speed,
	Bool visible
) {
	entity->direction = direction;
	entity->speed = speed;
	object_init(
		&entity->object,
		color,
		width, height,
		x, y,
		visible
	);
	return;
}

Bool entity_draw(
	CDC *dc,
	entity_t *entity
) {
	if (entity->object.visible) {
		object_draw(dc, &entity->object);
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
	}
	return;
}