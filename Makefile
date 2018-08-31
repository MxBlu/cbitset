
CC = gcc

test_driver : test_driver.o cbitset.o

test_driver.o : test_driver.c
cbitset.o : cbitset.c cbitset.h

clean : 
	rm -f $(BINS) *.o
