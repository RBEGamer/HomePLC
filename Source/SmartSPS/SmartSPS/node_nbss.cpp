#include "node_nbss.h"


node_nbss::node_nbss(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
	use_timer = ut;
}

node_nbss::~node_nbss()
{
}

void node_nbss::update(float timestep)
{
	if (node_nbss::updated_values) {
		node_nbss::updated_values = false;
		
			//SEND TO SERIAL SEND QUARRY -> PORT LOW
			serial_management::add_to_send_queue(p0_value_input_state +"\n");
		
	}
}

void node_nbss::init()
{
	p0_value_input_state = "";
		updated_values = false;
}


void node_nbss::load_node_parameters(std::string params)
{
	return;

}



void node_nbss::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_nbss::serial_income(std::string message)
{
	

}

void node_nbss::set_value(int position, float value)
{

	bool uv = true;
	switch (position)
	{
	case 0: p0_value_input_state = NumberToString(value); break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_nbss::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_value_input_state = NumberToString(value); break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_nbss::set_value(int position, bool value)
{

	bool uv = true;
	switch (position)
	{
	case 0:  if (value) { p0_value_input_state = "TRUE"; }
			 else { p0_value_input_state = "FALSE"; }  break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_nbss::set_value(int position, std::string value)
{

	bool uv = true;
	switch (position)
	{
	case 0:  p0_value_input_state = value; 
			 break;


	default:uv = false; break;
	}
	updated_values = uv;

}





float node_nbss::get_value_f(int position)
{
	
}

int node_nbss::get_value_i(int position)
{
	
}

bool node_nbss::get_value_b(int position)
{
	
}

std::string node_nbss::get_value_s(int position)
{
	
}
