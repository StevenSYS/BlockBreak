const entity_directions = {
	NONE: 0,
	UP: 1,
	DOWN: 2,
	LEFT: 3,
	RIGHT: 4
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
		switch (this.direction) {
			case entity_directions.UP:
				this.object.position[1] -= this.speed;
				break;
			case entity_directions.DOWN:
				this.object.position[1] += this.speed;
				break;
			case entity_directions.LEFT:
				this.object.position[0] -= this.speed;
				break;
			case entity_directions.RIGHT:
				this.object.position[0] += this.speed;
				break;
		}
		
		return this.object.draw();
	}
};