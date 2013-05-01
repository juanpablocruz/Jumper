CC=g++
LDFLAGS=`pkg-config --libs allegro-5.0 allegro_primitives-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0`
SOURCES=main.cpp character.cpp 
HEADERS=objects.h
EXECUTABLE=jumper

.PHONY:	all clean $(EXECUTABLE)

all: $(SOURCES) $(EXECUTABLE) $(HEADERS)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS) 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o