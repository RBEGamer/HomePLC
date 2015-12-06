#pragma once
#include <deque>
#include <iostream>

class serial_management
{
public:
	serial_management();
	~serial_management();
	static std::deque<std::string> recieve_queue;
	static std::deque<std::string> send_queue;
	static void add_to_send_queue(std::string msg);
	static void add_to_revieved_queue(std::string msg);
	static std::string get_recieved();
	static std::string get_message_to_send();
	static void update();
private:

};

