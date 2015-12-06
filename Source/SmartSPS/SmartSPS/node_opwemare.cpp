#include "node_opwemare.h"
/* Headerfiles für Unix/Linux */
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sstream>
#define closesocket(s) close(s)
node_opwemare::node_opwemare(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	//connector con[2];
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);

}





node_opwemare::~node_opwemare()
{
	delete(p_connections);
}

void node_opwemare::update(float timestep)
{

	if (updated_values) {
		updated_values = false;
		//hier sonst alle weitren node durchgehen //für alle nodes di einen ausgansnode besitzen
		//p0_value_output_state = !p0_value_output_state;
		if (p0_value_toggle_state) {
			p1_data_output_state = 	get_openweathermap_data(value_key, city_id, api_key);
			std::cout << "OpenWeatherMap request : " << p1_data_output_state << std::endl;
		}
		for (size_t i = 0; i < connection_count; i++) {
			if ((p_connections + i) != NULL) {
				switch ((p_connections + i)->input_pos) {
				case 1:
					//update value in in the connected node connector
					if ((p_connections + i)->connector_node_ptr != NULL) {
						(p_connections + i)->connector_node_ptr->set_value(p_connections[i].output_pos, p1_data_output_state);
						std::cout << "UPDATE NODE OUTPUT CONNECTION : " << nid << "-" << (p_connections + i)->input_pos << " -> " << (p_connections + i)->connector_node_ptr->nid << "-" << (p_connections + i)->output_pos << std::endl;
					}
					break;

				default:
					break;
				}
			}
		}
	}
}

void node_opwemare::init()
{
	node_opwemare::p1_data_output_state = "";
	node_opwemare::p0_value_toggle_state = true; //DEBUG
}

void node_opwemare::load_node_parameters(std::string params)
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
					case 0: api_key = param_result; break;
					case 1: city_id = param_result; break;
					case 2: value_key = param_result; break;
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
}



void node_opwemare::set_connection(int pos, base_node * ptr, int dest_pos)
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

void node_opwemare::serial_income(std::string message)
{
	


}

std::string node_opwemare::get_openweathermap_data(std::string search_key, std::string city_id, std::string api_key, std::string opm_url)
{
	char result;
	struct sockaddr_in server;
	struct hostent *host_info;
	in_addr_t addr;
	int sock;
	char buffer[8192];
	int count;
	int iResult = 0;
	
	/* Erzeuge das Socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		return "";
		exit(1);
	}

	/* Erzeuge die Socketadresse des Servers
	* Sie besteht aus Typ, IP-Adresse und Portnummer */
	memset(&server, 0, sizeof(server));
	addr = inet_addr(opm_url.c_str());
	if (addr != INADDR_NONE) {
		/* argv[1] ist eine numerische IP-Adresse */
		memcpy((char *)&server.sin_addr, &addr, sizeof(addr));
	}
	else {
		/* Wandle den Servernamen in eine IP-Adresse um */
		host_info = gethostbyname(opm_url.c_str());
		if (NULL == host_info) {
			return "";

		}
		memcpy((char *)&server.sin_addr, host_info->h_addr, host_info->h_length);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	/* Baue die Verbindung zum Server auf */
	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
		return "";

	}



	std::string ln1 = "GET /data/2.5/weather?id=";
	ln1.append(city_id);
	ln1.append("&appid=");
	ln1.append(api_key);
	ln1.append(" HTTP/1.0\r\nHost: ");
	ln1.append(opm_url);
	ln1.append("\r\nAccept: text/json\r\n\r\n");




	char recvbuf1[4096];
	int recvbuflen1 = 4096;
	int rf = 0;


	iResult = send(sock, ln1.c_str(), ln1.size(), 0);

	int end = -1;
	int flen = -1;
	std::string str1 = "";
	int contentSize = 0;
	while (true)
	{
		rf = recv(sock, recvbuf1, recvbuflen1, 0);
		if (end == -1) {
			contentSize += rf;
			str1 += recvbuf1;
			end = str1.find("\r\n\r\n"); //data begin
			if (end != -1)
			{
				end += 4;
				char* start_content_key = strstr(recvbuf1, "Content-Length:") + 15; //cl begin
				char* end_content_key = strstr(start_content_key, "\r\n"); //cl end
				std::string clen;
				clen.append(start_content_key, end_content_key);
				flen = atoi(clen.c_str());
				int s = str1.size();
				int off = rf - (contentSize - end);
				contentSize = rf - off;
			}
		}
		else {
			int size = std::min(rf, flen - contentSize);
			contentSize += size;
			if (contentSize >= flen) { break; };
		}
	}



	closesocket(sock);



	const char* start_param = str1.c_str();
	const char* end_param = 0;
	std::string param_result = "";
	std::string key_string = "\"" + search_key + "\":"; //<- needed for size
	std::string end_json_string = "\"id\":" + city_id;
	if (start_param != 0) {
		start_param = strstr(str1.c_str(), "\r\n\r\n");
		start_param += 4;
		end_param = strstr(start_param, end_json_string.c_str());
		if (end_param != 0) {
			param_result = "";
			param_result.append(start_param, end_param);
			//param_result = complete json weather string
			start_param = param_result.c_str();
			start_param = strstr(start_param, key_string.c_str());
			if (start_param != 0) {
				start_param += key_string.size();
				//start += length
				end_param = strstr(start_param, ",");
				if (end_param != 0) {
					param_result = "";
					param_result.append(start_param, end_param);
					//removemthe }
					start_param = param_result.c_str();
					start_param = strstr(start_param, "}");
					if (start_param != 0) {
						std::string fr = "";
						fr.append(param_result.c_str(), start_param);
						param_result = fr;

						return param_result;
					}
					else {
						//FINAL STRING
						return param_result;
					}
				}
			}
		}
	}
	return "";
}

void node_opwemare::set_value(int position, float value)
{

	bool uv = true;
	switch (position)
	{
	case 0: if (value > 1.0f) { p0_value_toggle_state = true; }
			else { p0_value_toggle_state = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_opwemare::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0: if (value > 0) { p0_value_toggle_state = true; }
			else { p0_value_toggle_state = false; } break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_opwemare::set_value(int position, bool value)
{

	bool uv = true;
	switch (position)
	{
	case 0:  p0_value_toggle_state = value;  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_opwemare::set_value(int position, std::string value)
{

	bool uv = true;
	switch (position)
	{
	case 0: if (value != "") { p0_value_toggle_state = true; }
			else { p0_value_toggle_state = false; } break;


	default:uv = false; break;
	}
	updated_values = uv;
}

float node_opwemare::get_value_f(int position)
{
	switch (position)
	{
	case 0:if (p0_value_toggle_state) { return 1.0f; }
		   else { return 0.0f; } break;
	default:
		return -1.0f;
		break;
	}
}

int node_opwemare::get_value_i(int position)
{
	switch (position)
	{
	case 0:if (p0_value_toggle_state) { return 1; }
		   else { return 0; } break;
	default:
		return -1;
		break;
	}
}

bool node_opwemare::get_value_b(int position)
{
	switch (position)
	{
	case 0:return p0_value_toggle_state; break;
	default:
		return -1.0f;
		break;
	}
}

std::string node_opwemare::get_value_s(int position)
{
	switch (position)
	{
	case 0:if (p0_value_toggle_state) { return "TRUE"; }
		   else { return "FALSE"; } break;
	default:
		return "FALSE";
		break;
	}
}
