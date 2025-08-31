static class misc {
	public static uint safeAddU(
		uint vari,
		uint val,
		uint max
	) {
		if ((vari + val) > max) {
			return max;
		} else {
			return (vari + val);
		}
	}
	
	public static uint lessThanU(
		uint vari,
		uint val
	) {
		if (vari < val) {
			return val;
		} else {
			return vari;
		}
	}
	
	public static int position(
		int x, int y,
		int width
	) {
		return (y * width) + x;
	}
}