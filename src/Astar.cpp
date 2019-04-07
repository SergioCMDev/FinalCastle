#include "Astar.h"

Astar::Astar(int sourceX, int sourceY, int destinationX, int destinationY) {
	nodoInicial = Node(sourceX, sourceY, false, true, NULL);
	nodoDestino = Node(destinationX, destinationY, true, true, NULL);
	int h = GetHeuristic(nodoInicial, nodoDestino);
	nodoInicial.Fvalue = h;
	nodoInicial.Hvalue = h;
	nodoInicial.Gvalue = 0;

	nodoDestino.Fvalue = 0;
	nodoDestino.Gvalue = 0;
	nodoDestino.Hvalue = 0;
	map.loadMap();
}

Astar::~Astar()
{
}

Astar::Astar() {

}


void Astar::CreatePathFromDestination(Node *nodoDestino, std::vector<Node> lista) {
	/*Node* node = nodoDestino->_parent;
	do {
		lista.push_back(*node);
		node = node->_parent;
	} while (node->_parent != NULL);*/

}


int Astar::GetGValue(Node &nodo, Node nodeAdyacente) {
	int ActualG = -1;
	if (((nodeAdyacente.posY > nodo.posY || nodeAdyacente.posY < nodo.posY) && nodeAdyacente.posX == nodo.posX) || //Check Above and below
		((nodeAdyacente.posX > nodo.posX || nodeAdyacente.posX < nodo.posX) && nodeAdyacente.posY == nodo.posY)) {
		ActualG = HORIZONTAL_COST;
	}
	else { //ITs diagonal

		ActualG = VERTICAL_COST;
	}
	int	gParent = 0;
	if (nodo._parent != NULL) {
		gParent = nodo._parent->Gvalue;

	}
	return ActualG + gParent;
}

int Astar::GetHeuristic(Node nodo, Node nodeDestino) {
	return abs(nodeDestino.posX - nodo.posX) * HORIZONTAL_COST + abs(nodeDestino.posY - nodo.posY) * VERTICAL_COST; //Manhattan
}

bool Astar::FoundInList(std::vector<Node> &lista, Node &node) {
	return  std::find(lista.begin(), lista.end(), node) != lista.end();
}

Node Astar::GetFromList(std::vector<Node> &lista, Node node) {
	std::vector<Node>::iterator it = std::find(lista.begin(), lista.end(), node);
	return (Node)*it;
}

void Astar::FillValuesNode(Node &nodo, Node &nodeAdyacente, Node NodeDestino)
{
	int GValue = -1;
	int HValue = -1;
	int g = GetGValue(nodo, nodeAdyacente);
	int h = GetHeuristic(nodo, NodeDestino);
	int FValue = GValue + HValue;
	nodeAdyacente.Fvalue = FValue;
	nodeAdyacente.Gvalue = GValue;
	nodeAdyacente.Hvalue = HValue;
}


void Astar::GetAdyacentes(Node nodo) {
	nodesAdyacentes[0] = Node(nodo.posX + 0, nodo.posY + 1, false, map.map_l1[(nodo.posX + 0) / 8][(nodo.posY + 1) / 8] == 0, NULL);
	nodesAdyacentes[1] = Node(nodo.posX + 1, nodo.posY + 1, false, map.map_l1[(nodo.posX + 1) / 8][(nodo.posY + 1) / 8] == 0, NULL);
	nodesAdyacentes[2] = Node(nodo.posX + 1, nodo.posY + 0, false, map.map_l1[(nodo.posX + 1) / 8][(nodo.posY + 0) / 8] == 0, NULL);
	nodesAdyacentes[3] = Node(nodo.posX + 1, nodo.posY - 1, false, map.map_l1[(nodo.posX + 1) / 8][(nodo.posY - 1) / 8] == 0, NULL);

	nodesAdyacentes[4] = Node(nodo.posX + 0, nodo.posY - 1, false, map.map_l1[(nodo.posX + 0) / 8][(nodo.posY - 1) / 8] == 0, NULL);
	nodesAdyacentes[5] = Node(nodo.posX - 1, nodo.posY - 1, false, map.map_l1[(nodo.posX - 1) / 8][(nodo.posY - 1) / 8] == 0, NULL);
	nodesAdyacentes[6] = Node(nodo.posX - 1, nodo.posY + 0, false, map.map_l1[(nodo.posX - 1) / 8][(nodo.posY + 0) / 8] == 0, NULL);
	nodesAdyacentes[7] = Node(nodo.posX - 1, nodo.posY + 1, false, map.map_l1[(nodo.posX - 1) / 8][(nodo.posY + 1) / 8] == 0, NULL);
}


void Astar::GetMinorFNode(std::vector<Node> &listaAbierta, int &FMinor, Node &minorF)
{
	for (std::vector<Node>::iterator it = listaAbierta.begin(); it != listaAbierta.end(); ++it)
	{
		int ActualFValueToCheck = ((Node)*it).Fvalue;
		if (ActualFValueToCheck < FMinor) {
			FMinor = ActualFValueToCheck;
			minorF = ((Node)*it);
		}
	}
}

void RemoveFromList(std::vector<Node> &lista, Node &FMinor) {
	std::vector<Node>::iterator it = std::find(lista.begin(), lista.end(), FMinor);
	if (it != lista.end()) {
		lista.erase(it);
	}
}

void Astar::GetPath() {

	listaAbierta.push_back(nodoInicial);
	bool destino = false;
	int g, h;
	while (!FoundInList(listaCerrada, nodoDestino) || listaAbierta.empty()) {
		int FMinor = std::numeric_limits<int>::max();
		Node nodeWithMinorF;
		GetMinorFNode(listaAbierta, FMinor, nodeWithMinorF);
		loading = true;
		listaCerrada.push_back(nodeWithMinorF);
		GetAdyacentes(nodeWithMinorF);
		RemoveFromList(listaAbierta, nodeWithMinorF);
		for (size_t i = 0; i < 8; i++)
		{
			if (nodesAdyacentes[i]._transitable && !FoundInList(listaCerrada, nodesAdyacentes[i])) {

				if (!FoundInList(listaAbierta, nodesAdyacentes[i])) {
					//nodesAdyacentes[i]._parent = &nodeWithMinorF;
					nodeWithMinorF._parent = &nodesAdyacentes[i];
					int h = GetHeuristic(nodesAdyacentes[i], nodoDestino);
					int g = GetGValue(nodeWithMinorF, nodesAdyacentes[i]);
					nodesAdyacentes[i].Fvalue = g + h;
					nodesAdyacentes[i].Gvalue = g;
					nodesAdyacentes[i].Hvalue = h;
					//FillValuesNode(minorF, nodesAdyacentes[i], nodoDestino);
					listaAbierta.push_back(nodesAdyacentes[i]);
				}
				else {
					Node nodoFromList = GetFromList(listaAbierta, nodesAdyacentes[i]);
					if (nodoFromList.Gvalue < nodeWithMinorF.Gvalue) {
						RemoveFromList(listaAbierta, nodeWithMinorF);

						nodoFromList._parent = &nodeWithMinorF;
						int g = GetGValue(nodoFromList, nodeWithMinorF);
						nodeWithMinorF.Gvalue = g;
						nodeWithMinorF.Fvalue = g + nodoFromList.Hvalue;
						listaAbierta.push_back(nodeWithMinorF);

					}
				}
			}
		}
		nodeWithMinorF.Fvalue = std::numeric_limits<int>::max();
		std::cout << "Loading..." << std::endl;
	}
	//CreatePathFromDestination(&nodoDestino, camino);
	loading = !loading;
}
