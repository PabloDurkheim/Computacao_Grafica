all:
	@echo 
	gcc jupiter.c -o jupiter -lGL -lGLU -lglut -lSOIL -lSDL -lSDLmain -lSDL_image -lSDL_mixer -lm
install-libraries:
	@echo 
	sudo apt-get update
	sudo apt-get install libsoil-dev 
	sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
	sudo apt-get install freeglut3-dev
run:
	@echo 
	./jupiter
clean:
	@echo 
	rm jupiter
