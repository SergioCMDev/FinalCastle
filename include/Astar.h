#ifndef __ASTAR_H__
#define __ASTAR_H__ 1

#pragma once
#include <vector>
#include <defines.h>
#include <Node.h>
#include <Read_map.h>
#include <sprite.h>
#include <iostream>
class Astar
{
public:
	Astar();
	~Astar();
	void GetPath();
	void SetValues(int sourceX, int sourceY, int destinationX, int destinationY);
	void SetValues(MathLib::Vec2 posOrigen, MathLib::Vec2 posDestino);
	std::vector<Node> listaCerrada;
	bool loading = false;
	Node nodoDestino;
	MathLib::Vec2 GetNextPosition(Node &inicio);
	std::vector<Node> GetCamino();


private:
	int GetGValue(Node &nodo, Node nodeAdyacente);
	int GetHeuristic(Node nodo, Node nodeDestino);
	Node GetFromList(std::vector<Node> &lista, Node node);
	bool FoundInList(std::vector<Node> &lista, Node &node);
	void FillValuesNode(Node &nodo, Node &nodeAdyacente, Node NodeDestino);
	void GetAdyacentes(Node nodo);
	Node GetMinorFNode(std::vector<Node> listaAbierta);
	std::vector<Node> listaAbierta;
	Node nodesAdyacentes[8];
	Node nodoInicial;
	std::vector<Node> camino;
	Read_Map map;
	int indiceListaAbierta = 0;
	Node* CreateNewParent(Node nodeWithMinorF);
};
#endif