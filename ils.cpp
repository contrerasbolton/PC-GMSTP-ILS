/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; -*- */
#include "ils.hpp"

ILS::ILS(int seed, Graph *h)
{
  g = h;
  generator.seed(seed);
  randValue = uniform_real_distribution<double>(0.0, 1.0);
  sizePop = 20;
  this->per_pert = 0.3;
  this->per_ls1 = 0.6;
  this->per_ls2 = 0.15;
}

ILS::ILS(int seed, Graph *h, int sizeE, double per_pert, double per_ls1, double per_ls2)
{
  g = h;
  generator.seed(seed);
  randValue = uniform_real_distribution<double>(0.0, 1.0);
  sizePop = sizeE;
  this->per_pert = per_pert;
  this->per_ls1 = per_ls1;
  this->per_ls2 = per_ls2;
  //cout << sizePop << " " << per_pert << " " << per_ls1 << " " << per_ls2 << endl;
}

ILS::~ILS()
{
  // delete g;
}

int ILS::rnd(unsigned low, unsigned high)
{
  return low + generator() % ((high + 1) - low);
}

void ILS::print_sol(vector <int> &solution)
{
  for(unsigned i = 0; i < solution.size(); i++)
    cout << solution[i] << " ";
  cout << endl;
}

double ILS::LS1(double SolCost, vector <int> &solution, vector <int> &encode_s)
{
  vector<int> random = encode_s;
  // int rand = rnd(0, 9);
  // if(rand % 3 != 0)
  shuffle(random.begin(), random.end(), generator);

  float actual = SolCost, nuevo;
  for(unsigned i = 0; i < random.size(); i++)
    {
      int temp = encode_s[i];
      shuffle(g->index_random[i].begin(), g->index_random[i].end(), generator);
      for(unsigned t = 0; t < g->cluster[i].size(); t++)
        {
          int j = g->index_random[i][t];
          int templocal = solution[i];
          int posTemp = encode_s[i];
          if(temp != j)
            {
              solution[i] = g->cluster[i][j];
              encode_s[i] = j;

              nuevo = g->kruskal(solution);
              if(actual > nuevo)
                return nuevo;
              else // to undo last change
                {
                  solution[i] = templocal;
                  encode_s[i] = posTemp;
                }
            }
        }
    }
  return actual;
}

double ILS::LS2(double SolCost, vector <int> &solution, vector <int> &encode_s)
{
  vector<int> random = encode_s;
  // int rand = rnd(0, 9);
  // if(rand % 3 != 0)
  shuffle(random.begin(), random.end(), generator);

  float actual = SolCost, nuevo;
  for(unsigned i = 0; i < random.size(); i++)
    {
      int temp = encode_s[i];
      shuffle(g->index_random[i].begin(), g->index_random[i].end(), generator);
      for(unsigned t = 0; t < g->cluster[i].size(); t++)
        {
          int j = g->index_random[i][t];
          int templocal = solution[i];
          int posTemp = encode_s[i];
          if(temp != j)
            {
              solution[i] = g->cluster[i][j];
              encode_s[i] = j;

              nuevo = g->kruskal(solution);
              if(actual > nuevo)
                {
                  actual = nuevo;
                  break;
                }
              else // to undo last change
                {
                  solution[i] = templocal;
                  encode_s[i] = posTemp;
                }
            }
        }
    }
  return actual;
}

double ILS::LS3(double SolCost, vector <int> &solution, vector <int> &encode_s)
{
  vector<int> random = encode_s;
  // int rand = rnd(0, 9);
  // if(rand % 3 != 0)
  shuffle(random.begin(), random.end(), generator);

  float actual = SolCost, nuevo;
  for(unsigned i = 0; i < random.size(); i++)
    {
      int temp = encode_s[i];
      shuffle(g->index_random[i].begin(), g->index_random[i].end(), generator);
      for(unsigned t = 0; t < g->cluster[i].size(); t++)
        {
          int j = g->index_random[i][t];
          int templocal = solution[i];
          int posTemp = encode_s[i];
          if(temp != j)
            {
              solution[i] = g->cluster[i][j];
              encode_s[i] = j;

              nuevo = g->kruskal(solution);
              if(actual > nuevo)
                actual = nuevo;
              else // to undo last change
                {
                  solution[i] = templocal;
                  encode_s[i] = posTemp;
                }
            }
        }
    }
  return actual;
}

// Initial Solution
int ILS::initialSolution(int N, vector<int> &solution, vector<int> &encode_s)
{
  for(auto i = 0; i < N; i++)
    {
      int pos = rnd(0, N - 1) % g->cluster[i].size();
      encode_s[i] = pos;
      solution[i] = g->cluster[i][pos];
    }
  return g->kruskal(solution);
}

// Perturbation
int ILS::perturbation(int N, int rangePerturbation, vector<int> &solution, vector<int> &encode_s)
{
  int position = 0;
  double numberPerturbation = rnd(0, rangePerturbation);
  vector<bool> done(N, false);
  for(int count = 0; count < numberPerturbation; count++)
    {
      do {
        position = rnd(0, N - 1);
      }
      while(done[position]);
      done[position] = true;
      int newValue = rnd(0, g->cluster[position].size() - 1);
      encode_s[position] = newValue;
      solution[position] = g->cluster[position][newValue];
    }
  // print_sol(solution);
  return g->kruskal(solution);
}

int ILS::solver(std::chrono::time_point<std::chrono::high_resolution_clock> start, double limit)
{
  int N = g->cluster.size();
  double currentCost;
  double bestCost = 99999999;
  vector <int> solution(N, 0); // solution, each position is a vertex of k-th cluster
  vector <int> encode_s(N, 0);
  vector <int> solutionBest;
  vector <int> encode_sBest;

  double bestbestCost = 99999999;
  vector <int> solutionBestBest;
  vector <int> encode_sBestBest;

  currentCost = initialSolution(N, solution, encode_s);
  // currentCost = LS3(currentCost, solution, encode_s);

  int iterMax = 100000;
  int history = 0;
  auto end = chrono::high_resolution_clock::now();
  limit*= 1e9;
  for(auto iteration = 1; iteration <= iterMax; iteration++)
    {
      // Calculating total time taken by the program.
      auto timeRun = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
      if(timeRun >= limit)
        break;
      // cout << "Iteration " << iteration << endl;

      // Perturbation
      if(randValue(generator) > per_pert) //.15 best .3
        currentCost = perturbation(N, N, solution, encode_s);
      else
        currentCost = perturbation(N, N * 0.1, solution, encode_s);

      if(randValue(generator) > 0.85 && solutionBest.size() > 0)
        {
          currentCost = bestCost;
          solution = solutionBest;
          encode_s = encode_sBest;
        }
      // Local Search
      double rate = randValue(generator);
      if(rate > per_ls1)
        currentCost = LS1(currentCost, solution, encode_s);
      else if(rate > per_ls2)
        currentCost = LS2(currentCost, solution, encode_s);
      else
        currentCost = LS3(currentCost, solution, encode_s);

      if(bestCost > currentCost)
        {
          currentCost = LS3(currentCost, solution, encode_s);
          // cout << "current Cost 3 " << currentCost << endl;

          bestCost = currentCost;
          solutionBest = solution;
          encode_sBest = encode_s;
          iter = iteration;
        }
      else
        history++;
      // history
      if(history == 200)
        {
          currentCost = bestCost;
          solution = solutionBest;
          encode_s = encode_sBest;

          history = 0;
          // currentCost = LS3(currentCost, solution, encode_s);
        }
      // reset
      if(iteration % 1000 == 0)
        {
          //Initial Solution
          currentCost = initialSolution(N, solution, encode_s);
          // cout << bestCost << endl;
          // save best best solution
          if(bestbestCost > bestCost) // case if there are several resets, save the best
            {
              bestbestCost = bestCost;
              solutionBestBest = solutionBest;
              encode_sBestBest = encode_sBest;
            }
          // reset solution
          bestCost = currentCost;
          solutionBest = solution;
          encode_sBest = encode_s;

          // currentCost = bestCost;
          // solution = solutionBest;
          // encode_s = encode_sBest;
        }
      end = chrono::high_resolution_clock::now();
    }
  // cout << "best Cost " << bestCost << endl;
  if(solutionBestBest.size())
    {
      if(bestCost < bestbestCost)
        return bestCost;
      else
        return bestbestCost;
    }
  return bestCost;
}

void ILS::updatePop(int cost, vector<int> &solution, vector<int> &encode_s)
{
  if(population.size() > 0)
    {
      map<int, pair<vector <int>, vector <int> > >::iterator rit = --population.end();
      // cout << sizePop << endl;
      // for (rit=population.rbegin(); rit!=population.rend(); ++rit)
      // if(population.size() > 0)
      // 	{
      // std::cout << rit->first << " => " << (rit->second).first.size() << '\n';
      // map<int, pair<vector <int>, vector <int> > >::iterator it = population.begin();
      // std::cout << it->first << " => " << (it->second).first.size() << '\n';
      // cout << endl;
      // }
      // for(map<int, pair<vector <int>, vector <int> > >::iterator it = population.begin(); it != population.end(); ++it)
      //   {
      //     cout << it->first << " ";
      //   }
      // cout << endl;

      if(population.size() < sizePop || rit->first > cost)
        {
          if(population.find(cost) == population.end())
            {
              population.insert(make_pair(cost, pair<vector<int>, vector<int> >(solution, encode_s)));
              // cout << population.size() << endl;
              while(population.size() > sizePop)
                {
                  population.erase(--population.end());
                }
            }
        }

      // cout << population.size() << endl;
    }
  else
    population.insert(make_pair(cost, pair<vector<int>, vector<int> >(solution, encode_s)));
}

// version used to run the final experiments
int ILS::solver2(std::chrono::time_point<std::chrono::high_resolution_clock> start, double limit)
{
  int N = g->cluster.size();
  double currentCost;
  double bestCost = 99999999;
  vector <int> solution(N, 0); // solution, each position is a vertex of k-th cluster
  vector <int> encode_s(N, 0);
  vector <int> solutionBest;
  vector <int> encode_sBest;

  double bestbestCost = 99999999;
  vector <int> solutionBestBest;
  vector <int> encode_sBestBest;

  // update current and best solution
  bestCost = currentCost = initialSolution(N, solution, encode_s);
  solutionBest = solution;
  encode_sBest = encode_s;
  updatePop(currentCost, solution, encode_s);

  // currentCost = LS3(currentCost, solution, encode_s);
  //to generate plots
  //ofstream out("iterations.txt");
  //out << 0 << " " << currentCost << " " << 0 << endl;
  //out.close();

  int iterMax = 500000;
  int history = 0;
  auto end = chrono::high_resolution_clock::now();
  limit*= 1e9;
  for(auto iteration = 1; iteration <= iterMax; iteration++)
    {
      // Calculating total time taken by the program.
      auto timeRun = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

      if(timeRun >= limit)
        break;
      // cout << "Iteration " << iteration << endl;

      // Perturbation
      if(randValue(generator) > per_pert) //.15 best .3
        {
          currentCost = perturbation(N, N, solution, encode_s);
          // else
          // 	currentCost = perturbation(N, N * 0.1, solution, encode_s);
          updatePop(currentCost, solution, encode_s);

          //out.open("iterations.txt", ios::app);
          //out << iteration << " " << currentCost << " " << 0 << endl;
          //out.close();
        }
      else if(solutionBest.size() && population.size())// && randValue(generator) < 0.9)
        {
          // currentCost = bestCost;
          // solution = solutionBest;
          // encode_s = encode_sBest;
          map<int, pair<vector <int>, vector <int> > >::iterator it = population.begin();
          int position = rnd(0, population.size() - 1);
          // cout << "rnd " << position << endl;
          advance(it, position);
          currentCost = it->first;
          solution = (it->second).first;
          encode_s = (it->second).second;

          currentCost = perturbation(N, N * 0.1, solution, encode_s);
          updatePop(currentCost, solution, encode_s);

          //out.open("iterations.txt", ios::app);
          //out << iteration << " " << currentCost << " " << 1 << endl;
          //out.close();
        }

      // Local Search
      double rate = randValue(generator);
      if(rate > per_ls1)
        currentCost = LS1(currentCost, solution, encode_s);
      else if(rate > per_ls2)
        currentCost = LS2(currentCost, solution, encode_s);
      else
        currentCost = LS3(currentCost, solution, encode_s);

      updatePop(currentCost, solution, encode_s);

      //out.open("iterations.txt", ios::app);
      //out << iteration << " " << currentCost << " " << 2 << endl;
      //out.close();

      if(bestCost > currentCost)
        {
          //cout << "best " << currentCost << endl;
          currentCost = LS3(currentCost, solution, encode_s);
          updatePop(currentCost, solution, encode_s);
          //cout << "best " << currentCost << endl;

          bestCost = currentCost;
          solutionBest = solution;
          encode_sBest = encode_s;
          iter = iteration;
          //to generate plots
          //out.open("iterations.txt", ios::app);
          //out << iteration << " " << currentCost << " " << 3 << endl;
          //out.close();
        }
      else
        history++;
      // history
      if(history == 100)
        {
          //currentCost = bestCost;
          //solution = solutionBest;
          //encode_s = encode_sBest;
          map<int, pair<vector <int>, vector <int> > >::iterator it = population.begin();
          int position = rnd(0, population.size() - 1);
          // cout << "rnd " << position << endl;
          advance(it, position);
          currentCost = it->first;
          solution = (it->second).first;
          encode_s = (it->second).second;

          history = 0;
          currentCost = LS2(currentCost, solution, encode_s);
          updatePop(currentCost, solution, encode_s);
          if(bestCost > currentCost)
            {
              // cout << "it best " << currentCost << endl;
              bestCost = currentCost;
              solutionBest = solution;
              encode_sBest = encode_s;
              //updatePop(currentCost, solution, encode_s);
            }
          //to generate plots
          //out.open("iterations.txt", ios::app);
          //out << iteration << " " << currentCost << " " << 4 << endl;
          //out.close();
        }

      // reset
      if(iteration % 1000 == 0)
        {
          map<int, pair<vector <int>, vector <int> > > pop(population);
          //map<int, pair<vector <int>, vector <int> > >::iterator rit = --population.end();
          for(map<int, pair<vector <int>, vector <int> > >::iterator it = pop.begin(); it != pop.end(); ++it)
            {
              map<int, pair<vector <int>, vector <int> > >::iterator rit = --population.end();
              currentCost = it->first;
              solution = (it->second).first;
              encode_s = (it->second).second;
              currentCost = LS3(currentCost, solution, encode_s);
              // cout << it->first << " " ;
              if(bestCost > currentCost)
                {
                  // cout << "it best " << currentCost << endl;
                  bestCost = currentCost;
                  solutionBest = solution;
                  encode_sBest = encode_s;
                  iter = iteration;
                  updatePop(currentCost, solution, encode_s);
                  //out.open("iterations.txt", ios::app);
                  //out << iteration << " " << currentCost << " " << 5 << endl;
                  //out.close();
                }
              else if(rit->first > currentCost)
                {
                  updatePop(currentCost, solution, encode_s);
                }

            }
          // cout << endl;
          //Initial Solution
          currentCost = initialSolution(N, solution, encode_s);
          updatePop(currentCost, solution, encode_s);

          // cout << bestCost << endl;
          // save best best solution
          if(bestbestCost > bestCost) // case if there are several resets, save the best
            {
              bestbestCost = bestCost;
              solutionBestBest = solutionBest;
              encode_sBestBest = encode_sBest;
            }
          // reset solution
          bestCost = currentCost;
          solutionBest = solution;
          encode_sBest = encode_s;

          // currentCost = bestCost;
          // solution = solutionBest;
          // encode_s = encode_sBest;
        }
      end = chrono::high_resolution_clock::now();
    }

  // cout << "best Cost " << bestCost << endl;
  if(solutionBestBest.size())
    {
      if(bestCost < bestbestCost)
        {
          //cout << solutionBest.size() << endl;
          //g->printSolution(solutionBest);//to generate plots
          return bestCost;
        }
      else
        {
          //cout << solutionBestBest.size() << endl;
          //g->printSolution(solutionBestBest); //to generate plots
          return bestbestCost;
        }
    }
  // cout << solutionBest.size() << endl;
  //g->printSolution(solutionBest);//to generate plots
  return bestCost;
}
