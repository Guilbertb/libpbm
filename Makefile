TARGET = testpbm
LIB = libpbm
#Makefile petit projet avec skeletonc
CFLAGS = -Wall -pedantic -lm -g
CC=gcc


$(TARGET): $(TARGET).c $(LIB).c
	$(CC) $(LIB).c $(TARGET).c -o $(TARGET) $(CFLAGS)

edit:	$(TARGET).c
	vi $(TARGET).c

gdb:	$(TARGET)
	$(DEB) $(TARGET)

clean:
	rm $(TARGET)

test:   testpbm
	./testpbm
	display image.pbm
