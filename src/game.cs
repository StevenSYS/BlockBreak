using System;
using System.Collections.Generic;

using static class_entity;

using static misc;
using static impl;
using static random;
using static progInfo;

class class_game {
	public enum inputs {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		RESET,
		NONE
	}
	
	internal readonly byte[,] colors = {
		{ 0x00, 0x00, 0xAA },
		{ 0x00, 0xAA, 0x00 },
		{ 0x00, 0xAA, 0xAA },
		{ 0xAA, 0x00, 0x00 },
		{ 0xAA, 0x00, 0xAA },
		{ 0xAA, 0x55, 0x00 },
		{ 0x55, 0x55, 0xFF },
		{ 0x55, 0xFF, 0x55 },
		{ 0x55, 0xFF, 0xFF },
		{ 0xFF, 0x55, 0x55 },
		{ 0xFF, 0x55, 0xFF },
		{ 0xFF, 0xFF, 0x55 }
	};
	
	internal bool timerStart = false;
	internal byte level = 1;
	internal byte blockCount = 0;
	internal ushort timer = 0;
	internal uint score = 0;
	internal uint highScore = 0;
	
	internal class_entity player;
	internal List<class_object> blocks = new List<class_object>();
	
	internal void generateLevel(byte level) {
		byte randomColor = 0;
		byte prevRandomColor;
		int[] blockSize = {
			RENDER_WIDTH / level,
			(int)(RENDER_HEIGHT / (level * 1.5))
		};
		
		blockCount = 0;
		
		if (level > 0 && level <= MAX_LEVEL) {
			for (byte y = 0; y < level; y++) {
				prevRandomColor = randomColor;
				
				while (randomColor == prevRandomColor) {
					randomColor = random.get();
				}
				
				for (byte x = 0; x < level; x++) {
					if (
						(x * blockSize[0] < RENDER_WIDTH) &&
						(y * blockSize[1] < RENDER_HEIGHT)
					) {
						blockCount++;
						blocks.Add(
							new class_object(
								colors[randomColor, 0], colors[randomColor, 1], colors[randomColor, 2],
								blockSize[0], blockSize[1],
								x * blockSize[0], y * blockSize[1],
								true
							)
						);
					}
				}
			}
		}
		return;
	}
	
	internal void init() {
		timer = (ushort)safeAddU((uint)timer, (uint)(level * 35), 0xFFFF);
		
		while (blocks != null && blocks.Count > 0) {
			for (byte i = 0; i < blocks.Count; i++) {
				blocks[i].visible = false;
				blocks.RemoveAt(i);
			}
		}
		
		player = new class_entity(
			0xFF, 0xFF, 0xFF,
			entity_directions.NONE,
			PLAYER_WIDTH, PLAYER_HEIGHT,
			PLAYER_START_X, PLAYER_START_Y,
			PLAYER_SPEED,
			true
		);
		
		this.generateLevel(level);
		return;
	}
	
	internal void reset() {
		this.timer = 0;
		this.level = 1;
		this.score = 0;
		this.timerStart = false;
		this.init();
		return;
	}
	
	internal void input(inputs input) {
		random.index++;
		switch (input) {
			case inputs.UP:
			case inputs.DOWN:
			case inputs.LEFT:
			case inputs.RIGHT:
				if (!this.timerStart) {
					this.timerStart = true;
				}
				this.player.direction = (entity_directions)input;
				break;
			case inputs.RESET:
				this.reset();
				break;
			default:
				break;
		}
		return;
	}
	
	public void draw(object sender, System.Windows.Forms.PaintEventArgs evt) {
		if (blockCount == 0) {
			level = (byte)safeAddU((uint)level, 1, MAX_LEVEL);
			score = (uint)safeAddU(score, (uint)timer / 4, 0xFFFFFFFF);
			init();
		}
		
		if (this.player.position[1] <= SCREEN_EDGE_UP) {
			this.player.direction = entity_directions.DOWN;
			this.player.position[1] = SCREEN_EDGE_UP;
		} else if (this.player.position[1] >= SCREEN_EDGE_DOWN) {
			this.player.direction = entity_directions.UP;
			this.player.position[1] = SCREEN_EDGE_DOWN;
		} else if (this.player.position[0] <= SCREEN_EDGE_LEFT) {
			this.player.direction = entity_directions.RIGHT;
			this.player.position[0] = SCREEN_EDGE_LEFT;
		} else if (this.player.position[0] >= SCREEN_EDGE_RIGHT) {
			this.player.direction = entity_directions.LEFT;
			this.player.position[0] = SCREEN_EDGE_RIGHT;
		}
		
		this.player.draw();
		foreach (class_object block in blocks) {
			if (block.visible) {
				block.draw();
				if (player.collision(block)) {
					block.visible = false;
					blockCount--;
					score = safeAddU(score, 10, 0xFFFFFFFF);
				}
			}
		}
		
		if (this.timerStart) {
			timer--;
		}
		
		if (timer == 0) {
			reset();
			if (this.score > this.highScore) {
				this.highScore = this.score;
				/* Save high score to the high score file */
			}
		}
		
		impl.drawText(
			0xFF, 0xFF, 0xFF,
			timer.ToString(),
			0, RENDER_HEIGHT - (int)(FONT_HEIGHT * 6)
		);
		impl.drawText(
			0xFF, 0xFF, 0xFF,
			highScore.ToString(),
			0, RENDER_HEIGHT - (int)(FONT_HEIGHT * 3)
		);
		impl.drawText(
			0xFF, 0xFF, 0xFF,
			score.ToString(),
			0, RENDER_HEIGHT - (int)(FONT_HEIGHT * 1.5)
		);
		return;
	}
	
	public class_game() {
		this.init();
		impl.init(this);
		return;
	}
}