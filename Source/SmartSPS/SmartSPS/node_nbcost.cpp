#include "node_nbcost.h"

node_nbcost::node_nbcost(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}



node_nbcost::~node_nbcost()
{
	delete(p_connections);
}

void node_nbcost::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;

		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		for (size_t i = 0; i < connection_count; i++) {
			switch ((p_connections + i)->input_pos) {
			case 0:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, const_int_value);
					std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			default:
				break;
			}
		}
	}
}

void node_nbcost::init()
{

}

void node_nbcost::load_node_parameters(std::string params)
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
					case 0: const_int_value =param_result.c_str(); break;
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



void node_nbcost::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_nbcost::serial_income(std::string message)
{
}

void node_nbcost::set_value(int position, float value)
{

}

void node_nbcost::set_value(int position, int value)
{

}

void node_nbcost::set_value(int position, bool value)
{

}

void node_nbcost::set_value(int position, std::string value)
{

}









float node_nbcost::get_value_f(int position)
{

}

int node_nbcost::get_value_i(int position)
{

}

bool node_nbcost::get_value_b(int position)
{

}

std::string node_nbcost::get_value_s(int position)
{

}
