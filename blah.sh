rm -v simple
g++ -o simple main.cpp Gui.cpp Gui.h Node.cpp Node.h Course.cpp Course.h Entrant.cpp Entrant.h Holder.cpp Holder.h FileReader.cpp FileReader.h `pkg-config --libs --cflags gtk+-2.0`
