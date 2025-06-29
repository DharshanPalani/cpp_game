#!/bin/sh

g++ $(find src -name "*.cpp") -o game.exe -Iraylib/include raylib/lib/libraylib.a -lopengl32 -lgdi32 -lwinmm

if [ $? -eq 0 ]; then
    echo "Build successful. Running game..."
    ./game.exe
else
    echo "Build failed."
fi

