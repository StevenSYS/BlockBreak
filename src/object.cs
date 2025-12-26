class class_object {
	public byte[] color = { 0, 0, 0 };
	public int[] size = { 0, 0 };
	public int[] position = { 0, 0 };
	
	public bool visible = false;
	
	public class_object(
		byte red, byte green, byte blue,
		int width, int height,
		int x, int y,
		bool visible
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
	
	public bool collision(class_object obj) {
		return (
			((this.position[0] + this.size[0]) >= obj.position[0]) &&
			(this.position[0] <= (obj.position[0] + obj.size[0])) &&
			(this.position[1] <= (obj.position[1] + obj.size[1])) &&
			((this.position[1] + this.size[1]) >= obj.position[1])
		);
	}
	
	public virtual void draw() {
		if (this.visible) {
			impl.drawFillRect(
				this.color[0], this.color[1], this.color[2],
				this.position[0], this.position[1],
				this.size[0], this.size[1]
			);
		}
		return;
	}
};