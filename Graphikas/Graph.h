#pragma once
#include <map>
#include <list>
#include <vector>

struct arch {

	int origin;

	int end;

};



class GraphD
{

	struct nexus {

		int data;

		std::list<nexus*> links;


	};

		//atributes
private:
	std::map<int,nexus*> nodes;



	//metodos
public:
	GraphD();
	GraphD(std::vector<arch> &arches);
	~GraphD();


	void insertArch(arch _arch);
	void destroyArch(arch _arch);






};

