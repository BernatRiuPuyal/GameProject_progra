#include "Graph.h"





int main() {


	std::vector<arch> ole;

	ole.push_back({ 1,2 });
	ole.push_back({ 1,3 });
	ole.push_back({ 1,4 });
	ole.push_back({ 2,3 });


	GraphD estit(ole);

	estit.destroyArch({ 1,2 });

}