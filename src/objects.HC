class object_t {
	U8 color;
	U16 size[2];
	I16 position[2];
	
	Bool visible;
};

U8 object_collision(
	object_t *object1,
	object_t *object2
) {
	if (
		((object1->position[0] + object1->size[0]) >= object2->position[0]) &&
		(object1->position[0] <= (object2->position[0] + object2->size[0])) &&
		(object1->position[1] <= (object2->position[1] + object2->size[1])) &&
		((object1->position[1] + object1->size[1]) >= object2->position[1])
	) {
		return 1;
	}
	return 0;
}

U0 object_init(
	object_t *object,
	U8 color,
	U16 width, U16 height,
	I16 x, I16 y,
	Bool visible
) {
	object->color = color;
	object->size[0] = width;
	object->size[1] = height;
	object->position[0] = x;
	object->position[1] = y;
	object->visible = visible;
	return;
}

Bool object_draw(
	CDC *dc,
	object_t *object
) {
	if (object->visible) {
		dc->color = object->color;
		GrRect(
			dc,
			object->position[0],
			object->position[1],
			object->size[0],
			object->size[1]
		);
	}
	return object->visible;
}