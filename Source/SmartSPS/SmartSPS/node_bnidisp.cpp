#include "node_bnidisp.h"



node_bnidisp::node_bnidisp(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}

node_bnidisp::~node_bnidisp()
{
}

void node_bnidisp::update(float timestep)
{
	if (node_bnidisp::updated_values && p0_value_input_state != "") {
		node_bnidisp::updated_values = false;
	
			//SEND TO SERIAL SEND QUARRY -> PORT LOW
			serial_management::add_to_send_queue(mid + "_" + msi + "_" + line + "_" + p0_value_input_state + "\n");
		
	}
}

void node_bnidisp::init()
{
}

void node_bnidisp::load_node_parameters(std::string params)
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
					case 2: line = param_result; break;
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



void node_bnidisp::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_bnidisp::serial_income(std::string message)
{
	//pasres_message
	updated_values = "";
}

void node_bnidisp::set_value(int position, float value)
{

	bool uv = true;
	switch (position)
	{
	case 0: p0_value_input_state = NumberToString((int)value); break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_bnidisp::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_value_input_state = NumberToString(value);
	 break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_bnidisp::set_value(int position, bool value)
{

	bool uv = true;
	switch (position)
	{
	case 0:   if (value) { p0_value_input_state = "TRUE"; }
			  else { p0_value_input_state = "FALSE"; }  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_bnidisp::set_value(int position, std::string value)
{

	bool uv = true;
	switch (position)
	{
	case 0: p0_value_input_state = value; break;


	default:uv = false; break;
	}
	updated_values = uv;
}

float node_bnidisp::get_value_f(int position)
{

}

int node_bnidisp::get_value_i(int position)
{

}

bool node_bnidisp::get_value_b(int position)
{

}

std::string node_bnidisp::get_value_s(int position)
{

}
