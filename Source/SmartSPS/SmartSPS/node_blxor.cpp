#include "node_blxor.h"

node_blxor::node_blxor(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
	use_timer = ut;
}



node_blxor::~node_blxor()
{
	delete(p_connections);
}

void node_blxor::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;

		//p2_c_output = (p0_a_input & p1_b_input);
		if (p0_a_input != p1_b_input) {
			p1_b_input = true;
		}
		else {
			p2_c_output = false;
		}

		if (p2_c_output != output_updated) {
			output_updated = p2_c_output;

			//hier sonst alle weitren node durchgehen //f�r alle nodes di einen ausgansnode besitzen
			for (size_t i = 0; i < connection_count; i++) {
				switch ((p_connections + i)->input_pos) {
				case 2:
					//update value in in the connected node connector
					if ((p_connections + i)->connector_node_ptr != NULL) {
						(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p2_c_output);
						//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

void node_blxor::init()
{
	node_blxor::p0_a_input = false;
	node_blxor::p1_b_input = false;
	node_blxor::p2_c_output = false;
	node_blxor::output_updated = true;

}

void node_blxor::load_node_parameters(std::string params)
{

}



void node_blxor::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_blxor::serial_income(std::string message)
{

}

void node_blxor::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value > 0.0f) { p0_a_input = true; }
			 else { p0_a_input = false; }  break;
	case 1: if (value > 0.0f) { p1_b_input = true; }
			else { p1_b_input = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_blxor::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value > 0) { p0_a_input = true; }
			 else { p0_a_input = false; }  break;
	case 1: if (value > 0) { p1_b_input = true; }
			else { p1_b_input = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_blxor::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_a_input = value;  break;
	case 1:  p1_b_input = value;  break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_blxor::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value != "") { p0_a_input = true; }
			 else { p0_a_input = false; }  break;
	case 1: if (value != "") { p1_b_input = true; }
			else { p1_b_input = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;

}









float node_blxor::get_value_f(int position)
{
	switch (position)
	{
	case 0:if (p0_a_input) { return 1.0f; }
		   else { return 0.0f; } break;
	case 1:if (p1_b_input) { return 1.0f; }
		   else { return 0.0f; } break;
	case 2:if (p2_c_output) { return 1.0f; }
		   else { return 0.0f; } break;
	default:
		return -1.0f;
		break;
	}
}

int node_blxor::get_value_i(int position)
{
	switch (position)
	{
	case 0:if (p0_a_input) { return 1; }
		   else { return 0; } break;
	case 1:if (p1_b_input) { return 1; }
		   else { return 0; } break;
	case 2:if (p2_c_output) { return 1; }
		   else { return 0; } break;
	default:
		return -1;
		break;
	}
}

bool node_blxor::get_value_b(int position)
{
	switch (position)
	{
	case 0: return p0_a_input; break;
	case 1: return p1_b_input; break;
	case 2: return p2_c_output; break;
	default:
		return -1.0f;
		break;
	}
}

std::string node_blxor::get_value_s(int position)
{
	switch (position)
	{
	case 0:if (p0_a_input) { return "TRUE"; }
		   else { return "FALSE"; } break;
	case 1:if (p1_b_input) { return "TRUE"; }
		   else { return "FALSE"; } break;
	case 2:if (p2_c_output) { return "TRUE"; }
		   else { return "FALSE"; } break;
	default:
		return "FALSE";
		break;
	}
}
