#include "node_nbcobof.h"

node_nbcobof::node_nbcobof(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}



node_nbcobof::~node_nbcobof()
{
	delete(p_connections);
}

void node_nbcobof::update(float timestep)
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
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, false);
					std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			default:
				break;
			}
		}
	}
}

void node_nbcobof::init()
{

}

void node_nbcobof::load_node_parameters(std::string params)
{

}



void node_nbcobof::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_nbcobof::serial_income(std::string message)
{
}

void node_nbcobof::set_value(int position, float value)
{

}

void node_nbcobof::set_value(int position, int value)
{

}

void node_nbcobof::set_value(int position, bool value)
{

}

void node_nbcobof::set_value(int position, std::string value)
{

}









float node_nbcobof::get_value_f(int position)
{

}

int node_nbcobof::get_value_i(int position)
{

}

bool node_nbcobof::get_value_b(int position)
{

}

std::string node_nbcobof::get_value_s(int position)
{

}
