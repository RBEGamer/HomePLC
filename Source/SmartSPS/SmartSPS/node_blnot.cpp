#include "node_blnot.h"

node_blnot::node_blnot(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}



node_blnot::~node_blnot()
{
	delete(p_connections);
}

void node_blnot::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;

		//p2_c_output = (p0_a_input & p1_b_input);
		p1_b_output = !p0_a_input;


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

void node_blnot::init()
{
	node_blnot::p0_a_input = false;
	node_blnot::p1_b_output = false;
}

void node_blnot::load_node_parameters(std::string params)
{

}



void node_blnot::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_blnot::serial_income(std::string message)
{
}

void node_blnot::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value > 1.0f) { p0_a_input = true; }
			 else { p0_a_input = false; }  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_blnot::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value > 0) { p0_a_input = true; }
			 else { p0_a_input = false; }  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_blnot::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_a_input = value;  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_blnot::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value == "TRUE") { p0_a_input = true; }
			 else { p0_a_input = false; }  break;
	default:uv = false; break;
	}
	updated_values = uv;
}









float node_blnot::get_value_f(int position)
{
	switch (position)
	{
	case 0:if (p0_a_input) { return 1.0f; }
		   else { return 0.0f; } break;
	case 1:if (p1_b_output) { return 1.0f; }
		   else { return 0.0f; } break;

	default:
		return -1.0f;
		break;
	}
}

int node_blnot::get_value_i(int position)
{
	switch (position)
	{
	case 0:if (p0_a_input) { return 1; }
		   else { return 0; } break;
	case 1:if (p1_b_output) { return 1; }
		   else { return 0; } break;

	default:
		return -1;
		break;
	}
}

bool node_blnot::get_value_b(int position)
{
	switch (position)
	{
	case 0: return p0_a_input; break;
	case 1: return p1_b_output; break;
	default:
		return -1.0f;
		break;
	}
}

std::string node_blnot::get_value_s(int position)
{
	switch (position)
	{
	case 0:if (p0_a_input) { return "TRUE"; }
		   else { return "FALSE"; } break;
	case 1:if (p1_b_output) { return "TRUE"; }
		   else { return "FALSE"; } break;

	default:
		return "FALSE";
		break;
	}
}
