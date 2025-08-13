<?php
	function createOption(
		$name, $argName,
		$type,
		$default,
		$min = "", $max = "",
		$step = "1"
	) {
		printf(
			"\t<label for=\"%s\">%s:</label>\n",
			$argName, $name
		);
		if (strcmp($type, "checkbox") == 0) {
			printf("\t\t\t\t<label class=\"checkbox\">\n\t");
		}
		printf(
			"\t\t\t\t<input type=\"%s\" name=\"%s\" ",
			$type, $argName
		);
		if (strcmp($type, "checkbox") == 0) {
			if (strcmp($type, "On") == 0) {
				printf("checked");
			}
		} else if (strcmp($type, "number") == 0) {
			printf(
				"min=\"%s\" max=\"%s\" value=\"%s\" step=\"%s\"",
				$min, $max, $default, $step
			);
		}
		printf(">\n");
		if (strcmp($type, "checkbox") == 0) {
			printf("\t\t\t\t\t<div class=\"icon\"></div>\n");
			printf("\t\t\t\t</label>\n");
		} 
		printf("\t\t\t\t<br>Default: %s\n", $default);
		printf("\t\t\t\t<br>\n\t\t\t");
		return;
	}
?>
<!DOCTYPE html>
<html lang="en">
	<head>
		<title>BlockBreak Web Versions</title>
		<link rel="stylesheet" href="style.css">
		<link rel="icon" type="image/png" href="images/favicon.png">
		<link rel="apple-touch-icon" sizes="192x192" href="images/AppleTouch.png">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
	</head>
	<body>
		<div>BlockBreakJS - Custom Settings</div>
		<hr>
		<div class="warning">WARNING: High scores are disabled when using custom settings!</div>
		<br>
		<form action="JS">
			<?php
				$items = array(
					array("name" => "Game Width", "argName" => "width", "type" => "number", "default" => "640", "min" => "1", "max" => "9999", "step" => "1.0"),
					array("name" => "Game Height", "argName" => "height", "type" => "number", "default" => "472", "min" => "1", "max" => "9999", "step" => "1.0"),
					array("name" => "Player Speed", "argName" => "playerSpeed", "type" => "number", "default" => "8", "min" => "1", "max" => "999", "step" => "1.0"),
					array("name" => "Player Width", "argName" => "playerWidth", "type" => "number", "default" => "16", "min" => "1", "max" => "9999", "step" => "1.0"),
					array("name" => "Player Height", "argName" => "playerHeight", "type" => "number", "default" => "16", "min" => "1", "max" => "9999", "step" => "1.0"),
					array("name" => "Font Size", "argName" => "fontSize", "type" => "number", "default" => "16", "min" => "1", "max" => "999", "step" => "0.01"),
					array("name" => "Touch Dead Zone", "argName" => "touchDeadZone", "type" => "number", "default" => "32", "min" => "1", "max" => "999", "step" => "1.0"),
					array("name" => "Timer Speed", "argName" => "timerSpeed", "type" => "number", "default" => "1", "min" => "0", "max" => "999", "step" => "0.01"),
					array("name" => "Max Blocks", "argName" => "maxBlocks", "type" => "number", "default" => "255", "min" => "1", "max" => "999", "step" => "1.0"),
					array("name" => "FPS", "argName" => "fps", "type" => "number", "default" => "30", "min" => "1", "max" => "240", "step" => "1.0"),
					array("name" => "Disable Border", "argName" => "noBorder", "type" => "checkbox", "default" => "Off", "min" => "", "max" => "", "step" => "1.0"),
					array("name" => "Disable Screenshot Button", "argName" => "noSButton", "type" => "checkbox", "default" => "Off", "min" => "", "max" => "", "step" => "1.0")
				);
				foreach ($items as $item) {
					createOption(
						$item["name"], $item["argName"],
						$item["type"],
						$item["default"],
						$item["min"],
						$item["max"],
						$item["step"],
					);
				}
			?><br>
			<input type="submit" class="button buttonGray" value="Play">
		</form>
		<br>
	</body>
</html>