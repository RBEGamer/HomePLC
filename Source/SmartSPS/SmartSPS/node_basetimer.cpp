#include "node_basetimer.h"

node_basetimer::node_basetimer(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}



node_basetimer::~node_basetimer()
{
	delete(p_connections);
}

void node_basetimer::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde
	if (p5_running_output && timestep > 0.0f) {
		if (p4_outtime_output <= 0.0f) {
			p5_running_output = false;
			p4_outtime_output = 0.0f;
			updated_values = true;
			running_state_updated = true;
		}else {
			p4_outtime_output -= timestep;
			if (p4_outtime_output < 0.0f) { p4_outtime_output = 0.0f; }
			updated_values = true;
		}
	}
	//std::cout << "Timer value" << p4_outtime_output << std::endl;
	if (updated_values) {
		updated_values = false;

		


		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		for (size_t i = 0; i < connection_count; i++) {
			switch ((p_connections + i)->input_pos) {
			case 4:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p4_outtime_output);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;

			case 5:
				if (running_state_updated) {
					//update value in in the connected node connector
					if ((p_connections + i)->connector_node_ptr != NULL) {
						(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p5_running_output);
						//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
					}
				
				}
				break;
			default:
				break;
			}
		}
		running_state_updated = false;
	}
}

void node_basetimer::init()
{
	
	p0_interval_input = 0.0f;
	p1_start_input = false;
	p2_stop_input = false;
	p3_reset_input = false;

	p4_outtime_output = 0.0f;
	p5_running_output = false;
	running_state_updated = false;
}

void node_basetimer::load_node_parameters(std::string params)
{

}



void node_basetimer::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_basetimer::serial_income(std::string message)
{
}

void node_basetimer::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_interval_input = value; p4_outtime_output = p0_interval_input; break;

	case 1: if (value > 0.0f) {
		p1_start_input = true; p5_running_output = true; running_state_updated = true; if (p4_outtime_output <= 0.0f) { p4_outtime_output = p0_interval_input; }
	}else { p1_start_input = false; } break;

	case 2: if (value > 0.0f) {
		p2_stop_input = true; p5_running_output = false; running_state_updated = true;
	}else { p2_stop_input = false; } break;

	case 3: if (value > 0.0f) {
		p3_reset_input = true; p4_outtime_output = 0.0f;
	}else { p3_reset_input = false; } break;

	default:uv = false; break;
	}
	updated_values = uv;
}

void node_basetimer::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_interval_input = value; p4_outtime_output = p0_interval_input; break;

	case 1: if (value > 0) {
		p1_start_input = true; p5_running_output = true; running_state_updated = true; if (p4_outtime_output <= 0.0f) { p4_outtime_output = p0_interval_input; }
	}
			else { p1_start_input = false; } break;

	case 2: if (value > 0) {
		p2_stop_input = true; p5_running_output = false; running_state_updated = true;
	}
			else { p2_stop_input = false; } break;

	case 3: if (value > 0) {
		p3_reset_input = true; p4_outtime_output = 0.0f;
	}
			else { p3_reset_input = false; } break;

	default:uv = false; break;
	}
	updated_values = uv;
}

void node_basetimer::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0: if (value) { p0_interval_input = 1.0f; p4_outtime_output = p0_interval_input;
	}
			else { p0_interval_input = 0.0f; } break;

	case 1: if (value) {
		p1_start_input = true; p5_running_output = true; running_state_updated = true; if (p4_outtime_output <= 0.0f) { p4_outtime_output = p0_interval_input; }
	}
			else { p1_start_input = false; } break;

	case 2: if (value) {
		p2_stop_input = true; p5_running_output = false; running_state_updated = true;
	}
			else { p2_stop_input = false; } break;

	case 3: if (value) {
		p3_reset_input = true; p4_outtime_output = 0.0f;
	}
			else { p3_reset_input = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_basetimer::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_interval_input = atoi(value.c_str()); p4_outtime_output = p0_interval_input; break;

	case 1: if (value == "TRUE") {
		p1_start_input = true; p5_running_output = true; running_state_updated = true; if (p4_outtime_output <= 0.0f) { p4_outtime_output = p0_interval_input; }
	}
			else { p1_start_input = false; } break;

	case 2: if (value == "TRUE") {
		p2_stop_input = true; p5_running_output = false; running_state_updated = true;
	}
			else { p2_stop_input = false; } break;

	case 3: if (value == "TRUE") {
		p3_reset_input = true; p4_outtime_output = 0.0f;
	}
			else { p3_reset_input = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}









float node_basetimer::get_value_f(int position)
{

}

int node_basetimer::get_value_i(int position)
{

}

bool node_basetimer::get_value_b(int position)
{

}

std::string node_basetimer::get_value_s(int position)
{

}
