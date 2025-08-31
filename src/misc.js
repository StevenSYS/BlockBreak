function safeAdd(vari, value, max) {
	if ((vari + value) > max) {
		return max;
	} else {
		return vari + value;
	}
}

function lessThan(vari, value) {
	if (vari < value) {
		return value;
	} else {
		return vari;
	}
}