# PC-GMSTP-ILS
## Prize-collecting Generalized Minimum Spanning Tree Problem
This code was written in the paper ``An effective two-level solution approach for the prize-collecting generalized minimum spanning tree problem by iterated local search'' by Carlos Contreras-Bolton and Víctor Parada.

The instances are in the directory `instances`. The instances are in groups in the directory `in`.

## Instructions to run

To build the binary type:
```
make
```
To run the program:

```
./execute22.sh InstancesSet

```
where InstancesSet is:

```
g1 : instances proposed in Marzo and Ribeiro (2020)
cc : instances with the clustering centering group
u3: instances with u=3
u5: instances with u=5
u7: instances with u=7
u9: instances with u=9
```

Give an example

```
/execute22.sh g1
```

## License
The program is distributed under the GNU General Public License, version 3.
See the `LICENSE` file.
