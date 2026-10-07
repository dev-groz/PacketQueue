#pragma once
#include <memory>
#include <vector>


class Packet
{
public:
	Packet() :
		data(0), dataCount(0), packetId(0) {}

	Packet(unsigned char* newData, unsigned int newDataCount, unsigned int newPacketId) {
		dataCount = newDataCount;
		packetId = newPacketId;
		data = std::vector<unsigned char>{};
		for (int i = 0; i < newDataCount; i++) {
			data.push_back(newData[i]);
		}
	}

	unsigned char* getData() {
		return data.data();
	}

	unsigned int getDataCount() {
		return dataCount;
	}

	unsigned int getPacketId() {
		return packetId;
	}

private:
	std::vector<unsigned char> data;
	unsigned int dataCount;
	unsigned int packetId;
};
