all:
	gcc main.c -o program-runner

clean:
	rm *.o || true
	rm program-runner || true
