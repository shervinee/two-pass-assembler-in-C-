p4: main.o firstPass.o secondPass.o helperFunctions.o hash.o
	gcc -g main.o firstPass.o secondPass.o helperFunctions.o hash.o -o p4
main.o: main.c P4Headers.h
	gcc -c main.c
firstPass.o: firstPass.c P4Headers.h
	gcc -c firstPass.c
secondPass.o: secondPass.c P4Headers.h
	gcc -c secondPass.c
helperFunctions.o: helperFunctions.c P4Headers.h
	gcc -c helperFunctions.c
hash.o: hash.c P4Headers.h
	gcc -c hash.c
clean:
	rm -f *.o core p4


