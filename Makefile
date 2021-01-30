LDLIBS=-lpcap

all: deauth-attack

deauth-attack: main.o header.o mac.o
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f deauth-attack *.o