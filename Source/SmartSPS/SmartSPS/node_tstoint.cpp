#include "node_tstoint.h"
#include <sstream>
#include <sys/time.h>
node_tstoint::node_tstoint(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
	use_timer = ut;
}



node_tstoint::~node_tstoint()
{
	delete(p_connections);
}

void node_tstoint::update(float timestep)
{


	//hier serial query abfragen um zu schauen ob der port geupdated wurde


	if (updated_values) {
		updated_values = false;
		std::string tmp = "";
		//p2_c_output = (p0_a_input & p1_b_input);
	
		time_t tt = p0_timestamp_input;
		struct tm * ptm = localtime(&tt);
		char buf[30];
		strftime(buf, 30, "%m:%d:%Y:%H:%M:%S", ptm);
	//	std::cout << buf << std::endl;
		
		const char* start = buf;
		const char* end = strstr(buf, ":");
		tmp.append(start, end);
		p2_month = atoi(tmp.c_str());
		start = end+1;
		end = strstr(start, ":");
		tmp = "";
		tmp.append(start, end);
		p1_day = atoi(tmp.c_str());
		start = end + 1;
		end = strstr(start, ":");
		tmp = "";
		tmp.append(start, end);
		p3_year = atoi(tmp.c_str());
		start = end + 1;
		end = strstr(start, ":");
		tmp = "";
		tmp.append(start, end);
		p6_hour = atoi(tmp.c_str());
		start = end + 1;
		end = strstr(start, ":");
		tmp = "";
		tmp.append(start, end);
		p5_minutes = atoi(tmp.c_str());
		start = end + 1;
		end = strstr(start, ":");
		tmp = "";
		tmp.append(start);
		p4_seconds = atoi(tmp.c_str());

		//free(start);
		//free(end);

		p7_date_string = NumberToString(p1_day) + "." + NumberToString(p2_month) + "." + NumberToString(p3_year);
		p8_time_string = NumberToString(p6_hour) + ":" + NumberToString(p5_minutes);
		p9_time_string_seconds = NumberToString(p6_hour) + ":" + NumberToString(p5_minutes) + ":" + NumberToString(p4_seconds);
		//hier sonst alle weitren node durchgehen //f�r alle nodes di einen ausgansnode besitzen
		for (size_t i = 0; i <connection_count; i++) {
			switch ((p_connections + i)->input_pos) {
			case 1:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p1_day);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;

			case 2:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p2_month);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;

			case 3:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p3_year);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;

			case 4:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p4_seconds);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;

			case 5:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p5_minutes);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;

			case 6:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p6_hour);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			case 7:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p7_date_string);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			case 8:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p8_time_string);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;
			case 9:
				//update value in in the connected node connector
				if ((p_connections + i)->connector_node_ptr != NULL) {
					(p_connections + i)->connector_node_ptr->set_value((p_connections + i)->output_pos, p9_time_string_seconds);
					//std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
				}
				break;

				
			default:
				break;
			}
		}
	}
}

void node_tstoint::init()
{
	node_tstoint::p0_timestamp_input = 0;
	node_tstoint::p1_day = 0;
	node_tstoint::p2_month = 0;
	node_tstoint::p3_year = 0;
	node_tstoint::p4_seconds = 0;
	node_tstoint::p5_minutes = 0;
	node_tstoint::p6_hour = 0;
	node_tstoint::p7_date_string = "";
	node_tstoint::p8_time_string = "";
	node_tstoint::p9_time_string_seconds = "";
	
}

void node_tstoint::load_node_parameters(std::string params)
{

}



void node_tstoint::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_tstoint::serial_income(std::string message)
{
	
}

void node_tstoint::set_value(int position, float value)
{
	bool uv = true;
	switch (position)
	{
	case 0:p0_timestamp_input = value;  break;
	default:uv = false; break;
	}
	updated_values = uv;
	
}

void node_tstoint::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_timestamp_input = value; break;
	default:uv = false; break;
	}
	updated_values = uv;

}

void node_tstoint::set_value(int position, bool value)
{
	bool uv = true;
	switch (position)
	{
	case 0: if (value) { p0_timestamp_input = 1; }
			else { p0_timestamp_input = 0; }  break;
	default:uv = false; break;
	}
	updated_values = uv;
	
}

void node_tstoint::set_value(int position, std::string value)
{
	bool uv = true;
	switch (position)
	{
	case 0:  p0_timestamp_input = atoi(value.c_str()); 
			  break;
	default:uv = false; break;
	}
	updated_values = uv;
	
}









float node_tstoint::get_value_f(int position)
{

}

int node_tstoint::get_value_i(int position)
{
	
}

bool node_tstoint::get_value_b(int position)
{
	
}

std::string node_tstoint::get_value_s(int position)
{
	
}
