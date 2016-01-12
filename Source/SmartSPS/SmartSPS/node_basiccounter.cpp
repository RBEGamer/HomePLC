#include "node_basiccounter.h"

node_basiccounter::node_basiccounter(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
	use_timer = ut;
}



node_basiccounter::~node_basiccounter()
{
	delete(p_connections);
}

void node_basiccounter::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;

		


		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		for (size_t i = 0; i < connection_count; i++) {
			switch ((p_connections + i)->input_pos) {
			case 3:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p3_counterout_output);
					std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			default:
				break;
			}
		}
	}
}

void node_basiccounter::init()
{
	p0_toggle_input = false;
	p1_incvalue_input = 0.0f;
	p2_setzero_input = 0.0f;
	p3_counterout_output = 0.0f;
	counter_last_state = true;
	
}

void node_basiccounter::load_node_parameters(std::string params)
{

}



void node_basiccounter::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_basiccounter::serial_income(std::string message)
{

}


void node_basiccounter::set_value(int position, float value)
{

}

void node_basiccounter::set_value(int position, int value)
{

}

void node_basiccounter::set_value(int position, bool value)
{

}

void node_basiccounter::set_value(int position, std::string value)
{

}









float node_basiccounter::get_value_f(int position)
{

}

int node_basiccounter::get_value_i(int position)
{

}

bool node_basiccounter::get_value_b(int position)
{

}

std::string node_basiccounter::get_value_s(int position)
{

}
