Test instances for the Prize-Collecting Generalized Minimum Spanning Tree Problem.

The instances have the form mXXXXn, where m is the number of clusters, n is the number of nodes and XXXXn is the name of the problem in TSPLIB (REINELT, 1991).
We modified the instances for the GMST problem, provided by the authors Paolo Toth and Albert Einstein F. Muritiba. We added a value of prize, pseudo-randomly generated in the range [0, 10], for every node in the previous instances. We also provide the best known solution of each instance for the PC-GMST problem in a separate file.

Reading a GTP file:
---------------------

First data is the number of nodes, n.
The 2n other lines give the x and y coordinates of each node.
A data gives the number of clusters, m.
The following is reapeated m times:
	the number of nodes in the first cluster, m1.
	the node number of the m1 nodes.
	the number of nodes in the first cluster, m2.
	the node number of the m2 nodes.
	....
m numbers of nodes (possibly the centers of the clusters).
A validating number set to -999.
n prize values in the range [0, 10], one for each node.
A validating number set to -999.
Euclidean distance (REINELT, 1991):
---------------------
Let x[i] and y[i] be the coordinates of node i. The distance between two points i and j must be computed as follows:
xd = x[i] - x[j];
yd = y[i] - y[j];
dij = (int) ( sqrt( xd*xd + yd*yd ) + 0.5 );
where sqrt is the C square root function.

Reference:
-----------
REINELT, G. TSPLIB-- A Traveling Salesman Problem Library. ORSA Journal on Computing, v. 3, n. 4, p. 376, 1991.
