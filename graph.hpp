/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; -*- */
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <random>
#include <bits/stdc++.h>
#include <chrono>
#include <boost/pending/disjoint_sets.hpp>

#define ARISTA pair<int, int>
#define ARISTA_PONDERADA pair<int, ARISTA>
#define Infinite 9999999.9
using namespace std;

class Graph {
public:
  int n; // vertices number
  int m; // edges number
  int k; // clusters number
  vector<pair<int, int> > coord; // coordenates of edges (x, y)
  vector<vector<int> > cluster; // cluster id with its vertices
  vector<int> vertexCluster; // vertex i belongs to id cluster
  vector<int> prize; // vertex i belongs to id cluster
  vector<vector<int> > cost; // cost matrix
  vector<vector<int> > index_random;
  // vector <int> solution; // solution, each position is a vertex of k-th cluster
  // for kruskal
  Graph(int n);
  virtual ~Graph();
  void initialize(int k);
  void kruskal();
  double kruskal(vector <int> &solution);
  double printSolution(vector<int> &solution);
};
#endif /* _GRAPH_H_ */
