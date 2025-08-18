class object {
	color = [];
	size = [];
	position = [];
	
	visible;
	
	constructor(
		red, green, blue,
		width, height,
		x, y,
		visible
	) {
		this.color[0] = red;
		this.color[1] = green;
		this.color[2] = blue;
		this.size[0] = width;
		this.size[1] = height;
		this.position[0] = x;
		this.position[1] = y;
		this.visible = visible;
		return;
	}
	
	collision(object) {
		if (
			((this.position[0] + this.size[0]) >= object.position[0]) &&
			(this.position[0] <= (object.position[0] + object.size[0])) &&
			(this.position[1] <= (object.position[1] + object.size[1])) &&
			((this.position[1] + this.size[1]) >= object.position[1])
		) {
			return true;
		}
		return false;
	}
	
	draw() {
		if (this.visible) {
			impl_setColor(this.color[0], this.color[1], this.color[2]);
			impl_drawFillRect(
				this.position[0], this.position[1],
				this.size[0], this.size[1]
			);
		}
		return;
	}
};