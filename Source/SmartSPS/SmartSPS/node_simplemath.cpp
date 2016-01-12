#include "node_simplemath.h"

node_simplemath::node_simplemath(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
	use_timer = ut;
}



node_simplemath::~node_simplemath()
{
	delete(p_connections);
}

void node_simplemath::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;

		if (p0_operation == "add") {
			p2_c_output = p0_a_input + p1_b_input;
		}

		if (p0_operation == "sub") {
			p2_c_output = p0_a_input - p1_b_input;
		}

		if (p0_operation == "mul") {
			p2_c_output = p0_a_input * p1_b_input;
		}

		if (p0_operation == "dif") {
			if (p1_b_input > 0 && p1_b_input != 0) {
				p2_c_output = p0_a_input / p1_b_input;
			}
			else if (p1_b_input == 0 && p0_a_input == 0) {
				p2_c_output = INFINITY;
			}
			
			

			if (p0_operation == "mod") {
				p2_c_output = fmodf(p0_a_input, p1_b_input);
			}
			
			if (p0_operation == "pow") {
				p2_c_output = powf(p0_a_input, p1_b_input);
			}

			if (p0_operation == "min") {
				p2_c_output = fminf(p0_a_input, p1_b_input);
			}

			if (p0_operation == "max") {
				p2_c_output = fmaxf(p0_a_input, p1_b_input);
			}

			if (p0_operation == "dim") {
				p2_c_output = fdimf(p0_a_input, p1_b_input);
			}
		}
		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
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

void node_simplemath::init()
{
	p0_a_input = false;
	p1_b_input = false;
	p2_c_output = false;

}

void node_simplemath::load_node_parameters(std::string params)
{
	//p0_operation
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
					case 0: p0_operation = param_result; break;

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



void node_simplemath::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_simplemath::serial_income(std::string message)
{
}

void node_simplemath::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_a_input = value;  break;
	case 1:	 p1_b_input = value; break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_simplemath::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0:   p0_a_input = value;  break;
	case 1:	p1_b_input = value; break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_simplemath::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value) { p0_a_input = 1.0f; }
			 else { p0_a_input = 0.0f; }  break;
	case 1:  if (value) { p1_b_input = 1.0f; }
			 else { p1_b_input = 0.0f; }  break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_simplemath::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value != "") { p0_a_input = 1.0f; }
			 else { p0_a_input = false; }  break;
	case 1: if (value != "") { p1_b_input = 1.0f; }
			else { p1_b_input = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;
	
}









float node_simplemath::get_value_f(int position)
{

}

int node_simplemath::get_value_i(int position)
{

}

bool node_simplemath::get_value_b(int position)
{

}

std::string node_simplemath::get_value_s(int position)
{

}
