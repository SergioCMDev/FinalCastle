#include "Node.h"



Node::Node()
{
}


Node::Node(int x, int y, bool destino, bool transitable, Node* parent) {
	posX = x;
	posY = y;
	_destino = destino;
	_transitable = transitable;
	_parent = parent;
	Gvalue = 0;
}

Node::Node(int F, int G, int H, bool destino, bool transitable, Node* parent)
{
	Fvalue = F;
	Gvalue = G;
	Hvalue = H;
	_destino = destino;
	_transitable = transitable;
	_parent = parent;
}


Node::~Node()
{
}