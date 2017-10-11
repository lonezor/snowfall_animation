CXX=g++
CFLAGS=-Wall -g3 -O3 `pkg-config --cflags cairo` -Irendering -Ienvironment/object
LIBS=`pkg-config --libs cairo`

all:
	$(CXX) $(CFLAGS) *.cpp environment/object/*.cpp rendering/*.cpp -o snowfall_animation $(LIBS)
test:
	rm -f /tmp/out.png && make && ./snowfall_animation && dbus-launch eog /tmp/out.png	
