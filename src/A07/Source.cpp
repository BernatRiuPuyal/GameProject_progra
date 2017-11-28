
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

#include <string>
#include <sstream>
#include <vector>



struct enemy {

	std::string nom;
	int vitalitat;
	int malAtac;
	int defensa;
	float  freq;
	int exp;
};





int main() {

	rapidxml::xml_document<> doc;

	std::ifstream file("config.xml");

	std::stringstream buffer;

	buffer << file.rdbuf();

	file.close();
	
	std::string content(buffer.str());

	doc.parse<0>(&content[0]);

	rapidxml::xml_node<> *pRoot = doc.first_node();

	std::vector<enemy> enemies;

	

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("enemy"); pNode; pNode = pNode->next_sibling()) {

		enemy insEnemy;

		insEnemy.nom = pNode->first_attribute()->value();

		insEnemy.vitalitat = atoi(pNode->first_node("vit")->value());

		insEnemy.malAtac = atoi(pNode->first_node("atDam")->value());

		insEnemy.defensa = atoi(pNode->first_node("def")->value());

		insEnemy.freq = (float)atof(pNode->first_node("frqAt")->value());

		insEnemy.exp = atoi(pNode->first_node("exp")->value());


		enemies.push_back(insEnemy);

	}







}