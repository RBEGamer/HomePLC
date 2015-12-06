#include "node_nbsttoi.h"

node_nbsttoi::node_nbsttoi(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}



node_nbsttoi::~node_nbsttoi()
{
	delete(p_connections);
}

void node_nbsttoi::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;

		//p2_c_output = (p0_a_input & p1_b_input);
		p1_b_output = atoi(p0_a_input.c_str());

		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		for (size_t i = 0; i < connection_count; i++) {
			switch ((p_connections + i)->input_pos) {
			case 1:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p1_b_output);
					std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			default:
				break;
			}
		}
	}
}

void node_nbsttoi::init()
{
	node_nbsttoi::p0_a_input = "";
	node_nbsttoi::p1_b_output = 0;
}

void node_nbsttoi::load_node_parameters(std::string params)
{

}



void node_nbsttoi::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_nbsttoi::serial_income(std::string message)
{
}

void node_nbsttoi::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_a_input = value; break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_nbsttoi::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_a_input = value;  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_nbsttoi::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0: if (value) { p0_a_input = "TRUE"; }
			else { p0_a_input = "FALSE"; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_nbsttoi::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_a_input = value;  break;
	default:uv = false; break;
	}
	updated_values = uv;
}









float node_nbsttoi::get_value_f(int position)
{
	
}

int node_nbsttoi::get_value_i(int position)
{
	
}

bool node_nbsttoi::get_value_b(int position)
{
	
}

std::string node_nbsttoi::get_value_s(int position)
{
	
}
