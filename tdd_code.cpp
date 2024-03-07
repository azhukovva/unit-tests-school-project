//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Aryna Zhukava <xzhuka01@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"

Graph::Graph() {}

Graph::~Graph() {}

std::vector<Node *> Graph::nodes()
{
    // std::vector<Node *> nodes;

    return nodeList;
}

std::vector<Edge> Graph::edges() const
{
    // std::vector<Edge> edges;

    return edgeList;
}

Node *Graph::addNode(size_t nodeId)
{
    for (auto &node : nodeList)
    {
        if (node->id == nodeId)
            return nullptr;
    }
    Node *node = new Node{nodeId};
    if (node == nullptr)
        return nullptr;

    node->id = nodeId;
    nodeList.push_back(node);
    return node;
}

bool Graph::addEdge(const Edge &edge)
{
    for (auto &graphEdge : edgeList)
    {
        if (graphEdge == edge)
            return false;
    }
    if (edge.a == edge.b)
        return false;

    if (getNode(edge.a) == nullptr)
        addNode(edge.a);

    if (getNode(edge.b) == nullptr)
        addNode(edge.b);

    edgeList.push_back(edge);
    return true;
}

void Graph::addMultipleEdges(const std::vector<Edge> &edges)
{
    for (auto &graphEdge : edges)
        addEdge(graphEdge);
}

Node *Graph::getNode(size_t nodeId)
{
    for (auto &node : nodeList)
    {
        if (node->id == nodeId)
            return node;
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge &edge) const
{
    for (auto &graphEdge : edgeList)
    {
        if (graphEdge == edge)
            return true; // contains
    }
    return false;
}

void Graph::removeNode(size_t nodeId)
{
    Node *nodePtr = getNode(nodeId); // pointer to the node with nodeID
    if (nodePtr == nullptr)
        throw std::out_of_range("Node is not found");

    std::vector<Edge> updatedEdges;
    for (auto &edge : edgeList)
    {
        if (edge.a != nodeId && edge.b != nodeId)
        {
            updatedEdges.push_back(edge);
        }
    }
    edgeList = updatedEdges;

    std::vector<Node *> updatedNodes;
    for (auto &node : nodeList)
    {
        if (node->id != nodeId)
        {
            updatedNodes.push_back(node);
        }
    }
    nodeList = updatedNodes; // New list of nodes without node with nodeId

    free(nodePtr);
}

void Graph::removeEdge(const Edge &edge)
{
    if (containsEdge(edge))
    {
        std::vector<Edge> edges;
        for (auto &graphEdge : edgeList)
        {
            if (graphEdge != edge)
                edges.push_back(graphEdge);
        }
        // New list of edges
        this->edgeList = edges;
    }
    else
        throw std::out_of_range("Edge is not found");
}

size_t Graph::nodeCount() const
{
    return nodeList.size();
}

size_t Graph::edgeCount() const
{
    return edgeList.size();
}

size_t Graph::nodeDegree(size_t nodeId) const
{
    int degree = 0;
    for (auto &node : nodeList)
    {
        if (node->id == nodeId) // if this node exists
        {
            for (auto &edge : edgeList)
            {
                if (edge.a == nodeId || edge.b == nodeId)
                    ++degree;
            }
        }
    }
    if (degree == 0)
        throw std::out_of_range("Node is not found");
    return degree;
}

size_t Graph::graphDegree() const
{
    size_t maxDegree = 0;
    for (const auto &node : nodeList)
    {
        size_t degree = nodeDegree(node->id);    // The number of edges connected to this node
        maxDegree = std::max(maxDegree, degree); // Compares the current maximum degree(maxDegree) with the degree of the current node(degree) and returns the greater
    }

    return maxDegree;
}

void Graph::coloring()
{
    int color = 1; // start color 
    size_t maxColor = graphDegree() + 1; 

    for (auto &node : nodeList)
    {
        node->color = color;
        if (node->color >= maxColor) // if it is a max -> return to the start color
            color = 1;
        color++; // Next colour for the next node
    }
}

void Graph::clear()
{
    for (auto &node : nodeList){
        delete node;
    }
    nodeList.clear();
    edgeList.clear();
}

/*** Konec souboru tdd_code.cpp ***/
