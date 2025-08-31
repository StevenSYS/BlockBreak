using System;

using static class_game;

using static impl;
using static progInfo;

class program {
	internal static class_game game;
	
	public static void Main() {
		game = new class_game();
		impl.uninit();
		return;
	}
}