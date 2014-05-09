OBJECTS=baulicht.xml blink.xml text.xml
CPP2XML=qdbuscpp2xml

all: $(OBJECTS)

%.xml: %.h
	$(CPP2XML) -o ../$@ $<

