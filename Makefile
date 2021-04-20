CC = gcc
LD = gcc

CFLAGS = -g -std=gnu99 -pedantic -Wall -Wextra -pthread -lrt
#CFLAGS = -g -std=c99 -pedantic -Wall -Wextra -Werror -lpthread   

all: proj2 proj2.o
#$< jmeno první závislosti		#$@ jmeno cile 		#$^ jmena vsech zavislosti

FILES = *

############## proj2 ###############
proj2: proj2.o
	$(CC) $(CFLAGS) $< -o $@
proj2.o: proj2.c proj2.h
	$(CC) $(CFLAGS) -c $< -o $@ 
#####################################

clean:
	rm *.o proj2
zip:
	zip proj2.zip *.c *.h Makefile
git:
	sudo git add *.c *.h Makefile
	sudo git commit -m "Update."
	sudo git push

merlin:
	scp -r $(FILES) xkuzni04@merlin.fit.vutbr.cz:/homes/eva/xk/xkuzni04/ios/proj2
