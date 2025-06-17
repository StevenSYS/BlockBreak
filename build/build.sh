#!/bin/bash
OUTPUT=BlockBreakC-WASM.wasm

clang \
	--target=wasm32 \
	-O3 \
	--no-standard-libraries \
	-DFONT_HEIGHT=16 \
	-I ../src/BlockBreakC/src/impl \
	-I ../src/BlockBreakC/src/random \
	-I ../src/BlockBreakC/src \
	-Wl,--export-all \
	-Wl,-allow-undefined-file imports.syms \
	../src/BlockBreakC/src/random/random.c \
	../src/*.c \
	../src/BlockBreakC/src/*.c \
	-o "$OUTPUT"

wasm-strip "$OUTPUT"