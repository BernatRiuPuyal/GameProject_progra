#include "Graph.h"



GraphD::GraphD()
{
}

GraphD::GraphD(std::vector<arch> &_arches) {

	for (auto it = _arches.begin(); it != _arches.end(); it++) insertArch(*it);

}

void GraphD::insertArch(arch _arch) { //pot ser que existeixin dos arches iguals 


	if (nodes[_arch.origin] == nullptr) {

		nodes[_arch.origin] = new nexus;
		nodes[_arch.origin]->data = _arch.origin;
	}
	

	if (nodes[_arch.end] == nullptr) {

		nodes[_arch.end] = new nexus;
		nodes[_arch.end]->data = _arch.end;
	}
	else {

	};
			

	nodes[_arch.origin]->links.push_back(nodes[_arch.end]);
}

void GraphD::destroyArch(arch _arch)
{
	


	for (auto it = nodes[_arch.origin]->links.begin(); it != nodes[_arch.origin]->links.end(); it++) {
		if ((*it) == nodes[_arch.end]) {
			nodes[_arch.origin]->links.erase(it);
			break;
		}
	}

}






GraphD::~GraphD()
{
}
