# CAL-Project

Ridesharing using graphs.

## Authors

* [David Dias](https://github.com/daviddias99 "daviddias99")
* [Joana Ferreira](https://github.com/joanaferreira0011 "joanaferreira0011")
* [Luís Cunha](https://github.com/luispcunha "luispcunha")

## Compilation/Installation

The project has its own make file and is ready to be open and compiled in CLion. 
Be aware that some Linux distributions won't be able to compile the project using the Makefile, as they won't recognise the **#ifdef linux** instruction. You can either manually clean these instructions or run it on an IDE like Clion, that will recognise them.

## Usage

CAL-Project has the following menu:

```
1- Choose city
2- Generate people
3- Add people to graph
4- Choose driver info
5- Show whole map
6- Show graph after driver DFS
7- Run Algorithm
8- Check complexity
0- Exit
```

* It is not possible to ask for 7 before 1,2,3 and 4. 
* It is not possible to ask for 5 before 1,2 and 3.
* It is not possible to ask for 8 before 1.

## Dependencies
* [Graphviz - Graph Visualization Software](https://www.graphviz.org/)
