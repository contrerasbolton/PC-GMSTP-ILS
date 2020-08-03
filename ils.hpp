/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; -*- */
#ifndef _ILS_H_
#define _ILS_H_
#include "graph.hpp"

class ILS {
public:
  int iter;
  Graph *g;
  default_random_engine generator;
  uniform_real_distribution<double> randValue;
  map<int, pair<vector <int>, vector <int> > > population;
  // Parameters
  unsigned sizePop;
  double per_pert;
  double per_ls1;
  double per_ls2;
  // Functions
  ILS(int seed, Graph *h);
  ILS(int seed, Graph *h, int sizeE, double per_pert, double per_ls1, double per_ls2);
  virtual ~ILS();
  int rnd(unsigned low, unsigned high);
  void print_sol(vector <int> &solution);
  double LS1(double SolCost, vector <int> &solution, vector <int> &encode_s);
  double LS2(double SolCost, vector <int> &solution, vector <int> &encode_s);
  double LS3(double SolCost, vector <int> &solution, vector <int> &encode_s);
  int initialSolution(int N, vector<int> &solution, vector<int> &encode_s);
  int perturbation(int N, int rangePerturbation, vector<int> &solution, vector<int> &encode_s);
  int solver(std::chrono::time_point<std::chrono::high_resolution_clock> start, double limit);
  int solver2(std::chrono::time_point<std::chrono::high_resolution_clock> start, double limit);
  void updatePop(int cost, vector<int> &solution, vector<int> &encode_s);
};
#endif /* _ILS_H_ */
