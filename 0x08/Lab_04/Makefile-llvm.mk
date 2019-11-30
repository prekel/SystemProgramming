MAKE = make

MAKEFILE = Makefile-llvm.mk

.PHONY: Lab_04_Lib Lab_04_Console clean

all: Lab_04_Console Lab_04_Lib

Lab_04_Lib:
	$(MAKE) -C  $@ -f $(MAKEFILE)

Lab_04_Console: Lab_04_Lib
	$(MAKE) -C  $@ -f $(MAKEFILE)

clean:
	$(MAKE) $@ -C Lab_04_Lib -f $(MAKEFILE)
	$(MAKE) $@ -C Lab_04_Console -f $(MAKEFILE)

