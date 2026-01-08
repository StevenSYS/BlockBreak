class stringPointer {
	string = "";
	memPos = 0;
	
	init(memory) {
		var stringArray = [];
		var currentCharacter;
		var memArray = new Uint8Array(memory);
		
		for (var i = this.memPos; i < memArray.length; i++) {
			currentCharacter = String.fromCharCode(memArray[i]);
			if (currentCharacter == "\0") {
				break;
			}
			stringArray.push(currentCharacter);
		}
		this.string = stringArray.join("");
		return;
	}
};