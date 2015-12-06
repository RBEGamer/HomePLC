#pragma once
#include "base_node.h"
class connector
{
public:
	connector();
	~connector();
	connector(int ninput_pos, int noutput_pos, base_node* nnode_ptr);
	base_node* connector_node_ptr; //refrence to the next node
	int input_pos;
	int output_pos;


private:

};

