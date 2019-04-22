#include "Astar.h"

Astar::Astar() {
	map.loadMap();
}

Astar::~Astar()
{
}

void Astar::SetValues(MathLib::Vec2 posOrigen, MathLib::Vec2 posDestino) {
	SetValues(posOrigen.x(), posOrigen.y(), posDestino.x(), posDestino.y());
}


void Astar::SetValues(int sourceX, int sourceY, int destinationX, int destinationY) {
	nodoInicial = Node(sourceX, sourceY, false, true);
	nodoDestino = Node(destinationX, destinationY, true, true);
	int h = GetHeuristic(nodoInicial, nodoDestino);
	nodoInicial.Fvalue = h;
	nodoInicial.Hvalue = h;
	nodoInicial.Gvalue = 0;

	nodoDestino.Fvalue = 0;
	nodoDestino.Gvalue = 0;
	nodoDestino.Hvalue = 0;
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
	nodesAdyacentes[0] = Node(nodo.posX + 0, nodo.posY + 1, false, map.map_l1[(nodo.posX + 0) / 8][(nodo.posY + 1) / 8] == 0);
	nodesAdyacentes[1] = Node(nodo.posX + 1, nodo.posY + 1, false, map.map_l1[(nodo.posX + 1) / 8][(nodo.posY + 1) / 8] == 0);
	nodesAdyacentes[2] = Node(nodo.posX + 1, nodo.posY + 0, false, map.map_l1[(nodo.posX + 1) / 8][(nodo.posY + 0) / 8] == 0);
	nodesAdyacentes[3] = Node(nodo.posX + 1, nodo.posY - 1, false, map.map_l1[(nodo.posX + 1) / 8][(nodo.posY - 1) / 8] == 0);

	nodesAdyacentes[4] = Node(nodo.posX + 0, nodo.posY - 1, false, map.map_l1[(nodo.posX + 0) / 8][(nodo.posY - 1) / 8] == 0);
	nodesAdyacentes[5] = Node(nodo.posX - 1, nodo.posY - 1, false, map.map_l1[(nodo.posX - 1) / 8][(nodo.posY - 1) / 8] == 0);
	nodesAdyacentes[6] = Node(nodo.posX - 1, nodo.posY + 0, false, map.map_l1[(nodo.posX - 1) / 8][(nodo.posY + 0) / 8] == 0);
	nodesAdyacentes[7] = Node(nodo.posX - 1, nodo.posY + 1, false, map.map_l1[(nodo.posX - 1) / 8][(nodo.posY + 1) / 8] == 0);
}


Node Astar::GetMinorFNode(std::vector<Node> listaAbierta)
{
	int FMinor = std::numeric_limits<int>::max();
	Node nodeFMinor;
	for (std::vector<Node>::iterator it = listaAbierta.begin(); it != listaAbierta.end(); ++it)
	{
		int ActualFValueToCheck = ((Node)*it).Fvalue;
		if (ActualFValueToCheck < FMinor) {
			FMinor = ActualFValueToCheck;
			nodeFMinor = ((Node)*it);
		}
	}
	return nodeFMinor;
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
		for each (Node var in listaAbierta)
		{
			int ActualFValueToCheck = var.Fvalue;
			if (ActualFValueToCheck < FMinor) {
				FMinor = ActualFValueToCheck;
			}
		}
		for each (Node var in listaAbierta)
		{
			int ActualFValueToCheck = var.Fvalue;
			if (var.Fvalue == FMinor) {

				nodeWithMinorF = var;
				break;
			}
		}
		//Node nodeWithMinorF = GetMinorFNode(listaAbierta);
		loading = true;

		listaCerrada.push_back(nodeWithMinorF);
		GetAdyacentes(nodeWithMinorF);
		RemoveFromList(listaAbierta, nodeWithMinorF);
		for (size_t i = 0; i < 8; i++)
		{
			if (nodesAdyacentes[i]._transitable && !FoundInList(listaCerrada, nodesAdyacentes[i])) {

				if (!FoundInList(listaAbierta, nodesAdyacentes[i])) {
					int h = GetHeuristic(nodesAdyacentes[i], nodoDestino);
					int g = GetGValue(nodeWithMinorF, nodesAdyacentes[i]);
					nodesAdyacentes[i].Gvalue = g;
					nodesAdyacentes[i].Hvalue = h;
					nodesAdyacentes[i].Fvalue = g + h;
					//SetParent(nodesAdyacentes[i], nodeWithMinorF);
					Node* parent = new Node(nodeWithMinorF.posX, nodeWithMinorF.posY, nodeWithMinorF._destino, nodeWithMinorF._transitable);
					parent->Fvalue = nodeWithMinorF.Fvalue;
					parent->Gvalue = nodeWithMinorF.Gvalue;
					parent->Hvalue = nodeWithMinorF.Hvalue;
					parent->_parent = &nodeWithMinorF;
					nodesAdyacentes[i]._parent = parent;
					//SetParent(nodesAdyacentes[i], nodeWithMinorF);
					listaAbierta.push_back(nodesAdyacentes[i]);

				}
				else {
					Node nodoFromList = GetFromList(listaAbierta, nodesAdyacentes[i]);
					if (nodoFromList.Gvalue < nodeWithMinorF.Gvalue) {
						RemoveFromList(listaAbierta, nodeWithMinorF);

						int g = GetGValue(nodoFromList, nodeWithMinorF);
						nodeWithMinorF.Gvalue = g;
						nodeWithMinorF.Fvalue = g + nodeWithMinorF._parent->Hvalue;

						Node* parent = new Node(nodeWithMinorF.posX, nodeWithMinorF.posY, nodeWithMinorF._destino, nodeWithMinorF._transitable);
						parent->Fvalue = nodeWithMinorF.Fvalue;
						parent->Gvalue = nodeWithMinorF.Gvalue;
						parent->Hvalue = nodeWithMinorF.Hvalue;
						parent->_parent = &nodeWithMinorF;
						nodoFromList._parent = parent;


						listaAbierta.push_back(nodoFromList);

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


MathLib::Vec2 Astar::GetNextPosition(Node &inicio)
{
	MathLib::Vec2 newPosition;
	if (DifferentPositions(inicio.GetPosition(), nodoDestino.GetPosition())) {
		std::vector<Node>::iterator it = std::find(listaCerrada.begin(), listaCerrada.end(), inicio);
		if (it != listaCerrada.end()) {

			auto nx = std::next(it, 1);
			inicio = ((Node)*nx);
			newPosition = ((Node)*nx).GetPosition();
			return newPosition;
		}

	}

	return newPosition;
}

std::vector<Node> Astar::GetCamino()
{
	std::vector<Node> camino;
	Node nodeDestino = listaCerrada.at(listaCerrada.size() - 1);
	do {
		if (nodeDestino._parent != NULL) {
			Node nodoFromList = GetFromList(listaCerrada, *nodeDestino._parent);

			camino.push_back(nodeDestino);
			nodeDestino = nodoFromList;
		}
	} while (nodeDestino._parent != NULL);
	return camino;
}