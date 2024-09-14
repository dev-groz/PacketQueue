#include <iostream>
#include <memory>
#include <array>

#include "PacketQueue.hpp"


int main()
{	
	PacketQueue<256, 10, 1024> packetQueue;
	unsigned char data[] = { (unsigned char)0xf, (unsigned char)0x17, (unsigned char)0x7 };
	packetQueue.push(data, 3, 15);
	packetQueue.push(data + 1, 2, 16);
	packetQueue.push(data, 2, 17);

	packetQueue.push(data, 1, 23);
	packetQueue.push(data + 1, 1, 24);
	unsigned char buffer[10];
	unsigned int dataCount = 0;
	unsigned int packetId = 0;

	for (size_t i = 0; i < 3; i++)
	{
		packetQueue.pop(buffer, 10, dataCount, packetId);
		std::cout << "printing packet " << packetId << std::endl;
		for (size_t i = 0; i < dataCount; i++)
		{
			std::cout << "\t" << (unsigned int)buffer[i] << std::endl;
		}
	}
}
