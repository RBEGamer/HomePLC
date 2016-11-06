# HomePLC
HomePLC is a PLC for smarthome purposes, to control your lamps, devices or machines. 
You can use as input several sensors or webservices. For the HomePLC you will need at least the main unit. 
The main unit contains a RaspberryPi witch run the HomePLC-Server software.
As connection to the modules (like relais, sensors,..), it uses a standard USB2RS485 stick.
To connect the Mainunit to the modules it uses a 4 wire standard cable, which contains power and serial data. 
The Serial data bus is RS485@9600 but you can change it to our needs.

# Features:
* RaspberryPi and Arduino based hardware
* PLC oriented programming node based programming language
* Simple Programming Interface
* Arduino Based Hardware Extentions (DMX, Relais, SensorInterfaces, Analog Inputs, GPS, RTC, RS485, PWM-Output,...)
* Webservice integration (OpenWeatherMap,Philips Hue, Netatmo)
* Din Rail Case for integration into exisitng PLC Systems
* Debug webserver at port 5555
* LUA scripting integration to create complex control flows and create your own programming nodes
* Simple Full-Duplex RS485 Protocol to connect further hardware
* Actor and sensor can be combined in one module


# HARDWARE (MAIN UNIT)
* Linux based computer, to mount it at the DIN-Rail i used a RaspberryPi 3
* 5V and 12V switching power supply
* Arduino Micro (LED, LCD, POWER)
* I2C 16x2 Display for status information
* 3 LEDs for power, error and message signals
* Sub-D9 female connector to connect modules
* USB2Serial converter, if your linux board have no serial port avariable
* RS485 transceiver chip (optional isolated)
* DIN-Rail case

# HARDWARE (SAMPLE MODULE)
* Din-Rail case
* 2 state leds (optional)
* Arduino micro
* RS485 transceiver chip (optional isolated)
* 2 Sub-D9 female connectors (in/out)
* 4 channel relais board

# SOFTWARE
The software are splitted in two parts :
* HomePLC-Server (runs on your main unit to control your devices)
* HomePLC-Commander (Design the interaction beween the modules and create the schematic files and upload it to your main unit)
The HomePLC schematic is a grafical control language to design a interaction between the modules.
You have several nodes like standard logical nodes :
* AND, OR, NOT,...
* FLIPFLOS
* MATH
* CONSTANS
* Time Nodes
* Compares
* Serial IN/OUT
All other currently implemented nodes are located at:
`HomePLC/Documentation/Implmented Nodes.csv`

If you have designed a schematic, enter the ip to upload a xml design file to the HomePLC-MainUnit.
The main unit will restart and will start to execute the new schematic. 
You can see the process and errors at the debug interfache.

# LOCATIONS
* A debug build of the HomePLC-Server for the RaspberryPi3 is located at `/Source/BUILDS/BUILD_15_01_2016/`
* The source of the HomePLC-Server to build ith on your own system is located at `/Source/SmartSPS/`
* The HomePLC-Commander source is located at `/Source/SmartPLC_Commander/`
* Sample programs for the HomePLC-Commander are located at `/Documentation/SampleConfig/for_smartsps_commander/`
* Pictures of the MainUnit hardware are located at `/Documentation/Pictures/`

# TODO
* Add Ethernet-Modules
* Add node debugging
* Add cmakelists

# IMAGES
###  BASE MAIN UNIT
![Gopher image](/Documentation/Pictures/base_case_complete.JPG)

### TWO EXTENTIONS (left 6 channel relais, right, 12 channel analog input)
![Gopher image](/Documentation/Pictures/two_extentions_with_case.JPG)

### OPEN MAIN UNIT
![Gopher image](/Documentation/Pictures/base_open.JPG)

