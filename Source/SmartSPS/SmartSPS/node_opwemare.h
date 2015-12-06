#pragma once
#include "single_node_include.h"
class node_opwemare : public base_node
{
public:
	node_opwemare(int id, bool us, const int con_count, std::string params, bool is_static);
	~node_opwemare();
	void update(float timestep = 0.0f);
	void init();
	void load_node_parameters(std::string params);
	connector* p_connections;
	int connection_count;
	void  set_connection(int pos, base_node* ptr, int dest_pos);
	virtual void serial_income(std::string message);
	std::string get_openweathermap_data(std::string search_key, std::string city_id, std::string api_key, std::string opm_url = "api.openweathermap.org");
	//PARAMS
	std::string api_key;	//param 2
	std::string city_id;		//param 0
	std::string value_key;		//param 1

							//VALUES
	bool p0_value_toggle_state; //pos 0
	std::string p1_data_output_state;




	void set_value(int position, float value);
	void set_value(int position, int value);
	void set_value(int position, bool value);
	void set_value(int position, std::string value);

	float get_value_f(int position);
	int get_value_i(int position);
	bool get_value_b(int position);
	std::string get_value_s(int position);

private:

};

