# **NSU Programming Course** #

This is just a wide branch of my programs which were created due my studying at [NSU](http://nsu.ru/).

### Folders (divided by courses) ###

* **first_year** - C programs (10 labs and archivator project)
* **second_year** - C++ programs (4 labs) and Java programs (3 labs)
* **oop** - C++ programs (5 tasks), see also [site with tasks](http://oop.afti.ru/students/troshnev-danil), but there were some changes, maybe some tasks have different numbers.
* **graphics** - the course of computer graphics, where custom engine was built on C++ with QtCreator and some basics functions of OpenGL lib. It can display a scene with 3D objects, allows to fly around the objects and play animations (key-frames used). Also custom shaders, materials, textures, meshes could be added here.

## C/C++ ##

### 1st year at Computer Sciense Department (first_year dir) ###

It was a long time ago... All labs were written on C.

### 2nd year at Computer Sciense Department (second_year/oop dir) ###

* lab 1 - it's missed T___T, but it was the first time I've touched the C++ and the simple realization of hash-table was there.
* lab 2 - the life game with MVC pattern.
* lab 3 - the prisoners game with strategy pattern.
* lab 4 - the graph structure realization with C++ templates and 2 graph walkers realizations (DFS, BFS).

### Object Oriented Paradigm course (oop dir) ###

* task 1 - long string and record array on C
* task 2 - object factory on C (object oriented C)
* task 3 - calendar program
* task 4 - graph tree building algorithm
* task 5 - topology sort
* task 6 - population game
* task 7 - XMODEM
* task 8 - image (with text) auto rotation algorithm
* task 9 - heap sort algorithm updated with iterators
* task 10 - custom filter iterator realization
* task 11 - custom shared pointer realization
* task 12 - object pool pattern
* task 13 - big vector (with tmp file swapping)
* task 14 - text editor (command pattern), it should be fixed, because history saves text state instead of updates (if it was image editor, my program would work very slow)
* task 15 - decorator pattern for code highlighter (it adds html tags for C++ key words).
* task 16 - wavelet algorithms for last tasks
* tro-jpeg-project - last task which exports images into jpeg. The zip archivator was used to compress data.

## Java ##

### 2nd year at Computer Sciense Department (second_year/java dir) ###

All labs were written according to MVC pattern.

* lab 1 - the simple text parser with words counting
* lab 2 - the calculator with commands (+, -, *, /) and exceptions handling (command patternn used).
* lab 3 - the tetris game with events handling, figures factory (prototypes used).

### Graphics course on C++ (graphics dir) ###

I've tried to build my own engine with shadows and key-frame animations using object oriented paradigm.
I succeded, but the architecture of the engine has some weak places, so **DO NOT USE IT FOR PRODUCTION**. It has only academic purposes to understand the principle how graphic engines work.

## Python ##

### Optics coursework on 2nd course at Physics Department (sf56-coursework dir) ###

This project was created for simulation of light passing through plate with 2 films and computing the transmission, reflection and absorbtion ratios. Actually, the simulation doesn't work correctly (the simulated and the experiment results are different).

### Optics coursework on 3rd course at Physics Department (ptycho-coursework dir) ###

This project has executable files *generator.py* for building the sequence of low-resolution images and *recoverer.py* for recovery the high-resolution image from sequence of low-res images (see Phourier-Ptychography microscopy). Also it contains some bash scripts to speed up the research of Ptychography methods.
