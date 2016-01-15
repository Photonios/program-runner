all:
	mkdir -p bin
	gcc src/main.c -o bin/program-runner

install:
	cp bin/* /usr/bin
	cp scripts /usr/bin

uninstall:
	rm /usr/bin/program-runner || true
	rm /usr/bin/program-runner-start || ture
	rm /usr/bin/program-runner-stop || true
	rm /usr/bin/program-runner-restart || true
	rm /usr/bin/program-runner-lib.sh || true

clean:
	rm *.o || true
	rm -r bin || true
