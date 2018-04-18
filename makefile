
CC= g++


INCLUDE = -Ilib/
VERSION = c++11
CFLAGS = -std=$(VERSION)

SQL_FLAGS = -I/usr/local/include -I/usr/local/include/cppconn -Wl,-Bdynamic 

LINK_FLAGS = -lmysqlcppconn  

CFLAGS += $(SQL_FLAGS)

FILES = main.cpp 

OBJECTS = $(foreach x, $(basename $(wildcard lib/objects/*.cpp)), $(x).o)

LIB_OBJ =  $(foreach x, $(basename $(wildcard lib/*.cpp)), $(x).o)

.PHONY: clean

all: $(OBJECTS) $(LIB_OBJ) final
	
	
final: 
	$(CC) -g $(FILES) -o final $(CFLAGS)  $(LIB) $(OBJECTS) $(LIB_OBJ) $(LINK_FLAGS)

output:
	$(CC) -g result.cpp -o result $(CFLAGS) $(LIB) lib/objects/sql.o $(LINK_FLAGS)

clean: 
	rm -f $(OBJECTS) $(LIB_OBJ) 

fclean:
	rm -f final output
	
re: fclean all

test: re
	./final "./test"
	make output

$(OBJECTS): lib/objects/%.o : lib/objects/%.cpp
	$(CC) $(CFLAGS) -c $< $(LIB) -o $@ 

$(LIB_OBJ): lib/%.o : lib/%.cpp
	$(CC) $(CFLAGS) -c $<  -o $@ $(LIB)
	

