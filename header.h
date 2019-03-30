#pragma once
#ifndef HEADER_H
#define HEADER_H
#include "raw.h"

//IPHeader Ŭ���� �����
class IPHeader {
private:
	IPV4H *header;
public:
	IPHeader(char *packet);
	int getDesaddr();
	int getSrcaddr();
	int getProtocol();
	int getIpLength();
	int getIpVer();
	int getIpTos();
	int getIpChecksum();
	int getIpHLen();
	int getIpId();
	int getTTL();

};

//TCPHeader Ŭ���� �����
class TCPHeader {
private:
	TCPH *header;
public:
	TCPHeader(int ipSize, char *packet);
	int getDesPort();
	int getSrcPort();
	int getTcpLength();
	int getSeqNo();
	int getAckNo();
	int getUrg();
	int getAck();
	int getPush();
	int getRes();
	int getSyn();
	int getFin();
	int getWin();
	int getChecksum();
	int getUrgPointer();
};

//UDPHeader Ŭ���� �����
class UDPHeader {
private:
	UDPH *header;
public:
	UDPHeader(int ipSize, char *packet);
	int getDesPort();
	int getSrcPort();
	int getUdpLength();
	int getUdpChecksum();
};

//DNSHeader Ŭ���� �����
class DNSHeader {
private:
	DNSH *header;
public:
	DNSHeader();
	DNSHeader(int headerSize, char *packet);
	int getQCount();
	int getAnsCount(); 
	int getAuthCount();
	int getAddCount();
};
#endif