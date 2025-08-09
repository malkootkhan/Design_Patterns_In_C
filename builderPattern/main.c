#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct NetworkPacket NetworkPacket, *pNetworkPacket;
typedef struct NetworkPacketBuilder NetworkPacketBuilder, *pNetworkPacketBuilder;

typedef pNetworkPacketBuilder (*IPoperation)(pNetworkPacketBuilder, const char *);
typedef pNetworkPacketBuilder (*portOperation)(pNetworkPacketBuilder, int);
typedef pNetworkPacketBuilder (*dataOperation)(pNetworkPacketBuilder, const char *);
typedef NetworkPacket (*build)(pNetworkPacketBuilder);

struct NetworkPacket {
    char sourceIP[30];
    char destIP[30];
    int port;
    char payLoad[256];
    int payLoadSize;
};

struct NetworkPacketBuilder {
	NetworkPacket packet;
    	IPoperation setSourceIP;
	IPoperation setDestIP;
	portOperation setPort;
	dataOperation setPayLoad;
	build Build;
};

pNetworkPacketBuilder sourceIPsetting(pNetworkPacketBuilder b, const char *ip)
{
	strncpy(b->packet.sourceIP, ip, sizeof(b->packet.sourceIP) - 1);
	return b;
}

pNetworkPacketBuilder destIPsetting(pNetworkPacketBuilder b, const char *ip)
{
	strncpy(b->packet.destIP, ip, sizeof(b->packet.destIP) - 1);
	return b;
}
pNetworkPacketBuilder portSetting(pNetworkPacketBuilder b, int port)
{
	b->packet.port = port;
	return b;
}
pNetworkPacketBuilder payloadSetting(pNetworkPacketBuilder b, const char *data)
{
	strncpy(b->packet.payLoad, data, sizeof(b->packet.payLoad) - 1);
	b->packet.payLoadSize = strlen(data);
	return b;
}

NetworkPacket buildSetting(pNetworkPacketBuilder b)
{
	return b->packet;
}

NetworkPacketBuilder createNetworkPacketBuilder(void)
{
	NetworkPacketBuilder b;
	memset(&b.packet, 0, sizeof(NetworkPacket));

	b.setSourceIP = sourceIPsetting;
	b.setDestIP = destIPsetting;
	b.setPort = portSetting;
	b.setPayLoad = payloadSetting;
	b.Build = buildSetting;

	return b;
}

int main()
{

	NetworkPacketBuilder b = createNetworkPacketBuilder();
	//NetworkPacket packet = b.packet;
	NetworkPacket packet;

	b.setSourceIP(&b, "192.168.14.1");
	b.setDestIP(&b, "192.168.20.10");
	b.setPort(&b, 1234);
	b.setPayLoad(&b, "Hello World!");
	packet = b.Build(&b);

	printf("port: %d\n", packet.port);
	printf("sourceIP: %s\n", packet.sourceIP);
	printf("destIP: %s\n", packet.destIP);
	printf("payload: %s payloadsize: %d\n", packet.payLoad, packet.payLoadSize);
	return 0;
}
