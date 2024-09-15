# Packet queue implementation in C++

Queue is implemented using _cyclic array_, which is best according that we have set max queue size.

In this project I have 2 classes: **Packet** and **PacketQueue**

**Packet** is a unit that hold the necessary info about packet, it's also dealing with memory allocation for data.

**PacketQueue** is a container that hold **Packets** and uses cyclic array logic

It has 2 functions:

- **push()** puts packet at the end of the queue

- **pop()** remove packet from the beginning and returning the packet
