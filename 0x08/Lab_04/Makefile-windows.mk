MAKE = mingw32-make

.PHONY: Lab_04_Lib Lab_04_Console clean

all : Lab_04_Console Lab_04_Lib getopt-from-mingw

MAKEFILE = Makefile-windows.mk

Lab_04_Lib:
	$(MAKE) -C $@ -f $(MAKEFILE)

getopt-from-mingw:
	$(MAKE) -C $@ -f $(MAKEFILE)

Lab_04_Console: Lab_04_Lib getopt-from-mingw
	$(MAKE) -C $@ -f $(MAKEFILE)

clean:
	$(MAKE) $@ -C getopt-from-mingw -f $(MAKEFILE)
	$(MAKE) $@ -C Lab_04_Lib -f $(MAKEFILE)
	$(MAKE) $@ -C Lab_04_Console -f $(MAKEFILE)
