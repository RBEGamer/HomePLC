#include "connector.h"

connector::connector()
{
	input_pos = -1;
	output_pos = -1;
	connector_node_ptr = 0;

}

connector::~connector()
{
}

connector::connector(int ninput_pos, int noutput_pos, base_node* nnode_ptr)
{
	input_pos = ninput_pos;
	output_pos = noutput_pos;
	nnode_ptr = nnode_ptr;
}
