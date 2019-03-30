#include "header.h"

//IPHeader 클래스 구현부
IPHeader::IPHeader(char *packet) {
	this->header = (IPV4H *)packet;
}

int IPHeader::getDesaddr() {
	return this->header->ipDestaddr;
}

int IPHeader::getSrcaddr() {
	return this->header->ipSrcaddr;
}

int IPHeader::getProtocol() {
	return this->header->ipProtocol;
}

int IPHeader::getIpLength() {
	return this->header->ipHeaderLength;
}

int IPHeader::getIpVer() {
	return this->header->ipVer;
}
int IPHeader::getIpTos() {
	return this->header->ipTos;
}

int IPHeader::getIpChecksum() {
	return this->header->ipChecksum;
}
int IPHeader::getIpHLen() {
	return this->header->ipHeaderLength;
}

int IPHeader::getIpId() {
	return this->header->ipId;
}

int IPHeader::getTTL() {
	return this->header->ipTTL;
}

//TCPHeader 클래스 구현부
TCPHeader::TCPHeader(int ipSize, char *packet) {
	this->header = (TCPH*)(packet + ipSize);
}

int TCPHeader::getDesPort() {
	return this->header->destPort;
}

int TCPHeader::getSrcPort() {
	return this->header->sourcePort;
}

int TCPHeader::getTcpLength() {
	return this->header->dataOffset;
}

int TCPHeader::getSeqNo(){
	return this->header->sequence;
}

int TCPHeader::getAckNo(){
	return this->header->acknowledge;
}

int TCPHeader::getUrg() {
	return this->header->urg;
}

int TCPHeader::getAck() {
	return this->header->ack;
}

int TCPHeader::getPush() {
	return this->header->psh;
}

int TCPHeader::getRes() {
	return this->header->rst;
}

int TCPHeader::getSyn() {
	return this->header->syn;
}

int TCPHeader::getFin() {
	return this->header->fin;
}

int TCPHeader::getWin() {
	return this->header->window;
}

int TCPHeader::getChecksum() {
	return this->header->checksum;
}

int TCPHeader::getUrgPointer() {
	return this->header->urgentPointer;
}
//UDPHeader 클래스 구현부
UDPHeader::UDPHeader(int ipSize, char *packet) {
	this->header = (UDPH*)(packet + ipSize);
}

int UDPHeader::getDesPort() {
	return this->header->destPort;
}

int UDPHeader::getSrcPort() {
	return this->header->sourcePort;
}

int UDPHeader::getUdpLength() {
	return this->header->udpLength;
}

int UDPHeader::getUdpChecksum() {
	return this->header->udpChecksum;
}
DNSHeader::DNSHeader(){}
DNSHeader::DNSHeader(int headerSize, char *packet)
{
	this->header = (DNSH*)(packet + headerSize);
}
int DNSHeader::getQCount() {
	return this->header->qCount;
}

int DNSHeader::getAnsCount(){
	return this->header->ansCount;
}

int DNSHeader::getAuthCount() {
	return this->header->authCount;
}

int DNSHeader::getAddCount() {
	return this->header->addCount;
}