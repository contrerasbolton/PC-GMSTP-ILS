/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2; -*- */
#include "graph.hpp"

Graph::Graph(int n)
{
  this->n = n;
  coord.reserve(n);
}

Graph::~Graph()
{

}

void Graph::initialize(int k)
{
  this->k = k;
  // cout << "oli " << n << endl;

  // ARISTA a;//arista
  // ARISTA_PONDERADA ap;//arista ponderada
  // //representación del grafo con un vector de aristas
  // ds = DS(n);
  // for(auto i = 0; i < n; i++)
  //   {
  //     for(auto j = i + 1; j < n; j++)
  // 	{
  // 	  if(vertexCluster[i] != vertexCluster[j])
  // 	    {
  // 	      a.first = i;
  // 	      a.second = j;
  // 	      ap.first = cost[i][j];
  // 	      ap.second = a;
  // 	      G.emplace_back(ap);
  // 	    }
  // 	}
  //   }

  // for(unsigned i = 0; i < G.size(); i++)
  //   {
  //     a = G[i].second;
  //     cout << a.first << " " << a.second << " = " << G[i]. first << " -> " << vertexCluster[a.first] << " " << vertexCluster[a.second] << endl;
  //   }
}

//algoritmo de kruskal
void Graph::kruskal()
{
  vector<ARISTA_PONDERADA> G; //Grafo
  vector<ARISTA_PONDERADA> S; // Solución
  ARISTA a;
  int u, v, w;//vertices
  vector<int> rank (n);
  vector<int> parent (n);
  boost::disjoint_sets<int*,int*> ds(&rank[0], &parent[0]);

  for(v = 0; v < n; v++)
    ds.make_set(v);
  sort(G.begin(), G.end());
  for(unsigned i = 0; i < G.size(); i++)
    {
      a = G[i].second;
      u = a.first;
      v = a.second;
      if(ds.find_set(u) != ds.find_set(v))
        {
          S.emplace_back(pair<int, ARISTA>(G[i].first, a));
          ds.union_set(u,v);
        }
    }

  ARISTA_PONDERADA ap;//arista ponderada
  //se imprimen salida
  for(unsigned i = 0; i < S.size(); i++)
    {
      ap = S[i];
      a = ap.second;
      u = a.first;
      v = a.second;
      w = ap.first;
      printf("(%d, %d, %d)\n", u, v, w);
    }
}

double Graph::kruskal(vector<int> &solution)
{
  vector<ARISTA_PONDERADA> G; //Grafo
  vector<ARISTA_PONDERADA> S; // Solución
  ARISTA_PONDERADA ap;//arista ponderada
  int u, v;//vertices
  int N = solution.size();
  ARISTA arc;
  vector<int> fake(n, 0);
  // DS ds = DS(N);
  double prizes = 0;
  vector<int> rank (N);
  vector<int> parent (N);
  boost::disjoint_sets<int*,int*> ds(&rank[0], &parent[0]);

  //representación del grafo con un vector de aristas
  for(auto i = 0; i < N; i++)
    {
      u = solution[i];
      prizes += prize[u];
      // cout << u << " p - > " << prize[u] << endl;
      fake[u] = i;
      ds.make_set(i);
      for(auto j = i + 1; j < N; j++)
        {
          v = solution[j];
          if(vertexCluster[u] != vertexCluster[v])
            {
              arc.first = u;
              arc.second = v;
              ap.first = cost[u][v];
              ap.second = arc;
              G.emplace_back(ap);
              // cout << u << ", " << v << " = ";
              // cout << cost[u][v] << endl;
            }
        }
    }

  // for(v = 0; v < N; v++)
  //  ds.make_set(v);

  sort(G.begin(), G.end());

  double cost = 0;
  for(unsigned i = 0; i < G.size(); i++)
    {
      arc = G[i].second;
      u = arc.first;
      v = arc.second;
      if(ds.find_set(fake[u]) != ds.find_set(fake[v]))
        {
          // cout << u << ", " << v << " " << G[i].first << endl;
          S.emplace_back(pair<int, ARISTA>(G[i].first, arc));
          ds.union_set(fake[u], fake[v]);
          cost += G[i].first;
        }
    }

  // ARISTA_PONDERADA ap;//arista ponderada
  //se imprimen salida
  // printf("arbol resultante\n");
  // for(unsigned i = 0; i < S.size(); i++)
  //   {
  //     ap = S [i];
  //     arc = ap.second;
  //     // u = arc.first;
  //     // v = arc.second;
  //     // w = ap.first;
  //     printf("(%d, %d, %d)\n", arc.first, arc.second, ap.first);
  //   }
  // cout << "Cost is " << cost << endl;
  // cout << "Prizes is " << prizes << endl;
  // exit(0);
  // if(S.size() != N - 1)
  //   {
  //     cout << S.size() << " " << N << endl;
  //     getchar();
  //     return 999999;
  //   }
  // delete ds;
  return cost - prizes;
}

double Graph::printSolution(vector<int> &solution)
{
  vector<ARISTA_PONDERADA> G; //Grafo
  vector<ARISTA_PONDERADA> S; // Solución
  ARISTA_PONDERADA ap;//arista ponderada
  int u, v;//vertices
  int N = solution.size();
  ARISTA arc;
  vector<int> fake(n, 0);
  // DS ds = DS(N);
  double prizes = 0;
  vector<int> rank (N);
  vector<int> parent (N);
  boost::disjoint_sets<int*,int*> ds(&rank[0], &parent[0]);

  //representación del grafo con un vector de aristas
  for(auto i = 0; i < N; i++)
    {
      u = solution[i];
      prizes += prize[u];
      // cout << u << " p - > " << prize[u] << endl;
      fake[u] = i;
      ds.make_set(i);
      for(auto j = i + 1; j < N; j++)
        {
          v = solution[j];
          if(vertexCluster[u] != vertexCluster[v])
            {
              arc.first = u;
              arc.second = v;
              ap.first = cost[u][v];
              ap.second = arc;
              G.emplace_back(ap);
              // cout << u << ", " << v << " = ";
              // cout << cost[u][v] << endl;
            }
        }
    }

  // for(v = 0; v < N; v++)
  //  ds.make_set(v);

  sort(G.begin(), G.end());

  //cout << "solution" << endl;
  double cost = 0;
  int count = 0;
  //for(unsigned i = 0; i < G.size(); i++)
  for(unsigned i = 0; count < N-1; i++)
    {
      arc = G[i].second;
      u = arc.first;
      v = arc.second;
      if(ds.find_set(fake[u]) != ds.find_set(fake[v]))
        {
          // cout << u << ", " << v << " " << G[i].first << endl;
          //cout << coord[u].first << " " << coord[u].second << " " << 1 << endl;
          //cout << coord[v].first << " " << coord[v].second << " " << 1 << endl << endl;
          S.emplace_back(pair<int, ARISTA>(G[i].first, arc));
          ds.union_set(fake[u], fake[v]);
          cost += G[i].first;
          count++;
        }

    }

  // ARISTA_PONDERADA ap;//arista ponderada
  //se imprimen salida
  // printf("arbol resultante\n");
  // for(unsigned i = 0; i < S.size(); i++)
  //   {
  //     ap = S [i];
  //     arc = ap.second;
  //     // u = arc.first;
  //     // v = arc.second;
  //     // w = ap.first;
  //     printf("(%d, %d, %d)\n", arc.first, arc.second, ap.first);
  //   }
  // cout << "Cost is " << cost << endl;
  // cout << "Prizes is " << prizes << endl;
  // exit(0);
  // if(S.size() != N - 1)
  //   {
  //     cout << S.size() << " " << N << endl;
  //     getchar();
  //     return 999999;
  //   }
  // delete ds;
  return cost - prizes;
}
