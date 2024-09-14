#pragma once
#include <memory>


class Packet
{
public:
	Packet() :
		data(0), dataCount(0), packetId(0) {}

	Packet(unsigned char* newData, unsigned int newDataCount, unsigned int newPacketId) {
		dataCount = newDataCount;
		packetId = newPacketId;
		data = (unsigned char*)std::malloc(sizeof(unsigned char) * newDataCount);
		if (data != 0)
		{
			std::memcpy(data, newData, newDataCount);
		}
		else {
			throw std::exception("Internal error: Malloc returned 0!");
		}
	}

	unsigned char* getData() {
		return data;
	}

	unsigned int getDataCount() {
		return dataCount;
	}

	unsigned int getPacketId() {
		return packetId;
	}

	void freeData() {
		std::free(data);
	}
private:
	unsigned char* data;
	unsigned int dataCount;
	unsigned int packetId;
};
