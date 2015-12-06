#pragma once
//SERIAL MANAGEMENT CLASS
#include "serial_management.h"
#include <sstream>      // std::stringstream
#include "serialib.h"
#include "serialib.h"
//NODE BASE CLASS
#include "base_node.h"




//BASIC IO NODES
#include "node_nbdi.h" // 1 GPIO INPUT <mid><msi><gpio>
#include "node_nbdo.h" // 1 GPIO OUTPUT <mid><msi><gpio>
#include "node_bndmx.h" // 1 Channel DMX Output <mid><msi><channel>
#include "node_bnidisp.h" //Show Text on Display <mid><msi><line>
//BASIC LOGIC GATE NODES
#include "node_bland.h" //NAD GATE
#include "node_blor.h" //OR GATE
#include "node_blxor.h" // XOR GATE
#include "node_blnot.h" // NOT GATE
#include "node_blbuffer.h" // BUFFER / DRIVER GATE
//FURTHER CONTROL LOGIC
#include "node_bifte.h"  //IF TRUE CHOOSE A ELSE CHOOSE B INT
#include "node_biftest.h" //IF TRUE CHOOSE A ELSE CHOOSE B STRING
#include "node_biftefl.h" //IF TRUE CHOOSE A ELSE CHOOSE B FLOAT
//VALUE COMPARES
#include "node_intcomp.h" //COMPARE TWO INT VALUES <== >= <= > < !=>
#include "node_floatcomp.h" //COMPARE TWO FLOAT VALUES <== >= <= > < != >
#include "node_strcomp.h" //COMPARE TWO STRING VALUES < == != >
//BASIC LOGIC FLIP FLOPS
#include "node_blfrs.h" // RS FLIP FLOP
#include "node_blft.h" // T FLIP FLOP
//BASIC CONSTANT VALUES
#include "node_nbcoin.h" //CONSTANT INT VALUE <value>
#include "node_nbcost.h" //CONSTANT STRING VALUE <value>
#include "node_nbcofl.h" //CONSTANT FLOAT VALUE <value>
#include "node_nbcobot.h" // CONSTANT BOOL VALUE TRUE
#include "node_nbcobof.h" //CONSTANT BOOL VALUE FALSE
//BASIC UNIT CONVERTERS
#include "node_nbsttoi.h" // CONVERTS STRINGS TO INTS
#include "node_nbsttof.h" // CONVERTS STRINGS TO FLOATS
#include "node_nbitof.h" //CONVERTS INTs TO FLOATS
#include "node_nbftoi.h" //CONVERTS FLOATS TO INTS
#include "node_nbinttostr.h" //CONVERT INT TO STRING
#include "node_nbfltostr.h" //CONVERT FLOAT TO STRING
//TIME
#include "node_ctimest.h" // GETS THE CURRENT TIMESTAMP AS INT
#include "node_tstoint.h" //CONVERTS A TIMESTAMP TO SINGLE INTS
//PHILIPS HUE
#include "node_phhlux.h" // PHILIPS HUE LUX LAMPS  <bridge_ip><username><light_id>
//OpenWeatherMap 
#include "node_opwemare.h" //Current Weater Request <api_key><city_id><key_search>
