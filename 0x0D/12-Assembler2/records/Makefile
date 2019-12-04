AS = as
LD = gcc

ASFLAGS = --32
LDFLAGS = -m32

all : read-records write-records

read-record.o : read-record.s
	$(AS) $(ASFLAGS) $< -o $@
    
read-records.o : read-records.s
	$(AS) $(ASFLAGS) $< -o $@

write-newline.o : write-newline.s
	$(AS) $(ASFLAGS) $< -o $@

write-record.o : write-record.s
	$(AS) $(ASFLAGS) $< -o $@

write-records.o : write-records.s
	$(AS) $(ASFLAGS) $< -o $@

count-chars.o : count-chars.s
	$(AS) $(ASFLAGS) $< -o $@


write-records : write-records.o write-record.o write-newline.o count-chars.o
	$(LD) $(LDFLAGS) $^ -o $@

read-records : read-records.o read-record.o write-newline.o count-chars.o
	$(LD) $(LDFLAGS) $^ -o $@

.PHONY : clean
clean :
	rm write-records read-records *.o