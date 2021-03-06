CC= g++

INCLUDE = -Ilib/
VERSION = c++14
CFLAGS = -std=$(VERSION)
SQL_FLAGS = -I/usr/local/include -I/usr/local/include/cppconn -Wl,-Bdynamic 
LINK_FLAGS = -lmysqlcppconn
CFLAGS += $(SQL_FLAGS)

FILES = main.cpp

OUTPUT_FILES = lib/objects/sql.cpp

OUTPUT_OBJECTS = $(foreach x, $(basename $(OUTPUT_FILES)), $(x).o)

OBJECTS = $(foreach x, $(basename $(wildcard lib/objects/*.cpp)), $(x).o)

LIB_OBJ =  $(foreach x, $(basename $(wildcard lib/*.cpp)), $(x).o)

.PHONY: clean

all: $(OBJECTS) $(LIB_OBJ) final
	
final: 
	$(CC) -g $(FILES) -o final $(CFLAGS) $(LIB) $(OBJECTS) $(LIB_OBJ) $(LINK_FLAGS)

output:
	$(CC) -g result.cpp -o result $(CFLAGS) $(LIB) $(OUTPUT_OBJECTS)  $(LINK_FLAGS)

generate:
	$(CC) -g generate.cpp -o generate $(CFLAGS) $(LIB) $(OUTPUT_OBJECTS)  $(LINK_FLAGS)

clean: 
	rm -f $(OBJECTS) $(LIB_OBJ) 

fclean:
	rm -f final result

purge: fclean
	make clean
	rm -f result.cpp result.h generate

zip: purge
	zip out.zip -r ./*

	
re: fclean all

test: re
	./final "./test/test"
	make output
	./result
	rm -f result
	./final -emf "./test/emftest"
	make output 
	./result
	rm -f result
	./final -emf "./test/example1"
	make output 
	./result
	rm -f result
	./final -emf "./test/example2"
	make output 
	./result
	rm -f result
	./final -emf "./test/example3"
	make output 
	./result
	rm -f result
	./final -emf "./test/example4"
	make output 
	./result
	rm -f result
	./final -emf "./test/example5"
	make output 
	./result
	rm -f result
	./final -emf "./test/example6"
	make output 
	./result

sample:
	$(CC) -g test.cpp -o test $(CFLAGS) 

$(OBJECTS): lib/objects/%.o : lib/objects/%.cpp
	$(CC) -g $(CFLAGS) -c $< $(LIB) -o $@ 

$(LIB_OBJ): lib/%.o : lib/%.cpp
	$(CC) -g $(CFLAGS) -c $<  -o $@ $(LIB)