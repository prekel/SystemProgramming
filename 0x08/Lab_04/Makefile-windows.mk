MAKE = mingw32-make

.PHONY: Lab_04_Lib Lab_04_Console clean

all : Lab_04_Console Lab_04_Lib getopt-from-mingw

Lab_04_Lib:
	$(MAKE) -C $@

getopt-from-mingw:
	$(MAKE) -C $@

Lab_04_Console: Lab_04_Lib getopt-from-mingw
	$(MAKE) -C $@

clean:
	$(MAKE) $@ -C getopt-from-mingw
	$(MAKE) $@ -C Lab_04_Lib
	$(MAKE) $@ -C Lab_04_Console
