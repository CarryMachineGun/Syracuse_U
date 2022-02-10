/*
HW1 by Yuchen Wang
SU Net ID: ywang249  SUID: 905508464
HW1: Due: 11:59pm, Wed., Feb. 9.
Using 4 threads (T1, T2, T3, and main) to perform parallel processing for the Floyd-Warshall
All-Pair Shortest Path Algorithm.

You need to first perform a dependency analysis at the beginning of your submitted code to justify your implementation.
Without correctly doing this, you will not receive credits even if your program generates correct results.

//Your analysis

THE TRUTH IS THIS ALGORITHM CAN NOT BE FULLY PROCESSED IN PARALLEL!!!!!!!! LOCKS ARE NECESSARY!!!!!

Because dependencied can not be fully eliminated.
Therefore, my program doesn't guarantee corrent answer when it run in parallel.

1. Why not k

Based on the transmission formula shortPath(i, j, k) = min(shortPath(i, j, k-1), shortPath(i, k, k-1) +  shortPath(k, j, k-1))
The value of Dis(i, j, k) is based on the result of last round Dis(i, j, k-1), thus can not be done in parallel without using locks

2. Why not i and j

Also based on the transmission formula shortPath(i, j, k) = min(shortPath(i, j, k-1), shortPath(i, k, k-1) +  shortPath(k, j, k-1))
So, Dist[i][j] = min(Dis[i][j], Dist[i][k] + Dist[k][j])
That means for a particular k, j, Dist[k][j] is needed by all the column elements of j.
It also means for a particular k, j, Dist[i][k] is needed by all the row elements of i.
Hence it can not be done in parallel without using lock


You can discuss with other people regrading the original Floyd Warshall algorithm.
However, you are not allowed to discuss with other people on the threaded implementation
and the data dependency analysis.

*/
#include <iostream>
#include <vector>
#include <thread>
#include <list>
#include <fstream>

using namespace std;

void FW(vector<vector<int>> &Dist, vector<vector<int>> &Next, int u_start, int u_end, int nodes)
{
	for (int k = 0; k < nodes; k++)
	{
		for (int i = u_start; i < u_end; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				if(Dist[i][j] > Dist[i][k] + Dist[k][j])
				{
					Dist[i][j] = Dist[i][k] + Dist[k][j];
					Next[i][j] = Next[i][k];
				}
			}
		}
	}

	return;
}

int main()
{
	// Read in number of nodes and number of edges
	ifstream In("graph.txt");
	int Nodes, Edges;
	In >> Nodes >> Edges;
	int a, b, c;

	vector<list<pair<int, int>>> Graph(Nodes); // read in from graph.txt

	// In >> a >> b >> c; do this within a loop

	for (int i = 0; i < Edges; i++)
	{
		In >> a >> b >> c;
		Graph[a].push_back({b, c});
	}

	In.close();

	vector<vector<int>> Dist(Nodes, vector<int>(Nodes, 9999));
	vector<vector<int>> Next(Nodes, vector<int>(Nodes, -1));
	// YOu need to initialize diagonal values in Dist and Next

	for (int i = 0; i < Nodes; i++)
	{
		Dist[i][i] = 0;
		Next[i][i] = i;
	}

	// Need to read in graph anc construct initial Dist and Next matrices

	for (int i = 0; i < Nodes; i++)
	{
		for (pair<int, int> &j : Graph[i])
		{
			Dist[i][j.first] = j.second;
			Next[i][j.first] = j.first;
		}
	}

	// Implement threaded programming

	thread T1{FW, ref(Dist), ref(Next), 0, Nodes/4, Nodes};
	thread T2{FW, ref(Dist), ref(Next), Nodes/4, Nodes/2, Nodes};
	thread T3{FW, ref(Dist), ref(Next), Nodes/2, Nodes/4*3, Nodes};
	FW(Dist, Next, Nodes - Nodes/4, Nodes, Nodes);
	T1.join();
	T2.join();
	T3.join();

	// Print results
	cout << "Dist Matrix" << endl;
	for (auto &i : Dist)
	{
		for (auto &j : i)
		{
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Next Matrix" << endl;

	for (auto &i : Next)
	{
		for (auto &j : i)
		{
			cout << j << " ";
		}
		cout << endl;
	}

	return 0;
}

/*
Input file:  graph.txt

	Sample input file

	6 //# of nodes in graph
	12 //# of edges in graph
	0 5 16//an edge from node 0 to node 5 with a weight (cost) of 16
	0 4 15
	0 2 4
	0 3 12
	0 1 9
	1 3 3
	1 5 2
	2 3 14
	2 1 3
	3 4 4
	4 5 1
	5 3 2


	Note that it is possible that there are multiple edges from
	a node to another with either identical or different cost.


	Sample output for the above graph.

Dist Matrix

0 9999 8 9999 11 9 7
9999 0 6 8 9 9999
....





Next Matrix
0 -1 3 -1 2 3
-1 1 2 4 3 -1
...




*/
