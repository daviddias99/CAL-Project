# Ridesharing using Graphs

# Repos name

**2017/2018** - 2rd Year, 2nd Semester

**Course:** *Conceção e Análise de Algoritmos* ([CAL](https://sigarra.up.pt/feup/en/UCURR_GERAL.FICHA_UC_VIEW?pv_ocorrencia_id=419999)) | Algorithm Design and Analysis

**Authors:** David Silva ([daviddias99](https://github.com/daviddias99)), Joana Ferreira ([joanaferreira0011](https://github.com/joanaferreira0011 "joanaferreira0011")) and Luís Cunha ([luispcunha](https://github.com/luispcunha))

---

**Description:** This is a group project developed for the course of CAL (analysis and construction of algorithms) at FEUP. It uses a greedy approach to solve the problem of ridesharing (finding a route for a driver while picking up people that are going to the same destination, while taking time constraints into account). 
In the docs folder you may find the full description of the project and it's development (report delivered for evaluation) and the report in paper format (this format does not contain the empirical data nor the sections concerning the implementation of the algorithms).

**Technologies:** C++, graph_viz

**Skills:** Algorithm design, graph algorithms, algorithm specification, Network algorithms

**Grade:** 19.74 / 20

---

## Compilation/Installation

The project has its own make file and is ready to be open and compiled in CLion. 

Be aware that some Linux distributions won't be able to compile this project using the Makefile provided, as they won't recognise the **#ifdef linux** instruction. To solve this, you can either manually delete these instructions or run it on an IDE like Clion, that will recognise them.
If in linux, the line of CMakeLists : "link_libraries(ws2_32 wsock32)" must be commented.

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
* It is not possible to ask for 5 before 1.
* It is not possible to ask for 8 before 1.
* It is not possible to ask for 6 before 4.
* No action is possible before 1
* If person-file for the city already exists, 2 may be skipped. If so, when choosing the driver, the user will be promptd to choose the destination node which must be the same as the destination of the existing person-file.
* If the user executes 2, when executing 4 the program will automatically use the randomly chosen destination of the people as the destination of the driver.
* To avoid unintended behaviour, 8 should not be run after 4,6 or 7, and 7 after 6. Any new runs of the algorithms should also be done by restarting the program.
NOTE: The algorithms were tested mainly on the map of Fafe
## Dependencies
* [GraphViewer](https://paginas.fe.up.pt/~rossetti/rrwiki/doku.php?id=teaching:1011:cal:graphviewer)
