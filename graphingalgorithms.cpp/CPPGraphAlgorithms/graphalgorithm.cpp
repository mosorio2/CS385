/*******************************************************************************
 * Name        : graphalgorithm.cpp
 * Author      : Brian S. Borowski
 * Version     : 1.0
 * Date        : September 27, 2014
 * Description : Class that implements standard graph traversal algorithms.
 ******************************************************************************/
#include "graphalgorithm.h"
#include "graph.h"
#include "weightedgraph.h"
#include "vertex.h"
#include "minheap.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <climits>
#include <stdexcept>

using namespace std;


static void depth_first_search_visit(
        vertex_id vertex,
        const Graph * const graph,
        bool *visited,
        vector<vertex_id> &order);
/*
static void breadth_first_search_visit(
        vertex_id vertex,
        const Graph * const graph,
        bool *visited,
        vector<vertex_id> &order);
*/
vector<vertex_id> breadth_first_search(const Graph * const graph) {
	vector<vertex_id> v;
	return v;
    // TODO
}
/*
static void breadth_first_search_visit(
        vertex_id vertex, const Graph * const graph, bool *visited,
        vector<vertex_id> &order) {
    // TODO
}
*/
vector<vertex_id> depth_first_search(const Graph * const graph) {
	vector<vertex_id> order, vertices = graph->get_vertices();
	size_t num_vertices = static_cast<size_t>(graph->get_highest_vertex_id());
	order.reserve(num_vertices);
	bool *visited = new bool[num_vertices+1];
	fill(visited, visited + num_vertices + 1, false);
	for (vector<vertex_id>::iterator it = vertices.begin(); it != vertices.end(); ++it)
	{
		if(!visited[*it])
		{
			depth_first_search_visit(*it, graph, visited, order);
		}
	}

	delete [] visited;
	return order;

    // TODO
}

static void depth_first_search_visit(
        vertex_id vertex, const Graph * const graph, bool *visited,
        vector<vertex_id> &order) {
    visited[vertex] = true;
    order.push_back(vertex);
    vector<vertex_id> adjacent = graph->get_adjacent(vertex);
    for(vector<vertex_id> :: iterator it = adjacent.begin();
    		it!= adjacent.end(); ++it){
    	if (!visited[*it]){
    		depth_first_search_visit(*it, graph, visited, order);
    	}
    }
}


vector<vertex_id> top_sort(const Graph * const graph) {
	vector<vertex_id> order, vertices = graph->get_vertices();
	size_t num_vertices = static_cast<size_t>(graph->get_highest_vertex_id());
	order.reserve(num_vertices);
	int *in_degrees = new int[num_vertices + 1];
	fill(in_degrees, in_degrees + num_vertices + 1, -1);

	for (vector<vertex_id>::iterator it = vertices.begin();
			it != vertices.end(); ++it){
		in_degrees[*it] = 0;
	}

	priority_queue< vertex_id, vector<vertex_id>, greater<vertex_id> > zero_indegree_nodes;

	for(size_t i = 1; i<=num_vertices; ++i)
	{
		vector<vertex_id> adjacent = graph->get_adjacent(i);
		for (vector<vertex_id>::iterator it = adjacent.begin();
				it!= adjacent.end(); ++it){
			++in_degrees[*it];
		}
	}

	for (size_t i = 1; i <= num_vertices; ++i)
	{
		if (in_degrees[i] == 0)
		{
			zero_indegree_nodes.push(i);
		}
	}

	while (!zero_indegree_nodes.empty())
	{
		vertex_id n = zero_indegree_nodes.top();
		zero_indegree_nodes.pop();
		order.push_back(n);
		vector<vertex_id> adjacent = graph->get_adjacent(n);
		for (vector<vertex_id>::iterator it = adjacent.begin(); it != adjacent.end(); ++it)
		{
			--in_degrees[*it];
			if (in_degrees[*it] == 0)
			{
				zero_indegree_nodes.push(*it);
			}
		}
	}

	for (size_t i =1; i <= num_vertices; ++i)
	{
		if (in_degrees[i] > 0)
		{
			order.clear();
			break;
		}
	}

	delete [] in_degrees;
	return order;
}

pair<uint_t, string> shortest_path(
        vertex_id src, vertex_id dst, const WeightedGraph * const graph) {
    pair<uint_t, string> result;
    return result;
}

