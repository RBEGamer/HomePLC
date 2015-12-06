#include "base_node.h"


base_node::base_node(int id, bool us, const int con_count, bool is_static)
{
	nid = id;
	use_serial_recieve = us;
	is_value_static = is_static;
}

base_node::base_node() {
	nid = -1;
}


 base_node::base_node(int id)
{
	nid = id;
	enabled = true;
}

base_node::~base_node()
{
}

void base_node::update(float timestep)
{
}

void base_node::init()
{
}

void base_node::load_node_parameters(std::string params)
{
}

void base_node::serial_income(std::string message)
{
}


void base_node::set_connection(int pos, base_node * ptr, int dest_pos)
{
}

void base_node::set_value(int position, float value)
{
}

void base_node::set_value(int position, int value)
{
}

void base_node::set_value(int position, bool value)
{
}

void base_node::set_value(int position, std::string value)
{
}

float base_node::get_value_f(int position)
{
	return 0.0f;
}

int base_node::get_value_i(int position)
{
	return 0;
}

bool base_node::get_value_b(int position)
{
	return false;
}

std::string base_node::get_value_s(int position)
{
	return std::string();
}

