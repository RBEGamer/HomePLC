#include "serial_management.h"


serial_management::serial_management()
{
	
}

serial_management::~serial_management()
{
}

void serial_management::add_to_send_queue(std::string msg)
{
	if (msg != "") {
		serial_management::send_queue.push_back(msg);
		std::cout << "message to output queue send" << std::endl;
	}
}

void serial_management::add_to_revieved_queue(std::string msg)
{
	if (msg != "") {
		serial_management::recieve_queue.push_back(msg);
		std::cout << "message to input queue send" << std::endl;
	}
}

std::string serial_management::get_recieved()
{
	std::string tmp = "";
	if (!serial_management::recieve_queue.empty()) {
		tmp = serial_management::recieve_queue.front();
		serial_management::recieve_queue.pop_front();
	}
	return tmp;
}

std::string serial_management::get_message_to_send()
{
	std::string tmp = "";
	if (!serial_management::send_queue.empty()) {
		tmp = serial_management::send_queue.front();
		serial_management::send_queue.pop_front();
	//	std::cout << "front : " << tmp << std::endl;
	}
	return tmp;
}

void serial_management::update()
{
	//DO SEND AND REVIEVE STUFF HERE
}


