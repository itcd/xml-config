#include "config.h"

int main(int argc, char *argv[])
{
	ServerConfig sc1;
	std::cout << sc1.toString() << std::endl;
	ClientConfig cc1;
	std::cout << cc1.toString() << std::endl;

	// Load settings from the XML file specified in the first command-line argument
	std::string xml = argc > 1 ? argv[1] : (base_filename(argv[0]) + "_VRServer.xml");
	ServerConfig sc(xml.c_str());
	std::cout << xml << std::endl << sc.toString() << std::endl;

	// Load settings from the XML file specified in the first command-line argument
	std::string xml2 = argc > 2 ? argv[2] : (base_filename(argv[0]) + "_VRClient.xml");
	ClientConfig cc(xml2.c_str());
	std::cout << xml2 << std::endl << cc.toString() << std::endl;
}
