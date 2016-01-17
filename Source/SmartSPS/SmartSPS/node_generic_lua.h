#pragma once
#include "single_node_include.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
class node_generic_lua : public base_node
{
public:
	node_generic_lua(int id, bool us, const int con_count, std::string params, bool is_static, bool ut);
	~node_generic_lua();
	void update(float timestep = 0.0f);
	void init();
	void load_node_parameters(std::string params);
	connector* p_connections;
	int connection_count;
	void  set_connection(int pos, base_node* ptr, int dest_pos);
	virtual void serial_income(std::string message);
	//PARAMS
	std::string filepath;
	std::string input_param_string;		//param 1
	std::string output_param_string;		//param 2

							//VALUES
	bool p0_value_output_state; //pos 0

	lua_State* L;

	int lua_variable_amount;

	enum lua_variable_type
	{
		 _input, _output
	};

	enum lua_variable_datatype
	{
		 _bool, _string, _float, _int
	};
	struct lua_variable
	{
		int position;
		lua_variable_type var_type;
		lua_variable_datatype vat_dtype;
		std::string lua_variable_name;

	};

	lua_variable* lua_variables;

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

