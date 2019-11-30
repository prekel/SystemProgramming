MAKE = mingw32-make

MAKEFILE = Makefile-mingw.mk

all:
	$(MAKE) -C Lab_04_Lib -f $(MAKEFILE)
	$(MAKE) -C Lab_04_Console -f $(MAKEFILE)

clean:
	$(MAKE) -C Lab_04_Lib -f $(MAKEFILE) clean
	$(MAKE) -C Lab_04_Console -f $(MAKEFILE) clean
