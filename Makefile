all: build run

apt:
	sudo apt-get install i2c-tools libi2c-dev
	# i2cdetect 1
	# i2cget -y 1 0x60 0x1

clean:
	rm -f si5351_cli

build: 
	g++ -ggdb -std=c++11 -li2c -Wfatal-errors -Wall *.cpp -o ./si5351_cli

build_debug: 
	g++ -ggdb -std=c++11 -li2c -Wfatal-errors -Werror -Wall *.cpp -o ./si5351_cli -DSI5351_DEBUG -DSI5351_FATAL_ERRORS=1 '-DSI5351_ON_ERROR=throw 1; '

run:
	./si5351_cli || true
	./si5351_cli 1 3600000.0 -100

RPI ?= pi@raspberrypi.local
rpi:
	rsync -avr . $(RPI):/home/pi/Si5351Arduino4Linux/
	ssh $(RPI) /bin/bash -c 'set -e ; cd /home/pi/Si5351Arduino4Linux/ && pwd && make'