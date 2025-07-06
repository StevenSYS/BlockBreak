#!/bin/bash
compile() {
	output="$1".wasm
	clang \
		--target=wasm32 \
		-O3 \
		--no-standard-libraries \
		-DFONT_HEIGHT=16 \
		-I ../src/BlockBreakC/src/impl \
		-I ../src/BlockBreakC/src/impl/highScore \
		-I ../src/BlockBreakC/src/random \
		-I ../src/BlockBreakC/src \
		-Wl,--export-all \
		-Wl,-allow-undefined-file imports.syms \
		../src/BlockBreakC/src/random/random.c \
		../src/impls/shared.c \
		../src/BlockBreakC/src/*.c \
		-o "$output"
		wasm-strip "$output"
}

compile "BlockBreakC-WASM"