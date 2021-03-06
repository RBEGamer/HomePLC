#include "node_strcomp.h"

node_strcomp::node_strcomp(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
	use_timer = ut;
}



node_strcomp::~node_strcomp()
{
	delete(p_connections);
}

void node_strcomp::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;
		p3_output = false;
		if (comp_node == "==" && p0_input_a == p1_input_b) {
			p3_output = true;
		}
	

		if (comp_node == "!=" && p0_input_a != p1_input_b) {
			p3_output = true;
		}
		
		if (comp_node == ">" && p0_input_a.size() > p1_input_b.size()) {
			p3_output = true;
		}
		if (comp_node == ">=" && p0_input_a.size() >= p1_input_b.size()) {
			p3_output = true;
		}
		
		if (comp_node == "<" && p0_input_a.size() < p1_input_b.size()) {
			p3_output = true;
		}

		if (comp_node == "<" && p0_input_a.size() <= p1_input_b.size()) {
			p3_output = true;
		}
		if (last_p3_output != p3_output) {
			last_p3_output = p3_output;
			//hier sonst alle weitren node durchgehen //f�r alle nodes di einen ausgansnode besitzen
			for (size_t i = 0; i < connection_count; i++) {
				switch ((p_connections + i)->input_pos) {
				case 3:
					//update value in in the connected node connector
					if ((p_connections + i)->connector_node_ptr != NULL) {
						(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p3_output);
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

void node_strcomp::init()
{
	node_strcomp::p0_input_a = "";
	node_strcomp::p1_input_b = "";
	node_strcomp::p3_output = false;
	node_strcomp::last_p3_output = false;

}

void node_strcomp::load_node_parameters(std::string params)
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



void node_strcomp::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_strcomp::serial_income(std::string message)
{

}

void node_strcomp::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value > 0) { p0_input_a = "TRUE"; }
			 else { p0_input_a = "FALSE"; }  break;
	case 1:if (value > 0) { p1_input_b = "TRUE"; }
		   else { p1_input_b = "FALSE"; } break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_strcomp::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value > 0) { p0_input_a = "TRUE"; }
			 else { p0_input_a = "FALSE"; }  break;
	case 1:if (value > 0) { p1_input_b = "TRUE"; }
		   else { p1_input_b = "FALSE"; } break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_strcomp::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value) { p0_input_a = "TRUE"; }
			 else { p0_input_a = "FALSE"; }  break;
	case 1:if (value) { p1_input_b = "TRUE"; }
		   else { p1_input_b = "FALSE"; } break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_strcomp::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_input_a = value;  break;
	case 1: p1_input_b = value; break;
	default:uv = false; break;
	}
	updated_values = uv;

}









float node_strcomp::get_value_f(int position)
{

}

int node_strcomp::get_value_i(int position)
{

}

bool node_strcomp::get_value_b(int position)
{

}

std::string node_strcomp::get_value_s(int position)
{

}
