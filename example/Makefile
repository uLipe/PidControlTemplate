#
# TODO: Develop a better build system :P
#
CC=gcc
CFLAGS= -Wall -g2 -O3 -I ../lib
SRC = ../lib/pid_controller_2p2z.c ../lib/pid_controller_numerical.c pi_controller.c

all:
	@rm -f *.o  *.out   
	@rm -rf build/
	@echo "[CC] Building pi_controller example!"
	@$(CC) $(CFLAGS) $(SRC) -o pi_controller.out
	@mkdir build 
	@mv pi_controller.out build/
	@rm -f *.o  *.out   
	@echo "[CC] pi_controller example was built succesfully!"

clean:
	@echo "[CLEAN]: Cleaning !"
	@rm -rf build/
	@echo "[CLEAN]: Done !"
