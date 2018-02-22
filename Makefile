CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: walk

mac: lab1Mac

walk: walk.cpp
	g++ $(CFLAGS) walk.cpp fernandoM.cpp joshuaC.cpp kuljitS.cpp erikS.cpp rafaelN.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -owalk


lab1Mac: walk.cpp
	g++ walk.cpp -Wall -owalk -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -framework OpenGl -framework Cocoa -lm -lGL

clean:
	rm -f walk
	rm -f *.o

