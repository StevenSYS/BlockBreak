const entity_directions = {
	UP: 0,
	DOWN: 1,
	LEFT: 2,
	RIGHT: 3,
	NONE: 4
};

class entity {
	direction;
	speed;
	object;
	
	constructor(
		red, green, blue,
		direction,
		width, height,
		x, y,
		speed,
		visible
	) {
		this.direction = direction;
		this.speed = speed;
		this.object = new object(
			red, green, blue,
			width, height,
			x, y,
			visible
		);
		return;
	}
	
	draw() {
		if (this.object.visible) {
			if (this.direction != entity_directions.NONE) {
				this.object.position[
					this.direction >= entity_directions.LEFT ? 0 : 1
				] += (
					this.direction % 2
				) == 0 ? -this.speed : this.speed;
			}
			this.object.draw();
		}
		return;
	}
};