/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; -*- */
#include "ils.hpp"
// #include "Grafo.hpp"
int n; // number of vertices
int m; // number of clusters
int edges;
Graph *g;
vector< pair<string, int> > instances;

int dist(int i, int j)
{
  int xd = g->coord[i].first - g->coord[j].first;
  int yd = g->coord[i].second - g->coord[j].second;
  return (int) (sqrt(xd * xd + yd * yd) + 0.5);
}

void read(string instance)
{
  FILE *file;
  int temp, size, x, y;

  if((file = fopen(instance.c_str(), "r")) == NULL)
    cout << "Error to read instance: " << instance << endl;
  // read n
  if(fscanf(file, "%d", &n) == EOF)
    cout << "Error to read number of vertices" << endl;

  g = new Graph(n);
  //coord.reserve(n);
  // coord x
  for(auto i = 0; i < n; i++)
    {
      if(fscanf(file, "%d", &x) == EOF)
        cout << "Error to read coord x" << endl;

      if(fscanf(file, "%d", &y) == EOF)
        cout << "Error to read coord y" << endl;
      // cout << x << " " << y << "\n";
      g->coord.emplace_back(pair<int,int>(x, y));
    }

  // read m
  if(fscanf(file, "%d", &m) == EOF)
    cout << "Error to read number of clusters" << endl;

  // read clusters
  // g->cluster.reserve(m);
  for(auto i = 0; i < m; i++)
    {
      if(fscanf(file, "%d", &size) == EOF)
        cout << "Error to read size of cluster "<< i << endl;
      vector<int> vertex;
      // vertex.reserve(size);
      // cout << size << endl;
      for(auto j = 0; j < size; j++)
        {
          if(fscanf(file, "%d", &temp) == EOF)
            cout << "Error to read vertices of cluster" << endl;
          vertex.emplace_back(temp-1);
        }
      g->cluster.emplace_back(vertex);
      sort(g->cluster[i].begin(), g->cluster[i].end());
    }
  // centers of the clusters [?]
  for(auto i = 0; i < m; i++)
    {
      if(fscanf(file, "%d", &temp) == EOF)
        cout << "Error to read clusters" << endl;
    }

  if(fscanf(file, "%d", &temp) == EOF)
    cout << "Error to read prizes" << endl;

  if(temp == -999)
    {
      for(auto i = 0; i < n; i++)
        {
          if(fscanf(file, "%d", &temp) == EOF)
            cout << "Error to read prizes" << endl;
          g->prize.emplace_back(temp);
        }
      if(fscanf(file, "%d", &temp) == EOF)
        cout << "Error to read prizes" << endl;

      // if(temp == -999)
      //   cout << "Reading successfully" << endl;
      if(temp != -999)
        cout << "cannot read the prizes, second. temp:  " << temp << endl;
    }
  else
    {
      cout << "cannot read the prizes, first. temp:  " << temp << endl;
      exit(0);
    }

  // cout << n << " " << m << endl;

  // g->vertexCluster.reserve(n);
  for(auto i = 0; i < n; i++)
    g->vertexCluster.emplace_back(0);

  for(auto i = 0; i < m; i++)
    {
      g->index_random.emplace_back(vector<int>());
      // cout << i << " ";
      for(unsigned j = 0; j < g->cluster[i].size(); j++)
        {
          // cout << g->cluster[i][j] << " ";
          g->vertexCluster[g->cluster[i][j]] = i;
          g->index_random[i].emplace_back(j);
        }
      // cout << endl;
    }
  // g->cost.reserve(n);
  edges = 0;
  for(auto i = 0; i < n; i++)
    {
      vector<int> temp2;
      // g->cost[i].reserve(n);

      for(auto j = 0; j < n; j++)
        {
          temp2.emplace_back(dist(i, j));
          // cout << temp2[j] << " ";
          if(i < j && g->vertexCluster[i] != g->vertexCluster[j])
            edges++;
        }
      g->cost.emplace_back(temp2);
      // cout << endl;
    }
  // for(auto i = 0; i < n; i++)
  //   {
  //     cout << i << " -> " << g->vertexCluster[i] << endl;
  //   }
  fclose(file);
  g->initialize(m);
  // g->kruskal();
  //for(auto i = 0; i < n; i++)
  //cout << g->coord[i].first << " " << g->coord[i].second << " " << g->vertexCluster[i]  << endl<< endl;
}

void getListInstances(const char path[])
{
  const int SIZE = 255;
  char linea[SIZE + 1] = "";
  string nameInstance;
  ifstream in(path);

  if(!in.good())
    {
      cout << "Error to load the instances file)[" << path << "]..." << endl;
      exit(1);
    }
  while(!in.eof())
    {
      in.getline(linea, SIZE);

      if(linea[0] != '#' && strlen(linea) > 1)
        {
          string cadena(linea);
          pair<string, float> instance(cadena, 0);
          instances.emplace_back(instance);
        }
    }
  // for(unsigned i = 0; i < instances.size(); i++)
  //   cout << instances[i].first << " " << instances[i].second << endl;
  in.close();
}

int main(int argc, char *argv[])
{
  string instance, output;
  double limit = 0, per_pert = 0, per_ls1 = 0, per_ls2 = 0;
  int seed = 0, sizeE = 0;
  if(argc < 5)
    {
      cout << "format to run:" << endl;
      cout << "./pc_gmstp instance.GTP output.txt time seed" << endl;
      return 0;
    }
  else if(argc == 5)
    {
      instance = argv[1];
      output = argv[2];
      limit = atof(argv[3]);
      seed = atoi(argv[4]);
    }
  else if(argc == 9)
    {
      instance = argv[1];
      output = argv[2];
      limit = atof(argv[3]);
      seed = atoi(argv[4]);
      sizeE = atoi(argv[5]);
      per_pert = atof(argv[6]);
      per_ls1 = atof(argv[7]);
      per_ls2 = atof(argv[8]);
    }
  else
    {
      cout << "format to run:" << endl;
      cout << "./pc_gmstp instance.GTP output.txt time seed sizeE %perturbation %ls1 %ls2" << endl;
      return 0;
    }
  if(limit == -1)
    limit = 3600;

  //cout << instance << " " << output << " " << limit << " " << seed << " " << sizeE << " " << per_pert<< " " << per_ls1 << " " << per_ls2 << endl;
  string path = "instances/";
  string ext = ".GTP";
  int cost = 0;
  double timeRun = 0.0;
  // getListInstances(name.c_str());
  read(path + instance);

  ILS *ils;
  if(argc == 5)
    ils = new ILS(seed, g);
  else
    ils = new ILS(seed, g, sizeE, per_pert, per_ls1, per_ls2);
  auto start = chrono::high_resolution_clock::now();
  // unsync the I/O of C and C++.
  ios_base::sync_with_stdio(false);

  // call ILS
  cost = ils->solver2(start, limit);

  auto end = chrono::high_resolution_clock::now();

  // Calculating total time taken by the program.
  timeRun = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  timeRun *= 1e-9;
  cout << "#"<<instance << " " << cost << " " << fixed << timeRun << setprecision(5) << " " << ils->iter << " " << seed << endl;
  //cout << "RunsExecuted = 1" << endl;
  //cout << "CPUTime_Mean = " << timeRun << endl;
  //cout << "BestSolution_Mean = " << cost << endl;
  ofstream out(output.c_str(), ios::app);
  out << instance << " " << cost << " " << n << " " << m << " " << edges << " " << fixed << timeRun << setprecision(5) << " " << ils->iter << " " << seed  << endl;
  out.close();
  delete ils;
  delete g;

  // ofstream out(output.c_str());
  // out.close();
  // unsigned sizeInstances = instances.size();
  // auto num_repeat = 10;
  // ILS *ils;
  // for(unsigned i = 0; i < sizeInstances; i++)
  //   {
  //     cout << instances[i].first << "\n";
  //     out.open(output.c_str(), ios::app);
  //     out << instances[i].first << " ";
  //     out.close();
  //     instance = path + instances[i].first + ext;
  //     // cout << instance << endl;
  //     //read instance
  //     read(instance);
  //     // reduction
  //     double avgCost = 0.0, avgTimeRun = 0.0, maxTimeRun = 0.0;
  //     int bestCost = 9999999;
  //     for(auto j = 0; j < num_repeat; j++)
  //       {
  //         ils = new ILS(j + 1, g);
  //         limit = TL[i]; // temporal

  //         auto start = chrono::high_resolution_clock::now();
  //         // unsync the I/O of C and C++.
  //         ios_base::sync_with_stdio(false);

  //         // call ILS
  //         cost = ils->solver(start, limit);

  //         auto end = chrono::high_resolution_clock::now();

  //         // Calculating total time taken by the program.
  //         timeRun = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  //         timeRun *= 1e-9;
  //         cout << cost << " " << fixed << timeRun << setprecision(5) << " " << ils->iter << endl;
  //         avgTimeRun += timeRun;
  //         avgCost += cost;
  //         if(cost < bestCost)
  //           bestCost = cost;
  //         if(maxTimeRun < timeRun)
  //           maxTimeRun = timeRun;
  //         delete ils;
  //       }
  //     avgTimeRun /= (double) num_repeat;
  //     avgCost /= (double) num_repeat;

  //     cout << bestCost << " " << avgCost << " " << avgTimeRun << " " << maxTimeRun << endl;
  //     out.open(output.c_str(), ios::app);
  //     out << bestCost << " " << avgCost << " " << avgTimeRun << " " << maxTimeRun << endl;
  //     out.close();

  // delete g;
  // }
  return 0;
}
