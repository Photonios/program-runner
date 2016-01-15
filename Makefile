all:
	gcc main.c -o program-runner

install:
	cp program-runner /usr/bin

uninstall:
	rm /usr/bin/program-runner

clean:
	rm *.o || true
	rm program-runner || true
