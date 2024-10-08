#pragma once

#include <array>
#include <memory>

#include "Packet.hpp"

template <unsigned int maxDataCount, unsigned int maxPacketsInQueue, unsigned int queueCapacity>
class PacketQueue {

public:
	PacketQueue() :
		dataCountInQueue(0),
		queueStart(0),
		queueEnd(0),
		elementsInQueue(0) {}

	bool push(unsigned char* data, unsigned int dataCount, unsigned int packetId) {
		if (dataCount > maxDataCount) {
			return false;
		}

		if (elementsInQueue == maxPacketsInQueue) {
			return false;
		}

		if (dataCountInQueue + dataCount > queueCapacity) {
			return false;
		}

		queue[queueEnd] = Packet(data, dataCount, packetId);
		queueEnd = (queueEnd + 1) % maxPacketsInQueue;

		dataCountInQueue += dataCount;

		++elementsInQueue;

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

		--elementsInQueue;

		return true;
	}

	~PacketQueue() {
		if (isEmpty())
			return;
		if (queueStart < queueEnd) {
			for (int i = queueStart; i < queueEnd; i++)
			{
				queue[i].freeData();
			}
		} else /* queueStart > queueEnd */ {
			for (int i = 0; i < queueEnd; i++)
			{
				queue[i].freeData();
			}

			for (int i = queueStart; i < maxPacketsInQueue; i++)
			{
				queue[i].freeData();
			}
		}
	}


private:
	bool isEmpty() {
		return elementsInQueue == 0;
	}

	std::array<Packet, maxPacketsInQueue> queue{};
	int dataCountInQueue;
	int queueStart;
	int queueEnd;
	int elementsInQueue;
};
