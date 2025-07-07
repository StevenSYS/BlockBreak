const urlParams = new URLSearchParams(window.location.search);

Global_Name = "BlockBreakJQ";

$("body").append("<script src=\"Modules/ModuleAdder.js\"></script>");
Module_Add("Overlaps.js");
Module_Add("SoundMusic.js");
Module_Add("ElementStuff.js");

$(document).ready(function() {
	$("body").on("contextmenu", function() {
		return false;
	});
	if (urlParams.has("jsFile")) {
		var jsFile = urlParams.get("jsFile");
		var soundWrapperVer = urlParams.get("sndVer");
		
		Module_Add("BlockBreak/" + jsFile);
		
		switch (jsFile) {
			case "BB1111240500P.js":
				BlockBreak_Init();
				break;
			default:
				Module_Add("Wrappers/SoundWrapper" + soundWrapperVer + ".js");
				blockBreakInit();
				break;
		}
	} else if (urlParams.has("Menu")) {
		Module_Add("MenuLoader.js");
		$.getJSON("Assets/Menus/" + urlParams.get("Menu") + ".json", function(JSON) {
			Menu_Load(JSON, false, urlParams.get("Menu"))
		});
	} else {
		Module_Add("MenuLoader.js");
		$.getJSON("Assets/Menus/MainMenu.json", function(JSON) {
			Menu_Load(JSON);
		});
	}
});