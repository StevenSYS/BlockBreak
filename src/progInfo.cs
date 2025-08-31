struct progInfo {
	/* - Program - */
	public const string PROGRAM_NAME = "BlockBreakC#";
	public const string PROGRAM_VERSION = "1.2pre";
	
	/* - Render - */
	public const ushort RENDER_WIDTH = 640;
	public const ushort RENDER_HEIGHT = 472;
	
	/* - Player - */
	public const ushort PLAYER_SPEED = RENDER_HEIGHT / 59;
	public const ushort PLAYER_WIDTH = RENDER_WIDTH / 40;
	public const ushort PLAYER_HEIGHT = RENDER_WIDTH / 40;
	
	/* Start */
	public const ushort PLAYER_START_X = (RENDER_WIDTH / 2) - (PLAYER_WIDTH / 2);
	public const ushort PLAYER_START_Y = RENDER_HEIGHT - (PLAYER_HEIGHT * 3);
	
	/* - Screen - */
	
	/* Edge */
	public const ushort SCREEN_EDGE_UP = 0;
	public const ushort SCREEN_EDGE_DOWN = RENDER_HEIGHT - PLAYER_HEIGHT;
	public const ushort SCREEN_EDGE_LEFT = 0;
	public const ushort SCREEN_EDGE_RIGHT = RENDER_WIDTH - PLAYER_WIDTH;
	
	/* - Max - */
	public const byte MAX_LEVEL = 255;
	public const byte MAX_FPS = 30;
	
	/* - Enable - */
	public const bool ENABLE_SCREENSHOT = true;
	
	/* - Font - */
	public const string FONT = "Arial";
	public const float FONT_HEIGHT = 8.0f;
}