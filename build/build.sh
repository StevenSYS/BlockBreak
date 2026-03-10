#!/bin/bash
compile() {
	output="$1.wasm"
	
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
		-I ../src/BlockBreakC/src \
		../src/shared.c \
		../src/BlockBreakC/src/*.c
	
	wasm-strip "$output"
}

compile "BlockBreakC-WASM" 