#include <iostream>
#include <memory>
#include <array>


class Packet
{
public:
	Packet() :
		data(0), dataCount(0), packetId(0) {}

	Packet(unsigned char* newData,	unsigned int newDataCount,	unsigned int newPacketId) {
		dataCount = newDataCount;
		packetId = newPacketId;
		data = (unsigned char*)std::malloc(sizeof(unsigned char) * newDataCount);
		if (data != 0)
		{
			std::memcpy(data, newData, newDataCount);
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



template <unsigned int maxDataCount, unsigned int maxPacketsInQueue, unsigned int queueCapacity>
class PacketQueue {

public:
	PacketQueue():
		dataCountInQueue(0),
		queueStart(0),
		queueEnd(0) {}

	bool push(unsigned char* data, unsigned int dataCount, unsigned int packetId) {
		if (dataCount > maxDataCount) {
			return false;
		}
			
		if (queueSize() + 1 > maxPacketsInQueue) {
			return false;
		}

		if (dataCountInQueue + dataCount > queueCapacity) {
			return false;
		}

		queue[queueEnd] = Packet(data, dataCount, packetId);
		queueEnd = (queueEnd + 1) % maxPacketsInQueue;

		dataCountInQueue += dataCount;

		return true;
	}

	bool pop(unsigned char* buffer, unsigned int bufferSize, unsigned int& dataCount, unsigned int& packetId) {
		if (isEmpty()) {
			return false;
		}

		Packet* firstPacket = &(queue[queueStart]);
		queueStart = (queueStart + 1) % maxPacketsInQueue;

		std::memcpy(buffer, firstPacket->getData(), bufferSize);

		packetId = firstPacket->getPacketId();

		dataCount = firstPacket->getDataCount(); 

		dataCountInQueue -= dataCount;
		firstPacket->freeData();

		return true;
	}

private:
	bool isEmpty() {
		return queueStart == queueEnd;
	}

	size_t queueSize() {
		if (queueStart <= queueEnd) {
			return queueEnd - queueStart;
		}
		else {
			return maxPacketsInQueue - (queueStart - queueEnd);
		}
	}

	std::array<Packet, maxPacketsInQueue> queue{};
	int dataCountInQueue;
	int queueStart;
	int queueEnd;
};




int main()
{
	
}
