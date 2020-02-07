cc -c simproc.c simproc.h 
cc -c test_simproc.c
cc test_simproc.o simproc.o -o test_simproc
./test_simproc
