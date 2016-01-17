#include "node_generic_lua.h"



node_generic_lua::node_generic_lua(int id, bool us, const int con_count, std::string params, bool is_static, bool ut)
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



node_generic_lua::~node_generic_lua()
{
	lua_close(L);
	delete(p_connections);
	delete(lua_variables);
	delete(L);
}

void node_generic_lua::update(float timestep)
{

	//CALL UPDATE WITH TIMESTEMP
	lua_getglobal(L, "update");
	if (!lua_isfunction(L, -1))
	{
		lua_pop(L, 1);
		std::cout << "cant update update function in lua script" << std::endl;
		return;
	}
	lua_pushnumber(L, timestep); //push timestep
	if (lua_pcall(L, 1, 0, 0) != 0) {
		printf("error running function `f': %s\n", lua_tostring(L, -1));
		return;
	}
	lua_pop(L, 1);




	for (size_t j = 0; j < lua_variable_amount; j++)
	{
		if (lua_variables[j].var_type != _output) { continue; }

		lua_getglobal(L, lua_variables[j].lua_variable_name.c_str());

		float fv_float = 0.0f;
		bool fv_bool = false;
		std::string fv_string = std::string("");
		int fv_int  = 0;

		if (lua_variables[j].vat_dtype == _int) {fv_int = lua_tonumber(L, -1);}
		if (lua_variables[j].vat_dtype == _float) { fv_float = lua_tonumber(L, -1); }
		if (lua_variables[j].vat_dtype == _bool) { fv_bool = lua_isboolean(L, -1); }
		if (lua_variables[j].vat_dtype == _string) { fv_string = lua_tostring(L, -1); }


	
		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		//p0_value_output_state = !p0_value_output_state;
		for (size_t i = 0; i < connection_count; i++) {
			if ((p_connections + i) != NULL) {
					if ((p_connections + i)->input_pos != lua_variables[j].position) { continue; }
					//update value in in the connected node connector
					if ((p_connections + i)->connector_node_ptr != NULL) {
						if (lua_variables[j].vat_dtype == _int) {
							(p_connections + i)->connector_node_ptr->set_value(p_connections[i].output_pos, fv_int);
						}else if (lua_variables[j].vat_dtype == _float) {
							(p_connections + i)->connector_node_ptr->set_value(p_connections[i].output_pos, fv_float);
						}else if (lua_variables[j].vat_dtype == _bool) {
							(p_connections + i)->connector_node_ptr->set_value(p_connections[i].output_pos, fv_bool);
						}else if (lua_variables[j].vat_dtype == _string) {
							(p_connections + i)->connector_node_ptr->set_value(p_connections[i].output_pos, fv_string);
						}
						
					}

			}
		}
		lua_pop(L, 1);
	}


	
}

void node_generic_lua::init()
{
	node_generic_lua::p0_value_output_state = false;
	

	//INIT LUA 
	L = { 0 };
	L = luaL_newstate();
	lua_newtable(L);
	luaL_openlibs(L);
	if (luaL_loadfile(L, filepath.c_str()) || lua_pcall(L, 0, 0, 0)) {
		printf("error: %s", lua_tostring(L, -1));
		
	}

	//CALL THE INIT FUNCTION
	lua_getglobal(L, "start");
	if (!lua_isfunction(L, -1))
	{
lua_pop(L, 1);
return;
	}
	if (lua_pcall(L, 0, 0, 0) != 0) {
		printf("error running function `f': %s\n", lua_tostring(L, -1));
		return;
	}
	lua_pop(L, 1);


}

void node_generic_lua::load_node_parameters(std::string params)
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
					case 0: filepath = param_result;
					case 1: lua_variable_amount = atoi(param_result.c_str()); break;
					case 2: input_param_string = param_result; break;
					case 3: output_param_string = param_result; break;
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



	//PARSE THE SHIT
	
	lua_variables = new lua_variable[lua_variable_amount]();

	//PARSE VARIABLE STRING
	//[0,string,counter];[1,int,output]
	if (input_param_string != "" || input_param_string != "%") {







	}

	//1. nach ; splitten
	//substring die [] entfernen
	//nach , splitten
	
	// 0 pos
	//1 type
	//2 name

	lua_variables[0].position = 0;
	lua_variables[0].var_type = _input;
	lua_variables[0].vat_dtype = _float;
	lua_variables[0].lua_variable_name = std::string("input");


	lua_variables[1].position = 0;
	lua_variables[1].var_type = _output;
	lua_variables[1].vat_dtype = _string;
	lua_variables[1].lua_variable_name = std::string("output");


	update();
}



void node_generic_lua::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_generic_lua::serial_income(std::string message)
{

	lua_getglobal(L, "serial_recieve");
	if (!lua_isfunction(L, -1))
	{
		lua_pop(L, 1);
		return;
	}
	lua_pushstring(L, message.c_str()); //push income message
	if (lua_pcall(L, 1, 0, 0) != 0) {
		printf("error running function `f': %s\n", lua_tostring(L, -1));
		return;
	}
	lua_pop(L, 1);

}

void node_generic_lua::set_value(int position, float value)
{
	bool uv = false;
	for (size_t i = 0; i < lua_variable_amount; i++)
	{
		if(lua_variables[i].position == position && lua_variables[i].var_type ==_input){
			if (lua_variables[i].vat_dtype == _float) {
				lua_pushnumber(L, value);
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}else if (lua_variables[i].vat_dtype == _int) {
				lua_pushnumber(L, value);
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}else if (lua_variables[i].vat_dtype == _string) {
				lua_pushstring(L, NumberToString(value).c_str());
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}else if (lua_variables[i].vat_dtype == _bool) {
				if (value > 0.0f) { lua_pushboolean(L, true); }else { lua_pushboolean(L, false); }
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);	
				uv = true;
			}
		}
	}
	updated_values = updated_values | uv;
}

void node_generic_lua::set_value(int position, int value)
{
	bool uv = false;
	for (size_t i = 0; i < lua_variable_amount; i++)
	{
		if (lua_variables[i].position == position && lua_variables[i].var_type == _input) {
			if (lua_variables[i].vat_dtype == _float) {
				lua_pushnumber(L, value);
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _int) {
				lua_pushnumber(L, value);
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _string) {
				lua_pushstring(L, NumberToString(value).c_str());
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _bool) {
				if (value > 0.0f) { lua_pushboolean(L, true); }
				else { lua_pushboolean(L, false); }
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
		}
	}
	updated_values = updated_values | uv;
}

void node_generic_lua::set_value(int position, bool value)
{
	bool uv = false;
	for (size_t i = 0; i < lua_variable_amount; i++)
	{
		if (lua_variables[i].position == position && lua_variables[i].var_type == _input) {
			if (lua_variables[i].vat_dtype == _float) {
				if (value) { lua_pushnumber(L, 1.0f); }else{ lua_pushnumber(L, 0.0f); }
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _int) {
				if (value) { lua_pushnumber(L, 1); }
				else { lua_pushnumber(L, 0); }
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _string) {
				if (value) { lua_pushstring(L, "TRUE"); }
				else { lua_pushstring(L, "FALSE"); }
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _bool) {
				 lua_pushboolean(L, value); 
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
		}
	}
	updated_values = updated_values | uv;
}

void node_generic_lua::set_value(int position, std::string value)
{
	bool uv = false;
	for (size_t i = 0; i < lua_variable_amount; i++)
	{
		if (lua_variables[i].position == position && lua_variables[i].var_type == _input) {
			if (lua_variables[i].vat_dtype == _float) {
				if (value != "") { lua_pushnumber(L, 1.0f); }
				else { lua_pushnumber(L, 0.0f); }
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _int) {
				if (value != "") { lua_pushnumber(L, 1); }
				else { lua_pushnumber(L, 0); }
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _string) {
			lua_pushstring(L, value.c_str());
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
			else if (lua_variables[i].vat_dtype == _bool) {
				if (value != "") { lua_pushnumber(L, true); }
				else { lua_pushnumber(L, false); }
				lua_getglobal(L, lua_variables[i].lua_variable_name.c_str());
				lua_pop(L, 1);
				uv = true;
			}
		}
	}
	updated_values = updated_values | uv;
}





float node_generic_lua::get_value_f(int position)
{
	return 0.0f;
}

int node_generic_lua::get_value_i(int position)
{
	return 0;
}

bool node_generic_lua::get_value_b(int position)
{
	return false;
}

std::string node_generic_lua::get_value_s(int position)
{
	return std::string();
}
