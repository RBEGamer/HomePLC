#pragma once
#include "single_node_include.h"
class node_nbsttof : public base_node
{
public:
	node_nbsttof(int id, bool us, const int con_count, std::string params, bool is_static, bool ut);
	~node_nbsttof();
	void update(float timestep = 0.0f);
	void init();
	void load_node_parameters(std::string params);
	connector* p_connections;
	int connection_count;
	void  set_connection(int pos, base_node* ptr, int dest_pos);
	virtual void serial_income(std::string message);
	//PARAMS


	//VALUES
	std::string p0_a_input; //pos 0
	int p1_b_output;




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
