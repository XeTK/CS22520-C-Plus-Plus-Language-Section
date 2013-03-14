rm -v simple
g++ -o simple main.cpp Gui.cpp Gui.h `pkg-config --libs --cflags gtk+-2.0`
