#!/bin/bash
compile() {
	output="$1.wasm"
	
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
		-Wl,--export-dynamic \
		-Wall \
		-o "$output" \
		-DFONT_HEIGHT=16 \
		$screenshotFlags \
		-I ../src/BlockBreakC/src/impl \
		-I ../src/BlockBreakC/src/impl/highScore \
		-I ../src/BlockBreakC/src/impl/screenshot \
		-I ../src/BlockBreakC/src/shared \
		-I ../src/BlockBreakC/src \
		../src/impl/shared.c \
		../src/BlockBreakC/src/shared/*.c \
		../src/BlockBreakC/src/*.c
	
	wasm-strip "$output"
}

compile "BlockBreakC-WASM" true