#include "packet.h"
#include "print.h"
#include <iostream>
#include <WinSock2.h>

Packet::Packet(char *packet,Print *print, int size) {
	ip = new IPHeader(packet);
	int ipLen = ip->getIpLength() * 4;
	int tcpLen;
	int udpLen;
	switch (ip->getProtocol())
	{
		
	case TCP: // TCP ��������
		tcpCheck = true;
		tcp = new TCPHeader(ipLen, packet);
		tcpLen = tcp->getTcpLength() * 4;
		switch (this->getPort(ntohs(tcp->getDesPort()),ntohs(tcp->getSrcPort())))
		{
		case HTTP: //HTTP ��Ʈ
			setTcpPayload(packet, ipLen); 
			print->fPrintTcp(ip, tcp);
			print->fPrintPayload(app);
			print->fPrintDump(app, size - ipLen - tcpLen);
			Print::printApp(ip, tcp, "HTTP");
			break;
		case FTP_DATA: //FTP ������ ��Ʈ
			setTcpPayload(packet, ipLen);
			Print::printApp(ip, tcp, "FTP");
			break;
		case FTP_CONTROLL: //FTP ���� ��Ʈ
			setTcpPayload(packet, ipLen);
			Print::printApp(ip, tcp, "FTP");
			break;
		case TELNET: //Telnet ��Ʈ
			setTcpPayload(packet, ipLen);
			Print::printApp(ip, tcp, "TELNET");
			break;
		default:
			//Print::printTcp(ip, tcp);
			break;
		}
		break;
		
	case UDP: // UDP ��������
		udpCheck = true;
		udp = new UDPHeader(ipLen, packet);
		udpLen = sizeof(UDPH);
		switch (this->getPort(ntohs(udp->getDesPort()), ntohs(udp->getSrcPort())))
		{
		case DNS:
			dns = new DNSHeader(ipLen + udpLen, packet);
			setUdpPayload(packet, ipLen);
			Print::printUdp(ip, udp);
			print->fPrintDns(dns);
			//print->fPrintDump(app, size - ipLen - udpLen);
			//printf("\nThe response contains : ");
			//printf("\n %d Questions.", ntohs(dns->getQCount()));
			//printf("\n %d Answers.", ntohs(dns->getAnsCount()));
			//printf("\n %d Authoritative Servers.", ntohs(dns->getAuthCount()));
			//printf("\n %d Additional records.\n\n", ntohs(dns->getAddCount()));
			//printf("%s\n", dnsPayload);
			break;
		}
		break;

	default: // ��Ÿ ��������
		break;
	}
	


}
Packet::~Packet() {
	delete ip;

	if (this->tcpCheck)
		delete tcp;

	if(this->udpCheck)
		delete udp;
	delete[] app;
}
char* Packet::getPayload() {
	return this->app;
}
void Packet::setTcpPayload(char *packet, int ipLen) { // ��Ŷ�� ���̷ε� �κ��� �������ݴϴ�.

	app = (packet + ipLen + tcp->getTcpLength() * 4);
	//app = new char[(sizeof(char) * strlen(packet + ipLen + tcp->getTcpLength() * 4) + 1)];
	//memset(app, 0, sizeof(app));
	//strcpy(app, (char*)(packet + ipLen + (tcp->getTcpLength() * 4)));
	
}
void Packet::setUdpPayload(char *packet, int ipLen) { // ��Ŷ�� ���̷ε� �κ��� �������ݴϴ�.

	app = (packet + ipLen + udp->getUdpLength() * 4);
	//app = new char[(sizeof(char) * strlen(packet + ipLen + udp->getUdpLength() * 4) + 1)];
	//memset(this->app, 0, sizeof(app));
	//strcpy(this->app, (char*)(packet + ipLen + (udp->getUdpLength() * 4)));

}
int Packet::getPort(int dest, int source) {

	if (dest == HTTP || source == HTTP)
		return HTTP;

	if (dest == FTP_DATA || source == FTP_DATA)
		return FTP_DATA;

	if (dest == FTP_CONTROLL || source == FTP_CONTROLL)
		return FTP_CONTROLL;

	if (dest == TELNET || source == TELNET)
		return TELNET;

	if (dest == DNS || source == DNS)
		return DNS;
}
void Packets::add(Packet *temp) {
	this->list.push_back(temp);
}

Packet* Packets::getPacket(int index) {
	return this->list[index];
}