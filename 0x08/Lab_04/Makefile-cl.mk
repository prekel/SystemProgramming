MAKE = mingw32-make

MAKEFILE = Makefile-cl.mk

all:
	$(MAKE) -C getopt-from-mingw -f $(MAKEFILE)
	$(MAKE) -C Lab_04_Lib -f $(MAKEFILE)
	$(MAKE) -C Lab_04_Console -f $(MAKEFILE)

clean:
	$(MAKE) -C getopt-from-mingw -f $(MAKEFILE) clean
	$(MAKE) -C Lab_04_Lib -f $(MAKEFILE) clean
	$(MAKE) -C Lab_04_Console -f $(MAKEFILE) clean
