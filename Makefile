build:
	mkdir build
	cc main.c -o ./build/srm

install:
	mkdir build
	cc main.c -o ./build/srm
	sudo mv ./build/srm /bin/
