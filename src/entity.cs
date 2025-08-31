using static impl;
using static class_object;

class class_entity : class_object {
	public enum entity_directions {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE
	};
	
	public entity_directions direction = entity_directions.NONE;
	public int speed = 0;
	
	public class_entity(
		byte red, byte green, byte blue,
		entity_directions direction,
		int width, int height,
		int x, int y,
		int speed,
		bool visible
	) : base(
		red, green ,blue,
		width, height,
		x, y,
		visible
	) {
		this.direction = direction;
		this.speed = speed;
		return;
	}
	
	public override void draw() {
		if (this.visible) {
			if (this.direction != entity_directions.NONE) {
				this.position[
					this.direction >= entity_directions.LEFT ? 0 : 1
				] += (
					(int)this.direction % 2
				) == 0 ? -this.speed : this.speed;
			}
			
			impl.drawFillRect(
				this.color[0], this.color[1], this.color[2],
				this.position[0], this.position[1],
				this.size[0], this.size[1]
			);
		}
		return;
	}
}