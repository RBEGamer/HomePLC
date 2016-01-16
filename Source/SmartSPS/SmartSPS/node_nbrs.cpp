#include "node_nbrs.h"


node_nbrs::node_nbrs(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
	use_timer = ut;
}

node_nbrs::~node_nbrs()
{
}

void node_nbrs::update(float timestep)
{
	if (node_nbrs::updated_values) {
		node_nbrs::updated_values = false;


		for (size_t i = 0; i < connection_count; i++) {
			switch ((p_connections + i)->input_pos) {
			case 2:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p0_value_output_state);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			default:
				break;
			}
		}


	
		//p0_value_output_state
	}
}

void node_nbrs::init()
{

}


void node_nbrs::load_node_parameters(std::string params)
{
	return;

}



void node_nbrs::set_connection(int pos, base_node * ptr, int dest_pos)
{

	if (ptr != NULL) {


		//FORSCHLEIFE 
		for (size_t i = 0; i < connection_count; i++)
		{
			if ((p_connections + i)->connector_node_ptr == NULL) {
				(p_connections + i)->connector_node_ptr = ptr;
				(p_connections + i)->output_pos = dest_pos;
				(p_connections + i)->input_pos = pos;
				break;
			}

		}
	}
}
void node_nbrs::serial_income(std::string message)
{
	p0_value_output_state = "";
	updated_values = true;
}

void node_nbrs::set_value(int position, float value)
{

	

}

void node_nbrs::set_value(int position, int value)
{
	

}

void node_nbrs::set_value(int position, bool value)
{

	
}

void node_nbrs::set_value(int position, std::string value)
{

	

}





float node_nbrs::get_value_f(int position)
{

}

int node_nbrs::get_value_i(int position)
{

}

bool node_nbrs::get_value_b(int position)
{

}

std::string node_nbrs::get_value_s(int position)
{

}
