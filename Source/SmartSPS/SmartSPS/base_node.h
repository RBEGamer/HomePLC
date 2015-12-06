#pragma once
#include <iostream>
#include <cstring>
class base_node
{
public:
	 base_node(int id, bool us, const int con_count, bool is_static);
	 base_node();
	 base_node(int id);
	 virtual ~base_node();
	virtual void update(float timestep = 0.0f);
	virtual void init();
	bool enabled;
	bool updated_values;
	int nid;
	bool is_value_static;
	bool use_serial_recieve;
	virtual void load_node_parameters(std::string params);
	virtual void serial_income(std::string message);
	virtual void  set_connection(int pos, base_node* ptr, int dest_pos);
	virtual void set_value(int position, float value);
	virtual void set_value(int position, int value);
	virtual void set_value(int position, bool value);
	virtual void set_value(int position, std::string value);
	virtual float get_value_f(int position);
	virtual int get_value_i(int position);
	virtual bool get_value_b(int position);
	virtual std::string get_value_s(int position);



private:

};

