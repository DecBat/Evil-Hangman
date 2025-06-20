CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o my_string.o generic_vector.o associative_array.o
TEST_OBJECTS = unit_test.o test_def.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)

unit_test: my_string.o $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(TEST_OBJECTS) my_string.o

my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o

generic_vector.o: generic_vector.c
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o

associative_array.o: associative_array.c associative_array.h
	$(CC) $(CFLAGS) -c associative_array.c -o associative_array.o

main.o: main.c my_string.h unit_test.h
	$(CC) $(CFLAGS) -c main.c -o main.o

unit_test.o: unit_test.c my_string.h unit_test.h
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o

test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o

clean:
	rm -f string_driver unit_test $(OBJECTS) $(TEST_OBJECTS)
