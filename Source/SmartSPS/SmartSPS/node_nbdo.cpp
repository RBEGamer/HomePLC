#include "node_nbdo.h"


node_nbdo::node_nbdo(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}

node_nbdo::~node_nbdo()
{
}

void node_nbdo::update(float timestep)
{
	if (node_nbdo::updated_values) {
		node_nbdo::updated_values = false;
		if (node_nbdo::p0_value_input_state) {
			//SEND TO SERIAL SEND QUARRY -> PORT HIGH
			serial_management::add_to_send_queue(mid + "_" + msi + "_set_h_" + gpio_addr + "\n");
		} else {
			//SEND TO SERIAL SEND QUARRY -> PORT LOW
			serial_management::add_to_send_queue(mid + "_" + msi + "_set_l_" + gpio_addr + "\n");
		}
	}
}

void node_nbdo::init()
{
}

void node_nbdo::load_node_parameters(std::string params)
{
	const char* start_param = params.c_str();
	const char* end_param = 0;
	std::string param_result = "";
	int param_counter = 0;
	while (true)
	{
		if (start_param != 0) {
			end_param = strstr(start_param, "%");
			if (end_param != 0) {
				param_result = "";
				param_result.append(start_param, end_param);
				if (param_result != "") {
					//ASSIGN POINTER
					switch (param_counter)
					{
					case 0: mid = param_result; break;
					case 1: msi = param_result; break;
					case 2: gpio_addr = param_result; break;
					default:
						break;
					}
					param_counter++;
					start_param = end_param; //remove the %
					start_param++;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
}



void node_nbdo::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_nbdo::serial_income(std::string message)
{
	//pasres_message
	updated_values = true;
}

void node_nbdo::set_value(int position, float value)
{

	bool uv = true;
	switch (position)
	{
	case 0: if (value > 1.0f) { p0_value_input_state = true; }else { p0_value_input_state = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_nbdo::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0: if (value > 0) { p0_value_input_state = true; }
			else { p0_value_input_state = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_nbdo::set_value(int position, bool value)
{

	bool uv = true;
	switch (position)
	{
	case 0:  p0_value_input_state = value;  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_nbdo::set_value(int position, std::string value)
{

	bool uv = true;
	switch (position)
	{
	case 0: if (value != "") { p0_value_input_state = true; }
			else { p0_value_input_state = false; } break;


	default:uv = false; break;
	}
	updated_values = uv;
}

float node_nbdo::get_value_f(int position)
{
	switch (position)
	{
	case 0:if (p0_value_input_state) { return 1.0f; }
		   else { return 0.0f; } break;
	default:
		return -1.0f;
		break;
	}
}

int node_nbdo::get_value_i(int position)
{
	switch (position)
	{
	case 0:if (p0_value_input_state) { return 1; }
		   else { return 0; } break;
	default:
		return -1;
		break;
	}
}

bool node_nbdo::get_value_b(int position)
{
	switch (position)
	{
	case 0:return p0_value_input_state; break;
	default:
		return -1.0f;
		break;
	}
}

std::string node_nbdo::get_value_s(int position)
{
	switch (position)
	{
	case 0:if (p0_value_input_state) { return "TRUE"; }
		   else { return "FALSE"; } break;
	default:
		return "FALSE";
		break;
	}
}
