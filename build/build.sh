#!/bin/bash
compile() {
	output="$1".wasm
	
	if [ "$2" = true ]; then
		screenshotFlags="-DENABLE_SCREENSHOT"
	else
		screenshotFlags=""
	fi
	
	clang \
		--target=wasm32 \
		-std=c99 \
		-O2 \
		--no-standard-libraries \
		-Wl,--export-all \
		-Wl,-allow-undefined-file imports.syms \
		-Wall \
		-o "$output" \
		-DFONT_HEIGHT=16 \
		$screenshotFlags \
		-I ../src/BlockBreakC/src/impl \
		-I ../src/BlockBreakC/src/impl/highScore \
		-I ../src/BlockBreakC/src/impl/screenshot \
		-I ../src/BlockBreakC/src/input \
		-I ../src/BlockBreakC/src/random \
		-I ../src/BlockBreakC/src \
		../src/impl/shared.c \
		../src/BlockBreakC/src/input/input.c \
		../src/BlockBreakC/src/random/random.c \
		../src/BlockBreakC/src/*.c
	
	wasm-strip "$output"
}

compile "BlockBreakC-WASM" true