#include "node_ctimest.h"
#include <sys/time.h>
#include <stdio.h>
#include <sstream>
node_ctimest::node_ctimest(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	//connector con[2];
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);

}



node_ctimest::~node_ctimest()
{
	delete(p_connections);
}

void node_ctimest::update(float timestep)
{


	struct timeval tv;
	gettimeofday(&tv, NULL);
	//printf("Seconds since Jan. 1, 1970: %ld\n", tv.tv_sec);
	p0_curr_timestamp_output = tv.tv_sec;

	
	if (p0_curr_timestamp_output != saved_timestamp) {
	//	std::cout << "CURRENT TIMESTAMP" << p0_curr_timestamp_output << std::endl;
		updated_values = true;
		saved_timestamp = p0_curr_timestamp_output;
	}


 
	if (updated_values) {
		updated_values = false;





	
		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		//p0_value_output_state = !p0_value_output_state;
		for (size_t i = 0; i < connection_count; i++) {
			if ((p_connections + i) != NULL) {
				switch ((p_connections + i)->input_pos) {
				case 0:
					//update value in in the connected node connector
					if ((p_connections + i)->connector_node_ptr != NULL) {
						(p_connections + i)->connector_node_ptr->set_value(p_connections[i].output_pos, p0_curr_timestamp_output);
						std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
					}
					break;

				default:
					break;
				}
			}
		}
	}
}

void node_ctimest::init()
{
	p0_curr_timestamp_output = 0;
	saved_timestamp = -1;
}

void node_ctimest::load_node_parameters(std::string params)
{
	
}



void node_ctimest::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_ctimest::serial_income(std::string message)
{
	


}

void node_ctimest::set_value(int position, float value)
{
}

void node_ctimest::set_value(int position, int value)
{
}

void node_ctimest::set_value(int position, bool value)
{
}

void node_ctimest::set_value(int position, std::string value)
{
}

float node_ctimest::get_value_f(int position)
{
	return 0.0f;
}

int node_ctimest::get_value_i(int position)
{
	return 0;
}

bool node_ctimest::get_value_b(int position)
{
	return false;
}

std::string node_ctimest::get_value_s(int position)
{
	return std::string();
}
