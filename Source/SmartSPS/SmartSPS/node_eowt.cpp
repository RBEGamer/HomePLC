#include "node_eowt.h"

node_eowt::node_eowt(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	//connector con[2];
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
	use_timer = ut;
}



node_eowt::~node_eowt()
{
	delete(p_connections);
}

void node_eowt::update(float timestep)
{

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
						(p_connections + i)->connector_node_ptr->set_value(p_connections[i].output_pos, p0_value_output_state);
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

void node_eowt::init()
{
	p0_value_output_state = -127.0f;
	update();
}

void node_eowt::load_node_parameters(std::string params)
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
					case 2: temp_sensor = param_result; break;
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
	update();
}



void node_eowt::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_eowt::serial_income(std::string message)
{
	//pasres_message
	//0_eqri_0_0 id,msi,channel0,state0-1
	//if (message == mid + "_" + msi + "_" + temp_sensor + "_1\r\n") {


	const char* start = message.c_str();
	if (start == 0) { return; }
	//MID
	const char* end = strstr(start, "_");
	if (end == 0) { return; }
	//MSI
	 end += 1;
	 end = strstr(end, "_");
	 if (end == 0) { return; }
	 end += 1;
	 //TEMP SENSOR ID
	 end = strstr(end, "_");
	 if (end == 0) { return; }

	 std::string result = "";
	 result.append(start, end);
	 if (result != mid + "_" + msi + "_" + temp_sensor) { return; }
	 start = end;
	 start += 1;
	 result = "";
	 result.append(start);
	 if (result == "") { return; }
	 p0_value_output_state = atof(result.c_str());
		updated_values = true;




}

void node_eowt::set_value(int position, float value)
{

}

void node_eowt::set_value(int position, int value)
{

}

void node_eowt::set_value(int position, bool value)
{

}

void node_eowt::set_value(int position, std::string value)
{

}

float node_eowt::get_value_f(int position)
{
	return 0.0f;
}

int node_eowt::get_value_i(int position)
{
	return 0;
}

bool node_eowt::get_value_b(int position)
{
	return false;
}

std::string node_eowt::get_value_s(int position)
{
	return std::string();
}
