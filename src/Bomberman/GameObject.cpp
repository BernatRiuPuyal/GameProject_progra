#include "GameObject.h"



GameObject::GameObject()
{
	blocksPJ = false;		//nom�s a alguns walls sera true, ja s'especificara en ells.
	destructible = false;	// " " " " " " " 
	impacted = false;		//true al ser tocat per explosi�
	picked = false;			//d'inici cap objete es agafat
	type = NOTHING;
}


GameObject::~GameObject()
{
}

