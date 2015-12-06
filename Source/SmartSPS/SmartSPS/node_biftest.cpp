#include "node_biftest.h"

node_biftest::node_biftest(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}



node_biftest::~node_biftest()
{
	delete(p_connections);
}

void node_biftest::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;

		//p2_c_output = (p0_a_input & p1_b_input);
		if (p0_toggle_input) {
			p3_value_output = p1_iftrue_input;
		}
		else {
			p3_value_output = p2_ifelse_input;
		}

		std::cout << "update bifte to " << p3_value_output << std::endl;
		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		for (size_t i = 0; i < connection_count; i++) {
			switch ((p_connections + i)->input_pos) {
			case 3:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p3_value_output);
					std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			default:
				break;
			}
		}
	}
}

void node_biftest::init()
{
	node_biftest::p0_toggle_input = false;
	node_biftest::p1_iftrue_input = "";
	node_biftest::p2_ifelse_input = "";
	node_biftest::p3_value_output = "";
}

void node_biftest::load_node_parameters(std::string params)
{

}



void node_biftest::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_biftest::serial_income(std::string message)
{
}

void node_biftest::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value > 1.0f) { p0_toggle_input = true; }
			 else { p0_toggle_input = false; }  break;
	case 1: p1_iftrue_input = value; break;
	case 2: p2_ifelse_input = value; break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_biftest::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value > 0) { p0_toggle_input = true; }
			 else { p0_toggle_input = false; }std::cout << "got update at pos 0 to value " << p0_toggle_input << std::endl;  break;
	case 1: p1_iftrue_input = value; std::cout << "got update at pos 1 to value " << p1_iftrue_input << std::endl; break;
	case 2: p2_ifelse_input = value; std::cout << "got update at pos 2 to value " << p2_ifelse_input << std::endl; break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_biftest::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_toggle_input = value;  break;
	case 1:  if (value) { p1_iftrue_input = 1; }
			 else { p1_iftrue_input = ""; } break;
	case 2:  if (value) { p1_iftrue_input = 1; }
			 else { p1_iftrue_input = ""; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_biftest::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  if (value == "TRUE") { p0_toggle_input = true; }
			 else { p0_toggle_input = false; }  break;
	case 1: p1_iftrue_input = atoi(value.c_str()); break;
	case 2: p2_ifelse_input = atoi(value.c_str()); break;
	default:uv = false; break;
	}
	updated_values = uv;
}









float node_biftest::get_value_f(int position)
{

}

int node_biftest::get_value_i(int position)
{

}

bool node_biftest::get_value_b(int position)
{

}

std::string node_biftest::get_value_s(int position)
{

}
