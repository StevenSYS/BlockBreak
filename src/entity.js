const directions = {
	NONE: 0,
	UP: 1,
	DOWN: 2,
	LEFT: 3,
	RIGHT: 4
};

class entity {
	color = [];
	direction;
	size = [];
	position = [];
	speed;
	
	visible;
	
	constructor(
		red, green, blue,
		direction,
		width, height,
		x, y,
		speed,
		visible
	) {
		this.color[0] = red;
		this.color[1] = green;
		this.color[2] = blue;
		this.direction = direction;
		this.size[0] = width;
		this.size[1] = height;
		this.position[0] = x;
		this.position[1] = y;
		this.speed = speed;
		this.visible = visible;
		return;
	}
	
	collision(entity) {
		if (
			((this.position[0] + this.size[0]) >= entity.position[0]) &&
			(this.position[0] <= (entity.position[0] + entity.size[0])) &&
			(this.position[1] <= (entity.position[1] + entity.size[1])) &&
			((this.position[1] + this.size[1]) >= entity.position[1])
		) {
			return true;
		}
		return false;
	}
	
	draw(context, useDirection) {
		if (useDirection) {
			switch (this.direction) {
				case directions.UP:
					this.position[1] -= this.speed;
					break;
				case directions.DOWN:
					this.position[1] += this.speed;
					break;
				case directions.LEFT:
					this.position[0] -= this.speed;
					break;
				case directions.RIGHT:
					this.position[0] += this.speed;
					break;
			}
		}
		
		if (this.visible) {
			context.beginPath();
			context.fillStyle = "#" + this.color[0] + this.color[1] + this.color[2];
			context.rect(
				this.position[0], this.position[1],
				this.size[0], this.size[1]
			);
			context.fill();
		}
		return;
	}
};