.PHONY: all clean

CC:= g++-11

CFLAGS = -std=c++17 -Wno-deprecated-enum-enum-conversion -O2
CFLAGS += `pkg-config --cflags --libs opencv4` 

# CFLAGS += `python3-config --cflags --embed`
# LDFLAGS = `python3-config --ldflags --embed`


SOURCES := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCES))
DEPENDS := $(patsubst %.cpp,%.d,$(SOURCES))


all: main

clean:
	$(RM) $(OBJECTS) $(DEPENDS) main

-include $(DEPENDS)

# Make object files
%.o: %.cpp Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Linking the executable from the object files
main: $(OBJECTS)
	$(CC) $^ $(LDFLAGS) $(CFLAGS) -o $@
	./main
