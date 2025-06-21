#!/bin/bash
directories=(
	"sdl3"
	"glut"
	"glfw3"
	"sdl3GL"
	"raylib"
)

impls=(
	"SDL3"
	"GLUT"
	"GLFW3"
	"SDL3GL"
	"raylib"
)

buildDir="buildTest"

programName="BlockBreakC"

mkdirine() {
	if [ ! -d "$1" ]; then
		mkdir "$1"
	fi
}

build() {
	pushd "$1"
		make -j${nproc}
		if [ "$2" == "run" ]; then
			mv "libImpl.so" "../.."
			"../../$programName"
		fi
	popd
}

config() {
	cmake \
		-B"$1" \
		-S".." \
		-DCMAKE_BUILD_TYPE=Debug \
		-DBUILD_SHARED_LIBS=ON \
		-DIMPL="$2" \
		-DBUILD_ONLY_IMPL=$3
}

mkdirine "$buildDir"

pushd "$buildDir"
	if [ ! -d "impls" ]; then
		config "." "Dummy" "OFF"
		
		mkdirine "impls"
		for i in "${directories[@]}"; do
			mkdirine "impls/$i"
		done
		
		for i in "${!directories[@]}"; do
			config "impls/${directories[$i]}" "${impls[$i]}" "ON"
		done
	fi
	
	
	rm "libImpl.so"
	make -j${nproc}
	
	if [ "$1" == "run" ]; then
		"./$programName"
	fi
	
	for i in "${!directories[@]}"; do
		build "impls/${directories[$i]}" "$1"
	done
popd