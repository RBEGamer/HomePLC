#pragma once
#include <stdlib.h>     /* atoi */
#include "base_node.h"
#include "connector.h"
#include "serial_management.h"
#include <iostream>

#include <string>
#include <sstream>

template <typename T>
std::string NumberToString(T pNumber)
{
	std::ostringstream oOStrStream;
	oOStrStream << pNumber;
	return oOStrStream.str();
}
