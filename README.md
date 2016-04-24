# pacman-revisited
As the name says it is the great old-school Pacman rewritten.

## Info
You can eat peas and run away from the ghost with great joy by now, nevertheless it really requires a lot of work to be done. Here is a small to-do list:
- [x] Added possibility to change the map
- [ ] Add more enemies
- [ ] Add points info-box and pretty menu (the info was being sent to the stdout by so far and this is really unacceptable)

## Controls
Use arrows to turn. You can organise a queue of turns by pressing multiple arrows one after another. If done so, the Pacman will try to turn the first direction in the queue and then (in case of successful turn) pop it.

## Dependences
*Qt5*  libraries are needed. You can install them by:
``` bash
 sudo apt-get install qt5-default
```

If you still receive an error, installation of *qt-sdk* may fix it:
``` bash
sudo apt-get install qt-sdk
```
 
Then you may need to **reinstall** *qt5-default*, as *qt-sdk* replaces qt5 libraries with the qt4 ones. So run it again: 
``` bash
sudo apt-get install qt5-default
```

## Build
Run in the project's directory:
``` bash
qmake
make
```
