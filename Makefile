CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: walk

mac: lab1Mac

walk: walk.cpp joshuaC.cpp rafaelN.cpp erikS.cpp fernandoM.cpp kuljitS.cpp
	g++ $(CFLAGS) walk.cpp joshuaC.cpp rafaelN.cpp erikS.cpp fernandoM.cpp kuljitS.cpp Global.cpp SpriteSheet.cpp Timers.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -owalk


lab1Mac: walk.cpp joshuaC.cpp rafaelN.cpp erikS.cpp fernandoM.cpp kuljitS.cpp
	g++ walk.cpp joshuaC.cpp rafaelN.cpp erikS.cpp fernandoM.cpp kuljitS.cpp Global.cpp SpriteSheet.cpp Timers.cpp libggfontsMac.a -Wall -owalk -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -framework OpenGl -framework Cocoa -lm -lGL

clean:
	rm -f walk
	rm -f *.o

