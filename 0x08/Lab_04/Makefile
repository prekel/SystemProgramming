MAKE = make

.PHONY: Lab_04_Lib Lab_04_Console clean

all: Lab_04_Console Lab_04_Lib

Lab_04_Lib:
	$(MAKE) -C $@

Lab_04_Console: Lab_04_Lib
	$(MAKE) -C $@

clean:
	$(MAKE) $@ -C Lab_04_Lib
	$(MAKE) $@ -C Lab_04_Console
