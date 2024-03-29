CC = gcc # Compiler to use
OPTIONS = -O2 -g -Wall # -g for debug, -O2 for optimise and -Wall additional messages
INCLUDES = -I . # Directory for header file
OBJS = main.o module.o # List of objects to be build
.PHONY: all clean # To declare all, clean are not files
	 
all: ${OBJS}
	    @echo "Building.." # To print "Building.." message
		    ${CC} ${OPTIONS} ${INCLUDES} ${OBJS} -o dan_shell 
			 
%.o: %.c  # % pattern wildcard matching
	    ${CC} ${OPTIONS} -c $*.c ${INCLUDES}
list:
	    @echo $(shell ls) # To print output of command 'ls'
		 
clean:
	    @echo "Cleaning up.."
		    -rm -rf *.o # - prefix for ignoring errors and continue execution
			    -rm dan_shell
