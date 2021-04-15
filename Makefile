CC = gcc
LD = gcc

CFLAGS = -g -std=c99 -pedantic -Wall -Wextra -Werror   

all: proj2 proj2.o
#$< jmeno první závislosti		#$@ jmeno cile 		#$^ jmena vsech zavislosti

############## proj2 ###############
proj2: proj2.o
	$(CC) $(CFLAGS) $< -o $@
proj2.o: proj2.c proj2.h
	$(CC) $(CFLAGS) -c $< -o $@ 
#####################################

#run: tail 
#	./tail
clean:
	rm *.o
zip:
	zip proj2.zip *.c *.h Makefile
git:
	sudo git add *.c *.h Makefile
	sudo git commit -m "Update."
	sudo git push