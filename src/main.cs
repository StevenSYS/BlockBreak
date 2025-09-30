using System;

using static class_blockBreak;

using static impl;
using static progInfo;

class program {
	internal static class_blockBreak game;
	
	public static void Main() {
		game = new class_blockBreak();
		impl.uninit();
		return;
	}
}