#pragma once
#include "single_node_include.h"
class node_tstoint : public base_node
{
public:
	node_tstoint(int id, bool us, const int con_count, std::string params, bool is_static);
	~node_tstoint();
	void update(float timestep = 0.0f);
	void init();
	void load_node_parameters(std::string params);
	connector* p_connections;
	int connection_count;
	void  set_connection(int pos, base_node* ptr, int dest_pos);
	virtual void serial_income(std::string message);
	//PARAMS


	//VALUES
	int p0_timestamp_input;

	int p1_day;
	int p2_month;
	int p3_year;
	int p4_seconds;
	int p5_minutes;
	int p6_hour;




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
