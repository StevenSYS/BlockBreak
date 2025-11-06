using System;
using System.Timers;
using System.Windows.Forms;
using System.Drawing;

using static class_blockBreak;

using static progInfo;

static class impl {
	internal static Form window = new Form();
	internal static System.Timers.Timer timer = new System.Timers.Timer();
	internal static System.Drawing.Font font; 
	internal static System.Drawing.StringFormat strFormat;
	internal static System.Drawing.Graphics gfx;
	
	/* Draw */
	public static void drawFillRect(
		byte red, byte green, byte blue,
		int x, int y,
		int width, int height
	) {
		gfx.FillRectangle(
			new System.Drawing.SolidBrush(
				Color.FromArgb(255, red, green, blue)
			),
			new Rectangle(
				x, y,
				width, height
			)
		);
		return;
	}
	
	public static void drawText(
		byte red, byte green, byte blue,
		string text,
		int x, int y
	) {
		gfx.DrawString(
			text,
			font,
			new System.Drawing.SolidBrush(
				Color.FromArgb(255, red, green, blue)
			),
			x, y,
			strFormat
		);
		return;
	}
	
	/* Misc. */
	internal static void keyDown(class_blockBreak game, object sender, KeyEventArgs evt) {
		switch (evt.KeyCode) {
			case Keys.Up:
				game.input(inputs.UP);
				break;
			case Keys.Down:
				game.input(inputs.DOWN);
				break;
			case Keys.Left:
				game.input(inputs.LEFT);
				break;
			case Keys.Right:
				game.input(inputs.RIGHT);
				break;
			case Keys.Enter:
				game.input(inputs.RESET);
				break;
			case Keys.Escape:
				timer.Enabled = false;
				Application.Exit();
				uninit();
				break;
			default:
				game.input(inputs.NONE);
				break;
		}
	}
	
	public static void init(class_blockBreak game) {
		/* - Text - */
		font = new System.Drawing.Font(FONT, FONT_HEIGHT);
		strFormat = new System.Drawing.StringFormat();
		
		/* - Window - */
		window.Text = PROGRAM_NAME + " v" + PROGRAM_VERSION + " - Windows Form/GDI+";
		
		/* Sizing */
		window.ClientSize = new Size(RENDER_WIDTH, RENDER_HEIGHT);
		window.MinimumSize = new System.Drawing.Size(
			window.Width,
			window.Height
		);
		window.MaximumSize = window.MinimumSize;
		
		/* Drawing */
		gfx = window.CreateGraphics();
		
		window.BackColor = Color.Black;
		window.Paint += game.draw;
		window.KeyDown += (sender, evt) => { keyDown(game, sender, evt); };
		
		/* - Timer/Loop - */
		timer.Interval = 1000 / MAX_FPS;
		timer.Elapsed += (sender, evt) => { window.Refresh(); };
		timer.AutoReset = true;
		timer.Enabled = true;
		
		Application.Run(window);
		return;
	}
	
	public static void uninit() {
		window.Dispose();
		timer.Dispose();
		font.Dispose();
		strFormat.Dispose();
		gfx.Dispose();
		return;
	}
}