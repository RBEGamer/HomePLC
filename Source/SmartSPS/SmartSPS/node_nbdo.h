#pragma once
#include "single_node_include.h"
class node_nbdo : public base_node
{
public:
	node_nbdo(int id, bool us,const int con_count, std::string params, bool is_static);
	~node_nbdo();
	void update(float timestep = 0.0f);
	void init();
	void load_node_parameters(std::string params);
	connector* p_connections;
	int connection_count;
	char parameters[1];
	void  set_connection(int pos, base_node* ptr, int dest_pos);
	virtual void serial_income(std::string message);

	//PARAMS
	std::string gpio_addr;	//param 2
	std::string mid;		//param 0
	std::string msi;		//param 1
	//CONECTION
	bool p0_value_input_state; //pos 0


							
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


