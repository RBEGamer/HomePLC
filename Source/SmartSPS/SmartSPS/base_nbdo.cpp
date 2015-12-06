#include "node_nbdo.h"

node_nbdo::node_nbdo(int id)
{
	nid = id;
}

node_nbdo::~node_nbdo()
{
}

void node_nbdo::update(float timestep)
{
	if (node_nbdo::updated_values) {
		node_nbdo::updated_values = false;
		//logic machen

		if (node_nbdo::value_input_state) {
			//SEND TO SERIAL SEND QUARRY -> PORT HIGH
		}
		else {
			//SEND TO SERIAL SEND QUARRY -> PORT LOW
		}

		//hier sonst alle weitren node durchgehen
	}
}

void node_nbdo::init()
{
}

void node_nbdo::load_node_parameters(char params[])
{
	//WIRTE SPLIT FUNKTION TO ADD PARAMETERS TO FUNKTION
}

//
