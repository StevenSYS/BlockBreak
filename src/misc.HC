U0 safeAddU8(
	U8 *var,
	U8 value,
	U8 max
) {
	if ((*var + value) > max) {
		*var = max;
	} else {
		*var += value;
	}
	return;
}

U0 safeAddU16(
	U16 *var,
	U16 value,
	U16 max
) {
	if ((*var + value) > max) {
		*var = max;
	} else {
		*var += value;
	}
	return;
}

U0 safeAddU32(
	U32 *var,
	U32 value,
	U32 max
) {
	if ((*var + value) > max) {
		*var = max;
	} else {
		*var += value;
	}
	return;
}

U0 lessThanSetU16(
	U16 *var,
	U16 value
) {
	if (var < value) {
		*var = value;
	}
	return;
}