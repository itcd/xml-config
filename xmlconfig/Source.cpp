#include "config.h"

int main(int argc, char *argv[])
{
	ServerConfig sc1;
	std::cout << sc1.toString() << std::endl;
	ClientConfig cc1;
	std::cout << cc1.toString() << std::endl;

	auto xml = argc > 1 ? argv[1] : "VRServer.xml";
	auto xml2 = argc > 2 ? argv[2] : "VRClient.xml";
	ServerConfig sc(xml);
	std::cout << sc.toString() << std::endl;
	ClientConfig cc(xml2);
	std::cout << cc.toString() << std::endl;
}
