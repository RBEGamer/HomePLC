#include "node_intcomp.h"

node_intcomp::node_intcomp(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}



node_intcomp::~node_intcomp()
{
	delete(p_connections);
}

void node_intcomp::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;

		if (comp_node == "==" && p0_input_a == p1_input_b) {
			p3_output = true;
		}else {
			p3_output = false;
		}

		if (comp_node == ">=" && p0_input_a >= p1_input_b) {
			p3_output = true;
		}
		else {
			p3_output = false;
		}

		if (comp_node == "<=" && p0_input_a <= p1_input_b) {
			p3_output = true;
		}
		else {
			p3_output = false;
		}
		
		if (comp_node == "<" && p0_input_a < p1_input_b) {
			p3_output = true;
		}
		else {
			p3_output = false;
		}

		if (comp_node == ">" && p0_input_a > p1_input_b) {
			p3_output = true;
		}
		else {
			p3_output = false;
		}

		if (comp_node == "!=" && p0_input_a != p1_input_b) {
			p3_output = true;
		}
		else {
			p3_output = false;
		}


		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		for (size_t i = 0; i < connection_count; i++) {
			switch ((p_connections + i)->input_pos) {
			case 2:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p3_output);
					std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			default:
				break;
			}
		}
	}
}

void node_intcomp::init()
{
	node_intcomp::p0_input_a = 0;
	node_intcomp::p1_input_b = 0;
	node_intcomp::p3_output = false;
}

void node_intcomp::load_node_parameters(std::string params)
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
					case 0: comp_node = param_result; break;
				
					default:
						break;
					}
					param_counter++;
					start_param = end_param + 1; //remove the %
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



void node_intcomp::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_intcomp::serial_income(std::string message)
{
}

void node_intcomp::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_input_a = value;  break;
	case 1: p1_input_b = value; break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_intcomp::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_input_a = 0;  break;
	case 1:p1_input_b = 0; break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_intcomp::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value) { p0_input_a = 1; }
			 else { p0_input_a = 0; }  break;
	case 1:if (value) { p1_input_b = 1; }
		   else { p1_input_b = 0; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_intcomp::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_input_a = atoi(value.c_str());  break;
	case 1: p1_input_b = atoi(value.c_str()); break;
	default:uv = false; break;
	}
	updated_values = uv;
}









float node_intcomp::get_value_f(int position)
{

}

int node_intcomp::get_value_i(int position)
{

}

bool node_intcomp::get_value_b(int position)
{

}

std::string node_intcomp::get_value_s(int position)
{

}
