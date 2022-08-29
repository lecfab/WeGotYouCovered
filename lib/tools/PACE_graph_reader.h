/**
 * PACE_graph_reader.h
 *
 * Copyright (C) 2019 Demian Hespe <hespe@kit.edu>
 *****************************************************************************/

#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

void istream_reset(std::istream& is) {
  is.clear();
  is.seekg(0, is.beg);
}

std::pair<int,int> get_num_vertices_edges(std::istream& infile, bool &has_node_zero) {
  istream_reset(infile); // first pass to count vertices and edges
  int v_num = 0, e_num = 0;
  int u, v;
	while(infile >> u >> v) {
    if(u == v) {
      std::cout << "Self-loops are not authorised. Found one with node "<< u << std::endl;
      return {0, 0};
    }
    e_num ++;

    if(u == 0 or v == 0) has_node_zero = true;  // check whether node indices start at 0 or 1
    if(u > v_num) v_num = u;
    if(v > v_num) v_num = v;
	}
  if(has_node_zero) v_num ++;

  std::cout << "Number of nodes: " << v_num << std::endl;
	std::cout << "Number of edges: " << e_num << std::endl;

  return {v_num, e_num};
}

std::vector<std::vector<int>> readPaceGraph(std::istream& infile) {
    bool has_node_zero = false;
    int numVertices;
    int numEdges;
    std::string line;
    while (getline(infile, line)) {
        std::istringstream iss(line);
        char firstSymbol;
        if (!(iss >> firstSymbol)) { break; } // error

        if(firstSymbol == 'c') { continue; }
        else if(firstSymbol == 'p') {
            std:: string td;
            iss >> td >> numVertices >> numEdges;
            break;
        }
        else {
          std::pair<int,int> num_vertices_edges = get_num_vertices_edges(infile, has_node_zero);
          istream_reset(infile); // second pass to build the graph
          numVertices = num_vertices_edges.first;
          numEdges = num_vertices_edges.second;
          break;
        }
    }

    std::vector<std::vector<int>> graph(numVertices);

    while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }

        if(line[0] == 'c') {
            continue;
        }

        std::istringstream iss(line);

        int u, v;
        iss >> u >> v;

        if(!has_node_zero) { --u; --v; } // only necessary when nodes start from 1

        if(u < 0 || u >= numVertices) {
            std::cout << "Invalid node ID: " << u <<std::endl;
            exit(1);
        }
        if(v < 0 || v >= numVertices) {
            std::cout << "Invalid node ID: " << v <<std::endl;
            exit(1);
        }

        if(u == v) {
            continue;
        }

        if(std::find(graph[u].begin(), graph[u].end(), v) == graph[u]. end()) {
            graph[u].push_back(v);
        }

        if(std::find(graph[v].begin(), graph[v].end(), u) == graph[v]. end()) {
            graph[v].push_back(u);
        }
    }

    for(int i = 0; i < numVertices; ++i) {
        std::sort(graph[i].begin(), graph[i].end());
    }

    return graph;
}


std::vector<std::vector<int>> readPaceGraphFromFile(std::string fileName) {
    std::ifstream fin(fileName);
    return readPaceGraph(fin);
}

std::vector<std::vector<int>> readPaceGraphFromCin() {
    return readPaceGraph(std::cin);
}
