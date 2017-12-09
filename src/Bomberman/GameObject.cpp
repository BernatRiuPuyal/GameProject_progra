#include "GameObject.h"



GameObject::GameObject()
{
	blocksPJ = false;		//només a alguns walls sera true, ja s'especificara en ells.
	destructible = false;	// " " " " " " " 
	impacted = false;		//true al ser tocat per explosió
	picked = false;			//d'inici cap objete es agafat
	type = NOTHING;
}


GameObject::~GameObject()
{
}

