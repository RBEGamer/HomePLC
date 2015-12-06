#include "node_phhlux.h"
#include <iostream>


#include <stdio.h>

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


//std::string itoa(int a)
//{
//	std::string ss = "";   //create empty string
//	while (a)
//	{
//		int x = a % 10;
//		a /= 10;
//		char i = '0';
//		i = i + x;
//		ss = i + ss;      //append new character at the front of the string!
//	}
//	return ss;
//}

std::string int_to_string(const int& port) {
	std::stringstream ss;
	ss << port;
	return ss.str();
}
node_phhlux::node_phhlux(int id, bool us, const int con_count, std::string params, bool is_static)
{
	is_value_static = is_static;
	nid = id;
	use_serial_recieve = us;
	connection_count = con_count;
	p_connections = new connector[con_count]();
	load_node_parameters(params);
}

node_phhlux::~node_phhlux()
{
}

void node_phhlux::update(float timestep)
{
	if (updated_values) {
		updated_values = false;
		


		



		std::string cmd = "";
		if (p0_brightnes_input < 0) { p0_brightnes_input = 0; }
		if (p0_brightnes_input > 255) { p0_brightnes_input = 255; }
		if (p0_brightnes_input == 0) {
			cmd = "{\"on\":false";
			cmd.append("}");
		}
		else {
			cmd = "{\"on\":true, \"bri\" : ";
			cmd.append(int_to_string(p0_brightnes_input));
			cmd.append("}");
		}
		std::string ln1 = "PUT /api/";
		ln1.append(username);
		ln1.append("/lights/");
		ln1.append(light_id);
		ln1.append("/state HTTP/1.1\r\nkeep-alive\r\nHost: ");
		ln1.append(ip_address);
		ln1.append("\r\nContent-Length: ");
		ln1.append(int_to_string(cmd.size()));
		ln1.append("\r\nContent-Type: text/plain;charset=UTF-8\r\n\r\n");
		ln1.append(cmd);
		ln1.append("\r\n");


		struct sockaddr_in server;
		struct hostent *host_info;
		in_addr_t addr;
		int sock;
		char buffer[8192];
		int count;


		/* Erzeuge das Socket */
		sock = socket(PF_INET, SOCK_STREAM, 0);
		if (sock < 0) {
			perror("failed to create socket");
			exit(1);
		}

		/* Erzeuge die Socketadresse des Servers
		* Sie besteht aus Typ, IP-Adresse und Portnummer */
		memset(&server, 0, sizeof(server));
		addr = inet_addr(ip_address.c_str());
		if (addr != INADDR_NONE) {
			/* argv[1] ist eine numerische IP-Adresse */
			memcpy((char *)&server.sin_addr, &addr, sizeof(addr));
		}
		else {
			/* Wandle den Servernamen in eine IP-Adresse um */
			host_info = gethostbyname(ip_address.c_str());
			if (NULL == host_info) {
				fprintf(stderr, "unknown server: %s\n", ip_address.c_str());
				exit(1);
			}
			memcpy((char *)&server.sin_addr, host_info->h_addr, host_info->h_length);
		}

		server.sin_family = AF_INET;
		server.sin_port = htons(80);

		/* Baue die Verbindung zum Server auf */
		if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
			perror("can't connect to server");
			exit(1);
		}

		/* Erzeuge und sende den http GET request */
		//	sprintf(buffer, "GET %s HTTP/1.0\r\n\r\n", 80);

		send(sock, ln1.c_str(), ln1.size(), 0);
	//	std::cout << ln1 << std::endl;
		/* Hole die Serverantwort und gib sie auf Konsole aus */
	//	do {
		//	count = recv(sock, buffer, sizeof(buffer), 0);
			//write(1, buffer, count);
		//} while (count > 0)

		/* Schließe Verbindung und Socket */
		closesocket(sock);
		
		std::cout << "update hue lux :" << light_id << " to " << p0_brightnes_input << std::endl;

		
	}
}




void node_phhlux::init()
{
	p0_brightnes_input = 0;
	//updated_values = true;









	//send
}

void node_phhlux::load_node_parameters(std::string params)
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
					case 0: ip_address = param_result; break;
					case 1: username = param_result; break;
					case 2: light_id = param_result; break;
					default:
						break;
					}
					param_counter++;
					start_param = end_param; //remove the %
					start_param++;
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



void node_phhlux::set_connection(int pos, base_node * ptr, int dest_pos)
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
void node_phhlux::serial_income(std::string message)
{
	//pasres_message
	updated_values = true;
}

void node_phhlux::set_value(int position, float value)
{

	bool uv = true;
	switch (position)
	{
	case 0: p0_brightnes_input = value; break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_phhlux::set_value(int position, int value)
{
	bool uv = true;
	switch (position)
	{
	case 0: p0_brightnes_input = value;  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_phhlux::set_value(int position, bool value)
{

	bool uv = true;
	switch (position)
	{
	case 0: if (value) { p0_brightnes_input = 255; }
			else { p0_brightnes_input = 0; }  break;
	default:uv = false; break;
	}
	updated_values = uv;
}

void node_phhlux::set_value(int position, std::string value)
{

	bool uv = true;
	switch (position)
	{
	case 0: if (value == "TRUE") { p0_brightnes_input = 100; }
		   else { p0_brightnes_input = 0; } break;


	default:uv = false; break;
	}
	updated_values = uv;
}

float node_phhlux::get_value_f(int position)
{
	switch (position)
	{
	case 0: return p0_brightnes_input; break;
	default:
		return -1.0f;
		break;
	}
}

int node_phhlux::get_value_i(int position)
{
	switch (position)
	{
	case 0: return p0_brightnes_input; break;
	default:
		return -1;
		break;
	}
}

bool node_phhlux::get_value_b(int position)
{
	switch (position)
	{
	case 0: if (p0_brightnes_input > 0) { return true; }
			else { return false; } break;
	default:
		return -1.0f;
		break;
	}
}

std::string node_phhlux::get_value_s(int position)
{
	
}
