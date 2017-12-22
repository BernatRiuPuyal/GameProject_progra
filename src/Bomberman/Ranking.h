#pragma once
#include "Scene.h"
#include <vector>



class Ranking :
	public Scene
{
	enum phase{ENTERNAME1,ENTERNAME2,SHOWRANK};

	struct rankMember {
		std::string name;
		int score;

		bool operator<(rankMember a){

			return score < a.score;
		}

	};
	//atributos
private:
	std::vector<rankMember> rank;
	
	button buttonBack;

	phase enterName; //

	std::string introName; //name introducing 


	//metodos

public:




	Ranking(bool comeFromLevel); //comeFromLevel determina si s'ha vingut des de joc o no
	~Ranking();



private:
	void setup() override;
	void draw() override;
	void update() override;
	void inputHandler() override;

};

