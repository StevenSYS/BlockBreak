/*
	Date and time format:	MM/DD/YYYY HH:MM TT
	Last Modified:		11/11/2024 05:00 PM
*/

/* Booleans */
BlockBreak_Reset = false;
BlockBreak_TimerStart = false;
BlockBreak_ExitDown = false;
 
/* Intergers */
BlockBreak_FPS = 30;
BlockBreak_Width = 0;
BlockBreak_Height = 0;
BlockBreak_Pos = [156, 230];
BlockBreak_Direction = 0;
BlockBreak_Level = 1;
BlockBreak_Timer = 500;
BlockBreak_Score = 0;
BlockBreak_HighScore = 0;
 
/* Strings */
BlockBreak_RandomColor = "";

function BlockBreak_Init() {
	$(".Global_GameLayer").css("cursor", "none");
	$(".Global_GameLayer").css("user-select", "none");
	$("title").text("Block Break - " + Global_Name);
	if (!$(".BlockBreak_CRT").length)
		Element_Add($(".Global_GameLayer"), "div", "", "BlockBreak_CRT", "");
	Element_Add($(".Global_GameLayer"), "div", BlockBreak_Timer, "BlockBreak_Timer", "");
	Element_Add($(".Global_GameLayer"), "div", "0", "BlockBreak_Score", "");
	Element_Add($(".Global_GameLayer"), "div", BlockBreak_HighScore, "BlockBreak_HighScore", "");
	BlockBreak_Start();
}

function BlockBreak_Start() {
	if (localStorage.getItem("BlockBreak_HighScore") == undefined)
		localStorage.setItem("BlockBreak_HighScore", 0);
	BlockBreak_HighScore = localStorage.getItem("BlockBreak_HighScore");
	$(".BlockBreak_HighScore").text(BlockBreak_HighScore);
	if ($(".BlockBreak_Dot").length) {
		$(".BlockBreak_Dot").remove();
		$(".BlockBreak_Block").remove();
		BlockBreak_Direction = 0;
		BlockBreak_Pos[0] = 156;
		BlockBreak_Pos[1] = 230;
		clearInterval(BlockBreak_Interval);
		if (!BlockBreak_Reset) {
			BlockBreak_Score += Math.round(BlockBreak_Timer / 4);
			BlockBreak_Level++;
			BlockBreak_Timer += BlockBreak_Level * 50;
		}
		$(".Timer").text(BlockBreak_Timer);
		$(".Score").text(BlockBreak_Score);
	}

	Element_Add($(".Global_GameLayer"), "div", "", "BlockBreak_Dot", "");
	
	for (i = 0; i <= BlockBreak_Level + 4; i++) {
		BlockBreak_RandomColor = (Math.random() * 0xFFFFFF << 0).toString(16).padStart(6, "0");
		for (j = 0; j <= BlockBreak_Level; j++) {
			BlockBreak_Width = 320 / (BlockBreak_Level + 1);
			BlockBreak_Height = 240 / (BlockBreak_Level + 7);
			Element_Add($(".Global_GameLayer"), "div", "", "BlockBreak_Block", "background-color: #" + BlockBreak_RandomColor + "; left: " + j * BlockBreak_Width + "px; top: " + i * BlockBreak_Height + "px; width:" + BlockBreak_Width + "px; height: " + BlockBreak_Height + "px;");
	}}

	BlockBreak_Interval = setInterval(BlockBreak_gameLoop, 1000 / BlockBreak_FPS);

	$(document).keydown(function(event) {
		if (!BlockBreak_TimerStart)
			BlockBreak_TimerStart = true;
		switch (event.keyCode) {
			case 13: // Enter (Exit)
				if (!BlockBreak_ExitDown) 
					window.location.href = "?menu=MainMenu";
				BlockBreak_ExitDown = true;
				break;
			case 37: // Left 
				BlockBreak_Direction = 1;
				break;
			case 38: // Up
				BlockBreak_Direction = 2;
				break
			case 39: // Right 
				BlockBreak_Direction = 3;
				break;
			case 40: // Down
				BlockBreak_Direction = 4;
				break;
	}});

	function BlockBreak_gameLoop() {
		if (BlockBreak_Timer > 0 && BlockBreak_TimerStart) {
			BlockBreak_Timer--;
			$(".BlockBreak_Timer").text(BlockBreak_Timer);
		} else if (BlockBreak_Timer == 0) {
			if (BlockBreak_Score > localStorage.getItem("BlockBreak_HighScore")) {
				localStorage.setItem("BlockBreak_HighScore", BlockBreak_Score);
				BlockBreak_HighScore = BlockBreak_Score;
			}
			BlockBreak_Reset = true;
			BlockBreak_TimerStart = false;
			BlockBreak_Timer = 500;
			BlockBreak_Level = 1;
			BlockBreak_Score = 0;
			BlockBreak_Start();
		}
		
		$(".BlockBreak_Dot").css("top", BlockBreak_Pos[1]);
		$(".BlockBreak_Dot").css("left", BlockBreak_Pos[0]);

		touchingEdge = $(".Global_Edge").overlaps($(".BlockBreak_Dot"));	
		touchingBlock = $(".BlockBreak_Block").overlaps($(".BlockBreak_Dot"));
		if (!$(".BlockBreak_Block").length) {
			BlockBreak_Reset = false;
			BlockBreak_Start();
		}
		if (touchingEdge.targets.length || touchingBlock.targets.length) {
			if (touchingBlock.targets.length) {
				Sound_Play("BlockBreak/BlockHit.wav", 25);
				for (i = 0; i < touchingBlock.targets.length; i++)
					touchingBlock.targets[i].remove();
					BlockBreak_Score += i * 10;
					$(".Score").text(BlockBreak_Score);
			} else {
				Sound_Play("BlockBreak/EdgeHit.wav", 25);
				if (BlockBreak_Pos[1] >= 233)
					BlockBreak_Direction = 2;
				else if (BlockBreak_Pos[1] <= 1)
					BlockBreak_Direction = 4;
				if (BlockBreak_Pos[0] >= 313)
					BlockBreak_Direction = 1;
				else if (BlockBreak_Pos[0] <= 1)
					BlockBreak_Direction = 3;
		}}

		if (BlockBreak_Pos[1] > 240)
			BlockBreak_Pos[1] = 240;
		if (BlockBreak_Pos[1] < 0)
			BlockBreak_Pos[1] = 0;
		if (BlockBreak_Pos[0] > 320)
			BlockBreak_Pos[0] = 320;
		if (BlockBreak_Pos[1] < 0)
			BlockBreak_Pos[0] = 0;

		if (BlockBreak_Direction > 0) {
			switch (BlockBreak_Direction) {
			case 1: // Left
				BlockBreak_Pos[0] -= 4;
				break;
			case 2: // Up
				BlockBreak_Pos[1] -= 4;
				break;
			case 3: // Right
				BlockBreak_Pos[0] += 4;
				break;
			case 4: // Down
				BlockBreak_Pos[1] += 4;
				break;
}}}}