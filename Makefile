all:
	gcc main.c -o program-runner

install:
	cp program-runner /usr/bin
	cp program-runner-start /usr/bin
	cp program-runner-stop /usr/bin
	cp program-runner-restart /usr/bin
	cp program-runner-lib.sh /usr/bin

uninstall:
	rm /usr/bin/program-runner || true
	rm /usr/bin/program-runner-start || ture
	rm /usr/bin/program-runner-stop || true
	rm /usr/bin/program-runner-restart || true
	rm /usr/bin/program-runner-lib.sh || true

clean:
	rm *.o || true
	rm program-runner || true
