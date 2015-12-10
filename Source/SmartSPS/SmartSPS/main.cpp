

#if defined(_LINUX_)
#include <iostream>
#include <ctime> //timer class 
#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <string>
#include <unistd.h>
#include<netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define closesocket(s) close(s)
#include <math.h>


#endif


#if defined(_WIN_)
#include <iostream>
#include <windows.h>
#endif





#if defined(_MAC_)
#endif

#include "main_node_include.h"





//INIT STATIC VARIABLES
std::deque<std::string> serial_management::recieve_queue = std::deque<std::string>();
std::deque<std::string> serial_management::send_queue = std::deque<std::string>();
int uart0_filestream = -1;
serialib LS;                                                            // Object of the serialib class
int Ret;             //returns the recieved serial chars                                                   // Used for return values
char Buffer[128]; //for the serial recieve
base_node** nodes_buffer;
int end_loop_ticks = 0;
int start_loop_ticks = 0;
float average_delta_time = 0.0f;
float delta_time = 0.0f; //current updatetime in loop
bool break_update_cycle = false; //if false the programm exits
float serial_update_timer = 0.0f;
float serial_update_timer_max = 0.9f; //check for serial updates all
std::string* connection_string;//holds all connection inforamtion
std::stringstream ss;


size_t getTotalSystemMemory()
{
#if defined(_LINUX_)
	long pages = sysconf(_SC_PHYS_PAGES);
	long page_size = sysconf(_SC_PAGE_SIZE);
	return pages * page_size;
#endif
#if defined(_WIN_)
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys;
#endif
}

std::string request_schematic() {
std::cout << "STARTIC DOWNLOADING NEWEST SCHEMATIC VERSION" << std::endl;
	char result;
	struct sockaddr_in server;
	struct hostent *host_info;
	in_addr_t addr;
	int sock;
	char buffer[256];
	int count;

	int iResult = 0;
	std::string opm_url = "localhost";
	std::string ret_str = "";
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



	std::string ln1 = "GET /test.html";
	ln1.append(" HTTP/1.0\r\nHost: ");
	ln1.append(opm_url);
	ln1.append("\r\nAccept: text/html\r\n\r\n");




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
				//ret_str += (recvbuf1 + off);
			}
		}
		else {
			int size = std::min(rf, flen - contentSize);
			contentSize += size;
			//ret_str.append(&recvbuf1+flen - size, recvbuf1);
			if (contentSize >= flen) { break; };
		}
	}

	closesocket(sock);


	char* _start_content_key = strstr(recvbuf1, "\r\n\r\n") +4;
	ret_str.append(_start_content_key);
	return ret_str;
	

}

namespace xml_parser {

	//CHECK PASSED---------------------------------------------------------
	//get the versionstring of the start of the xml file
	std::string get_xml_version(const std::string xml_input) {
		std::string final_xml_version_string = "";
		const char *xml_version_string_begin = strstr(xml_input.c_str(), "<?xml ");
		if (xml_version_string_begin != 0) { //if
			xml_version_string_begin += 6; //remove the "<?xml "
			const char *xml_version_string_end = strstr(xml_version_string_begin, "?>");
			if (xml_version_string_end != 0) {
				std::string xml_version_string_content = "";
				xml_version_string_content.append(xml_version_string_begin, xml_version_string_end); //result: version='1.0'
				const char *xml_version_content_verion_start = strstr(xml_version_string_content.c_str(), "version=");
				if (xml_version_content_verion_start != 0) {
					xml_version_content_verion_start += 9; //remove version='
					const char *xml_content_version_end = strstr(xml_version_content_verion_start, "\"");
					if (xml_content_version_end != 0) {
						final_xml_version_string.append(xml_version_content_verion_start, xml_content_version_end);
					}
				}
			}
		}
		return final_xml_version_string;
	}
	//CHECK PASSED---------------------------------------------------------

	//CHECK PASSED---------------------------------------------------------
	//gets the content of the root node a root node is defined by <name></name>
	std::string get_xml_root_node_content(const std::string xml_input, const std::string node_name) {
		std::string schematic_content = "";
		const std::string nnbegin = "<" + node_name + ">";
		const std::string nnend = "</" + node_name + ">";
		const char* schematic_content_start = strstr(xml_input.c_str(), nnbegin.c_str());
		if (schematic_content_start != 0) {
			schematic_content_start += nnbegin.size(); //remove the <schematic>
			const char* schematic_content_end = strstr(schematic_content_start, nnend.c_str());
			if (schematic_content_end != 0) {
				schematic_content.append(schematic_content_start, schematic_content_end);
			}
		}
		return schematic_content;
	}
	//CHECK PASSED---------------------------------------------------------

	//CHECK PASSED---------------------------------------------------------
	//returns the amount of elements
	int get_element_count(const std::string xml_input, const std::string node_name) {
		std::string element_name = "<" + node_name; //create the complete  element start name without space (" ")!!
													//count the  "<nodename " to alloc the result string array
		const char* xml_element_start_count = strstr(xml_input.c_str(), element_name.c_str());
		int array_size = 0;
		while (true) {
			xml_element_start_count = strstr(xml_element_start_count, element_name.c_str());
			if (xml_element_start_count != 0) {
				xml_element_start_count += element_name.size();
				array_size++;
			}
			else {
				break;
			}
		}
		return array_size;
	}
	//CHECK PASSED---------------------------------------------------------

	//CHECK PASSED---------------------------------------------------------
	//gets the content of all nodes with the spcified name you can process the result (xmlkvp with the callback function
	void get_element_content(const std::string xml_input, const std::string node_name, void(*callback_func)(std::string*, int)) {
		std::string element_name = "<" + node_name; //create the complete  element start name without space (" ")!!
													//count the  "<nodename " to alloc the result string array
		const char* xml_element_start_count = strstr(xml_input.c_str(), element_name.c_str());
		int array_size = 0;
		while (true) {
			xml_element_start_count = strstr(xml_element_start_count, element_name.c_str());
			if (xml_element_start_count != 0) {
				xml_element_start_count += element_name.size();
				array_size++;
			}
			else {
				break;
			}
		}

		if (array_size > 0) {
			//node_counter = array_size;
			//	const int f_array_size = const_cast<const int&>(array_size);
			std::string* xml_elements_content = 0;
			xml_elements_content = new std::string[array_size];
			int array_pop_counter = 0; //counter for correct array asign
			if (xml_input.size() > 0) {
				const char* xml_element_start = strstr(xml_input.c_str(), element_name.c_str());
				while (true) {
					xml_element_start = strstr(xml_element_start, element_name.c_str());
					if (xml_element_start != 0) {
						xml_element_start += element_name.size(); //remove the <node
						const char* xml_element_end = strstr(xml_element_start, "/>");
						if (xml_element_end != 0) {
							xml_elements_content[array_pop_counter] = "";
							std::string xml_element_content = "";
							xml_element_content.append(xml_element_start, xml_element_end);
							xml_elements_content[array_pop_counter] = xml_element_content;
							callback_func(xml_elements_content, array_pop_counter);
							xml_element_start = xml_element_end + 2;
							array_pop_counter++;
						}
						else { break; }
					}
					else { break; }
				}
			}
			delete[]xml_elements_content; //delete array
		}//ende if arraysize > 0
	}
	//CHECK PASSED---------------------------------------------------------

	//CHECK PASSED---------------------------------------------------------
	//basic string replace function
	void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		if (from.empty())
			return;
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}
	//CHECK PASSED---------------------------------------------------------

	//CHECK PASSED---------------------------------------------------------
	//prepare the xml input : replace some charakters,
	void prepare_xml_input(std::string& xml_input) {
		//replaceAll(xml_input, std::string(char(39), sizeof(char)), std::string(char(34), sizeof(char))); //replace " with '
		replaceAll(xml_input, "", "\r\n");
		replaceAll(xml_input, "", "\n");
		replaceAll(xml_input, "\" = \"", "\"=\"");
		replaceAll(xml_input, " = ", "=");
		replaceAll(xml_input, "> <", "><");
	}
	//in this function you can process your xml results you can define an other function with the functionpointer-parameter in the get_element_content or get_element attribute
	//CHECK PASSED---------------------------------------------------------

	//CHECK PASSED---------------------------------------------------------
	//get the key value pairs of the result from the get_element_content_function
	std::string get_element_attributes(const std::string xml_input, const std::string element_name) {
		const char* xml_element_key_start = strstr(xml_input.c_str(), element_name.c_str());
		std::string result_string = "";
		if (xml_element_key_start != 0)
		{
			xml_element_key_start += element_name.size() + 2; //to remove the emelement name + the ="
			if (xml_element_key_start != 0)
			{
				const char* xml_element_key_end = strstr(xml_element_key_start, "\"");
				if (xml_element_key_end != 0)
				{
					result_string.append(xml_element_key_start, xml_element_key_end);
					return result_string;
				}
				else {
					return "";
				}
			}
			else
			{
				return "";
			}
		}
		else {
			return "";
		}
		return "";
	}
	//CHECK PASSED---------------------------------------------------------

}



void processing_serial_query(base_node* bn[]) {
	
	std::string message = serial_management::get_recieved();
	//load frome queue
	//if message exists btw 
	if (message != "") {
		for (size_t i = 0; i < (sizeof(bn) / sizeof(bn[0])); i++)
		{
			if (bn[i]->use_serial_recieve) {
				bn[i]->serial_income(message);
			}
		}
	}
	//remove query message




}

void make_connections(base_node* bn[], int bnsize, std::string _cstring) {

	base_node* obn = NULL;
	base_node* dbn = NULL;

	const char* start_cs = _cstring.c_str();
	if (start_cs == 0) { return; }
	while (true)
	{


		//WHILE BIS KEIN % MEHR VORHANDEN IST
		
		if (start_cs == 0) { break; }
		const char* end_on = strstr(start_cs, ":");
		if (end_on == 0) { break; }
		std::string origin_node_id = "";
		origin_node_id.append(start_cs, end_on);

		start_cs = end_on += 1;
		end_on = strstr(start_cs, ":");
		if (end_on == 0) { break; }
		std::string origin_node_con = "";
		origin_node_con.append(start_cs, end_on);

		start_cs = end_on += 1;
		end_on = strstr(start_cs, ":");
		if (end_on == 0) { break; }
		std::string dest_node_id = "";
		dest_node_id.append(start_cs, end_on);

		end_on += 1;
		start_cs = end_on;
		end_on = strstr(start_cs, "%");
		if (end_on == 0) { break; }
		
		std::string dest_node_con = "";
		dest_node_con.append(start_cs, end_on);

	
	
		for (size_t i = 0; i < bnsize; i++)
		{
			if (bn[i]->nid == atoi(origin_node_id.c_str())) {
				obn = bn[i];
				break;
			}
		}
		for (size_t i = 0; i < bnsize; i++)
		{
			if (bn[i]->nid == atoi(dest_node_id.c_str())) {
				dbn = bn[i];
				break;
			}
		}

		if (obn != NULL && dbn != NULL) {
			obn->set_connection(atoi(origin_node_con.c_str()), dbn, atoi(dest_node_con.c_str()));
			std::cout << "make connection for : " << origin_node_id << "-" << origin_node_con << " -> " << dest_node_id << "-" << dest_node_con << std::endl;
		}
		else {
			std::cout << "cant_ connect nodes 1" << std::endl;

		}

		start_cs = end_on + 1;
		obn = NULL;
		dbn = NULL;
	}
	free(obn);
	free(dbn);





}

int count_connections(std::string _cstring, int target_count_id) {
	int couter = 0;

	const char* start_cs = _cstring.c_str();
	if (start_cs == 0) { return 0; }
	while (true)
	{
		if (start_cs == 0) { break; }
		const char* end_on = strstr(start_cs, ":");
		if (end_on == 0) { break; }
		std::string origin_node_id = "";
		origin_node_id.append(start_cs, end_on);
		if (atoi(origin_node_id.c_str()) == target_count_id) {
			couter++;
		}
		end_on += 1;
		start_cs = end_on;
		end_on = strstr(start_cs, "%");
		if (end_on == 0) { break; }
		start_cs = end_on + 1;
	}
	return couter;
}


uint32_t getTick() {
#if defined(_LINUX_)
	struct timespec ts;
	unsigned theTick = 0U;
	clock_gettime(CLOCK_REALTIME, &ts);
	theTick = ts.tv_nsec / 1000000;
	theTick += ts.tv_sec * 1000;
	return theTick;
#endif
#if defined(_WIN_)
	return getTickCount();
#endif
}






void process_xml_nodes(std::string*  kvp, int element_count) {
	std::cout << "XML NODE CONTENT: " << kvp[element_count].c_str() << std::endl;
	int nid = -1;
	std::string  nsi ="";
	std::string nparam = "";
	std::string result = "";
	result = xml_parser::get_element_attributes(kvp[element_count], "nid");
	if (result == "") { return; }
	nid = atoi(result.c_str());
	if (nid < 0) { return; }
	result = "";
	result = xml_parser::get_element_attributes(kvp[element_count], "nsi");
	if (result == "") { return; }
	nsi = result;
	if (nsi == "") { return; }
	result = "";
	result = xml_parser::get_element_attributes(kvp[element_count], "ncon");

	if (result == "") {}
	else if(result == "%"){}
	else{ connection_string->append(result);}


		
	

//	xml_parser::replaceAll(*connection_string, "%%", "%");
	result = "";
	result = xml_parser::get_element_attributes(kvp[element_count], "nparam");
	nparam = result;

	if (nsi == "nbdi") { nodes_buffer[element_count] = new node_nbdi(nid, true, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "nbdo") { nodes_buffer[element_count] = new node_nbdo(nid, true, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "bndmx") { nodes_buffer[element_count] = new node_bndmx(nid, true, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "bnidisp") { nodes_buffer[element_count] = new node_bnidisp(nid, true, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "bland") { nodes_buffer[element_count] = new node_bland(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "blor") { nodes_buffer[element_count] = new node_blor(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "blxor") { nodes_buffer[element_count] = new node_blxor(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "blnot") { nodes_buffer[element_count] = new node_blnot(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "blbuffer") { nodes_buffer[element_count] = new node_blbuffer(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "bifte") { nodes_buffer[element_count] = new node_bifte(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "biftest") { nodes_buffer[element_count] = new node_biftest(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "biftefl") { nodes_buffer[element_count] = new node_biftefl(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "intcomp") { nodes_buffer[element_count] = new node_intcomp(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "floatcomp") { nodes_buffer[element_count] = new node_floatcomp(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "strcomp") { nodes_buffer[element_count] = new node_strcomp(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "blfrs") { nodes_buffer[element_count] = new node_blfrs(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "blft") { nodes_buffer[element_count] = new node_blft(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "nbcoin") { nodes_buffer[element_count] = new node_nbcoin(nid, false, count_connections(*connection_string, nid), nparam, true); return; };
	if (nsi == "nbcost") { nodes_buffer[element_count] = new node_nbcost(nid, false, count_connections(*connection_string, nid), nparam, true); return; };
	if (nsi == "nbcofl") { nodes_buffer[element_count] = new node_nbcofl(nid, false, count_connections(*connection_string, nid), nparam, true); return; };
	if (nsi == "nbcobot") { nodes_buffer[element_count] = new node_nbcobot(nid, false, count_connections(*connection_string, nid), nparam, true); return; };
	if (nsi == "nbcobof") { nodes_buffer[element_count] = new node_nbcobof(nid, false, count_connections(*connection_string, nid), nparam, true); return; };
	if (nsi == "nbsttoi") { nodes_buffer[element_count] = new node_nbsttoi(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "nbsttof") { nodes_buffer[element_count] = new node_nbsttof(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "nbitof") { nodes_buffer[element_count] = new node_nbitof(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "nbftoi") { nodes_buffer[element_count] = new node_nbftoi(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "nbinttostr") { nodes_buffer[element_count] = new node_nbinttostr(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "nbfltostr") { nodes_buffer[element_count] = new node_nbfltostr(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "ctimest") { nodes_buffer[element_count] = new node_ctimest(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "tstoint") { nodes_buffer[element_count] = new node_tstoint(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "basetimer") { nodes_buffer[element_count] = new node_basetimer(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "simplemath") { nodes_buffer[element_count] = new node_simplemath(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "phhlux") { nodes_buffer[element_count] = new node_phhlux(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "opwemare") { nodes_buffer[element_count] = new node_opwemare(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "stringappend") { nodes_buffer[element_count] = new node_stringappend(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "stringsplit") { nodes_buffer[element_count] = new node_stringsplit(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "stringoffset") { nodes_buffer[element_count] = new node_stringoffset(nid, false, count_connections(*connection_string, nid), nparam, false); return; };
	if (nsi == "basiccounter") { nodes_buffer[element_count] = new node_basiccounter(nid, false, count_connections(*connection_string, nid), nparam, false); return; };


}

void main_serial_update_loop() {
	//SEND SERIAL MESSAGE FROM QUEUE
	if (!serial_management::send_queue.empty()) {

		std::string msg = serial_management::get_message_to_send();
		std::cout << msg << std::endl;
		if (msg != "") {
			Ret = LS.WriteString(msg.c_str());
			usleep(100);// Send the command on the serial port
			if (Ret != 1) {                                                           // If the writting operation failed ...
				printf("Error while writing data\n");                              // ... display a message ...

			}
		}
	}
	// READ SERIAL MESSAGE FROM DEVICE TO SERIAL RECIEVE QUEUE
	Ret = LS.ReadString(Buffer, '\n', 128, 50);                                // Read a maximum of 128 characters with a timeout of 5 seconds
	if (Ret > 0) {
#if defined(DEBUG)
		std::cout << "recieved : " << Buffer << std::endl;
#endif
		serial_management::add_to_revieved_queue(Buffer);
	}
	//SERIAL PROCESSING STUFF -> TRANSMIT RECIEVED DATA TO ALL NODES WHO NEEDED SERIAL COMMANDS
	processing_serial_query(nodes_buffer); //process the recieved messsages
	serial_management::update();// The final character of the string must be a line feed ('\n')

}


int main(int argc, char *argv[])
{
	std::cout << "TOTAL SYSTEM RAM : " << (getTotalSystemMemory()/1024)/1024 << "MB" <<  std::endl;

	//INIT SERIAL STUFF
 	

//INIT SERIAL DEVICE
	std::cout << "STARTING MAIN UPDATE LOOP" << std::endl;
	Ret = LS.Open("/dev/ttyUSB0", 9600);                                     
	if (Ret != 1) {                                                          
		printf("Error while opening port. Permission problem ?\n");        
		return Ret;                                                       
	}
	std::cout << "NODESERVER V1.2 STARTING THE SERIAL INTERFACE IS: /dev/ttyUSB0" << std::endl;
	serial_management::add_to_send_queue("0_bnid_0_SmartSPS 1.2\n");
	#if defined(DEBUG)
	serial_management::add_to_send_queue("0_bnid_1_DEBUG-BUILD\n");
	#endif




	
	connection_string = new std::string();//create string


		//XML BIS NODES PARSEN
		std::string xml_input_string = request_schematic();

	if (xml_input_string == "") { return 1; }
#if defined(DEBUG)
//	std::cout << "XML RAW INPUT : " << xml_input_string.c_str() << std::endl;
#endif

	xml_parser::prepare_xml_input(xml_input_string);
#if defined(DEBUG)
//	std::cout << "XML PREPARED INPUT : " << xml_input_string.c_str() << std::endl;
#endif


	std::string xml_version_string = "";
	xml_version_string = xml_parser::get_xml_version(xml_input_string);
	if (xml_version_string == "") { return 2; }
#if defined(DEBUG)
	std::cout << "XML VERSION : " << xml_version_string.c_str() << std::endl;
#endif


	std::string xml_root_node_content_string = "";
	xml_root_node_content_string = xml_parser::get_xml_root_node_content(xml_input_string, "schematic");
	if (xml_root_node_content_string == "") { return 3; }
#if defined(DEBUG)
	//std::cout << "XML ROOT(SCHEMATIC) NODE CONTENT : " << xml_root_node_content_string.c_str() << std::endl;
#endif






	
	//GET AMOUNT OF NODES
	int node_amount = xml_parser::get_element_count(xml_root_node_content_string, "node");
	//CREATE DYNAMIC BASENODE ARRAY TO HOLD THE SCHEMATIC
	nodes_buffer = new base_node*[node_amount];
	//FINAL XML PROCESSING
	xml_parser::get_element_content(xml_root_node_content_string, "node", process_xml_nodes);



	//MAKE CONNECTION TO INSTANCES
	make_connections(nodes_buffer, node_amount, *connection_string); //CREATE CONNECTIONS FOR THE INPUTNODE
	//ENABLE ALL NODES
	for (size_t i = 0; i < node_amount; i++){
		nodes_buffer[i]->init(); //dont called from constructor to be shure tha all nodes are instancieated
		nodes_buffer[i]->enabled = true;
	}
		//FINISH WITH LOADING NODES
	std::cout << node_amount << " NODES LOADED : SCHMEATIC SIMULATION IS STARTING" << std::endl;
	bool first_iteration = true;


	//START MAINLOOP
	std::cout << "STARTING MAIN UPDATE LOOP" << std::endl;
	while (!break_update_cycle)
	{
		//STORE TIME AT LOOP START
		start_loop_ticks = getTick();

		//UPDATE ALL NODES 
		if (delta_time > 0) {
			for (int i = 0; i < node_amount; i++)
			{
				if (nodes_buffer[i]->enabled && nodes_buffer[i]->nid >= 0) {
					nodes_buffer[i]->update(delta_time);
				}
			}
		}


		//UPDATE ALL STATIC NODES
		if (first_iteration) {
			for (size_t i = 0; i < node_amount; i++) {
				if (nodes_buffer[i]->is_value_static) {
					nodes_buffer[i]->updated_values = true;
					nodes_buffer[i]->update();
				}
				first_iteration = false;
			}
		}

		//CHECK FOR SERIAL EVENTS
		main_serial_update_loop();
	//GET TIME AND CALC DELTATIME FOR THE NEXT ITERATION
		 end_loop_ticks = getTick();
		delta_time = (end_loop_ticks - start_loop_ticks) / 1000.0f;

		average_delta_time += delta_time;
		average_delta_time = average_delta_time / 2;
#if defined(DEBUG)
	//	std::cout << "average_frame_delta_time  :" << average_delta_time << std::endl;
#endif
	}






	std::cout << "LEAVING MAIN UPDATE LOOP AND CLEANUP" << std::endl;
	delete[] nodes_buffer;
	//----- CLOSE THE UART -----
	LS.Close();
	std::cout << "EXIT NODESERVER WITH EXITCODE 0" << std::endl;
	return 0;
}