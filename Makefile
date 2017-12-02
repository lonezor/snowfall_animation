CXX=g++
CFLAGS=-Wall -g3 -O3 `pkg-config --cflags cairo` -I. -Irendering -Iobjects -Ianimation
LIBS=`pkg-config --libs cairo`

all:
	$(CXX) $(CFLAGS) *.cpp objects/*.cpp rendering/*.cpp animation/*.cpp -o snowfall_animation $(LIBS)
test:
	rm -f /home/samba/git/png/*.png && make && ./snowfall_animation && dbus-launch eog /home/samba/git/png/out_000000.png	
view:
	eog /tmp/out_000000.png
