/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
void setVisited(Graph &graph);

bool sortEdges(Edge one, Edge two);

bool sortEdges(Edge one, Edge two) 
{
	bool retVal = true;
	if (one.getWeight() >= two.getWeight())
		retVal = false;
	return retVal;
}


void setVisited(Graph &graph)
{
	Vertex startPoint = graph.getStartingVertex();
	queue<Vertex> q;
	graph.setVertexLabel(startPoint,"UNEXPLORED");
	q.push(startPoint);
	while(q.empty() == false)
	{
		Vertex currentVertex = q.front();
		vector <Vertex> adjacent = graph.getAdjacent(currentVertex);
		q.pop();
		size_t x = 0; 
	while (x < adjacent.size())
		{
		if (graph.getVertexLabel(adjacent[x]).compare("UNEXPLORED") != 0)
		   	{
					graph.setEdgeLabel(currentVertex,adjacent[x], "UNEXPLORED");
					graph.setVertexLabel(adjacent[x], "UNEXPLORED");
					q.push(adjacent[x]);
			}
					
		if (graph.getEdgeLabel(currentVertex,adjacent[x]).compare("UNEXPLORED")!= 0)
					graph.setEdgeLabel(currentVertex,adjacent[x],"UNEXPLORED");	
		
		 
		x++;
		}
	}
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do adjacent[x] traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
	//TODO: YOUR CODE HERE

	setVisited(graph);
	
	Vertex startPoint = graph.getStartingVertex();
	
	vector<Vertex> adjacent = graph.getAdjacent(startPoint);

	int minWeightVal = graph.getEdgeWeight(startPoint, adjacent[0]);
	queue<Vertex> q;
	Vertex minVertex, minWeight;

	graph.setVertexLabel(startPoint, "VISITED");
	q.push(startPoint);
	while(q.empty() == false)
	{
		Vertex currentVertex = q.front();
		vector<Vertex> adjacent = graph.getAdjacent(currentVertex);
		q.pop();
		int x = 0;
		while ((size_t)x < adjacent.size())
		{
			
			if (graph.getVertexLabel(adjacent[x]).compare("UNEXPLORED") == 0)
			{
				graph.setEdgeLabel(currentVertex, adjacent[x], "DISCOVERY");
				graph.setVertexLabel(adjacent[x], "VISITED");
				q.push(adjacent[x]);
			} 
			else if (graph.getEdgeLabel(currentVertex, adjacent[x]).compare("UNEXPLORED") == 0)
				graph.setEdgeLabel(currentVertex, adjacent[x], "CROSS");
			if(graph.getEdgeWeight(currentVertex, adjacent[x]) <= minWeightVal)
			{
				minWeightVal = graph.getEdgeWeight(currentVertex,adjacent[x]);
				minVertex = currentVertex;
				minWeight = adjacent[x];
			}
			x++;
		}
	}

	graph.setEdgeLabel(minVertex, minWeight, "MIN");
	
	return minWeightVal;

}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  startPoint and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param startPoint - the vertex to startPoint the search from
 * @param end - the vertex to find adjacent[x] path to
 * @return the minimum number of edges between startPoint and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex startPoint, Vertex end)
{
	//TODO: YOUR CODE HERE

	setVisited(graph);
	queue<Vertex> q;
	graph.setVertexLabel(startPoint, "VISITED");
	q.push(startPoint);
	unordered_map<Vertex, Vertex> vertexMap;
	while(q.empty() == false)
	{
		Vertex currentVertex = q.front();
		vector<Vertex> adjacent = graph.getAdjacent(q.front());
		q.pop();
		size_t x = 0;
		while (x < adjacent.size())
		{
			if (graph.getVertexLabel(adjacent[x]).compare("UNEXPLORED") == 0)
			{
				vertexMap[adjacent[x]] = currentVertex;
				graph.setEdgeLabel(currentVertex, adjacent[x], "DISCOVERY");
				graph.setVertexLabel(adjacent[x], "VISITED");
				q.push(adjacent[x]);
			} 
			if (graph.getEdgeLabel(currentVertex, adjacent[x]).compare("UNEXPLORED") == 0)
				graph.setEdgeLabel(currentVertex, adjacent[x], "CROSS");
			x++;
		}
	}

	int retVal = 0;
	for (int y = 0; end != startPoint; y++)
	{
		graph.setEdgeLabel(end, vertexMap[end], "MINPATH");
		end = vertexMap[end];
		retVal = y;
	}
	retVal++;
	return retVal;
}

/**
 * Finds adjacent[x] minimal spanning tree on adjacent[x] graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of adjacent[x] minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating adjacent[x] priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
	//TODO: YOUR CODE HERE
	vector <Edge> edge_list = graph.getEdges();
	sort(edge_list.begin(), edge_list.end(), sortEdges);
	DisjointSets vertices;
	vector <Vertex> vertex_list = graph.getVertices();
	vertices.addelements(vertex_list.size());

	size_t x = 0;
	while (x < edge_list.size())
	{
		Vertex u = edge_list[x].source;
		Vertex v = edge_list[x].dest;
		int vertexU = std::stoi(u, NULL, 10);
		int vertexV = std::stoi(v, NULL, 10);		
		if (vertices.find(vertexU) != vertices.find(vertexV))
		{
			vertices.setunion((vertexU),vertexV);
			graph.setEdgeLabel(u,v,"MST");
		}

		x++;
	}
}


