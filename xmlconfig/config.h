//////////////////////////////////////////////////////////////////////////
//// XML serialization for settings
//// Created on 2016-10-28 by Shengzhou Luo
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cereal/archives/xml.hpp>
#include <sys/stat.h>

// http://stackoverflow.com/questions/17818099/how-to-check-if-a-file-exists-before-creating-a-new-file
bool fileExists(const char * filename)
{
	struct stat fileInfo;
	return stat(filename, &fileInfo) == 0;
}

struct ServerConfig
{
	unsigned short udpPort = 40000;
	unsigned short tcpPort = 40001;
	std::string transferFunctionFile = "../../transferfuncs/nucleon.tfi";
	std::string folderPath = "../../Samples/supernova/";
	std::string headerFile = "../../Samples/supernova/DSSupernova.mhd";

	ServerConfig(){}

	ServerConfig(const char * xml)
	{
		init(xml);
	}

	void init(const char * xml)
	{
		if (fileExists(xml))
		{
			std::ifstream is(xml);
			cereal::XMLInputArchive archive(is);
			archive(udpPort, tcpPort, transferFunctionFile, folderPath, headerFile);
		}
		else
		{
			std::ofstream os(xml);
			cereal::XMLOutputArchive archive(os);
			archive(CEREAL_NVP(udpPort), CEREAL_NVP(tcpPort), CEREAL_NVP(transferFunctionFile), CEREAL_NVP(folderPath), CEREAL_NVP(headerFile));
		}
	}

	std::string toString()
	{
		std::stringstream ss;
		ss << udpPort << std::endl << tcpPort << std::endl << transferFunctionFile << std::endl << folderPath << std::endl << headerFile << std::endl;
		return ss.str();
	}
};

struct ClientConfig
{
	unsigned char a = 127;
	unsigned char b = 0;
	unsigned char c = 0;
	unsigned char d = 1;
	unsigned short udpPort = 40000;
	unsigned short tcpPort = 40001;
	std::string transferFunctionFile = "../../Samples/CTknee/transfer_function/CT-Knee_spectrum_16_balance.tfi";

	ClientConfig(){}

	ClientConfig(const char * xml)
	{
		init(xml);
	}

	void init(const char * xml)
	{
		if (fileExists(xml))
		{
			std::ifstream is(xml);
			cereal::XMLInputArchive archive(is);
			std::string ip;
			archive(ip, udpPort, tcpPort, transferFunctionFile);
			setIP(ip);
		}
		else
		{
			std::ofstream os(xml);
			cereal::XMLOutputArchive archive(os);
			std::string ip = getIP();
			archive(CEREAL_NVP(ip), CEREAL_NVP(udpPort), CEREAL_NVP(tcpPort), CEREAL_NVP(transferFunctionFile));
		}
	}

	std::string getIP()
	{
		std::stringstream ss;
		ss << (int)a << "." << (int)b << "." << (int)c << "." << (int)d;
		return ss.str();
	}

	void setIP(std::string ipstr)
	{
		std::replace(ipstr.begin(), ipstr.end(), '.', ' ');
		std::stringstream ss(ipstr);
		int a0, b0, c0, d0;
		ss >> a0 >> b0 >> c0 >> d0;
		a = static_cast<unsigned char>(a0);
		b = static_cast<unsigned char>(b0);
		c = static_cast<unsigned char>(c0);
		d = static_cast<unsigned char>(d0);
	}

	std::string toString()
	{
		std::stringstream ss;
		ss << getIP() << std::endl << udpPort << std::endl << tcpPort << std::endl << transferFunctionFile << std::endl;
		return ss.str();
	}
};
