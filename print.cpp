#include "print.h"

Print::Print(FILE *log) {
	if (log == NULL)
	{
		printf("Unable to create file.");
		exit(1);
	}
	this->logFile = log;
}

void Print::fPrintIp(IPHeader *ip) {
	SOCKADDR_IN source, dest;

	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = ip->getSrcaddr();

	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip->getDesaddr();
	fprintf(logFile, "IP Header\n");
	fprintf(logFile, " |-IP Version : %d\n", ip->getIpVer());
	fprintf(logFile, " |-IP Header Length : %d DWORDS or %d Bytes\n", ip->getIpHLen(), (ip->getIpHLen()) * 4);
	fprintf(logFile, " |-Type Of Service : %d\n", ip->getIpTos());
	fprintf(logFile, " |-IP Total Length : %d Bytes(Size of Packet)\n", ntohs(ip->getIpLength()));
	fprintf(logFile, " |-Identification : %d\n", ntohs(ip->getIpId()));
	fprintf(logFile, " |-TTL : %d\n", ip->getTTL());
	fprintf(logFile, " |-Protocol : %d\n", ip->getProtocol());
	fprintf(logFile, " |-Checksum : %d\n", ntohs(ip->getIpChecksum()));
	fprintf(logFile, " |-Source IP : %s\n", inet_ntoa(source.sin_addr));
	fprintf(logFile, " |-Destination IP : %s\n", inet_ntoa(dest.sin_addr));
	fprintf(logFile, "\n");
}

void Print::close() {
	if (fclose(logFile) == -1)
	{
		printf("파일 닫기 에러");
		exit(1);
	}
}

void Print::fPrintTcp(IPHeader *ip, TCPHeader *tcp) {
	fPrintIp(ip);

	fprintf(logFile, "\n");
	fprintf(logFile, "TCP Header\n");
	fprintf(logFile, " |-Source Port : %d\n", ntohs(tcp->getSrcPort()));
	fprintf(logFile, " |-Destination Port : %d\n", ntohs(tcp->getDesPort()));
	fprintf(logFile, " |-Sequence Number : %d\n", ntohl(tcp->getSeqNo()));
	fprintf(logFile, " |-Acknowledge Number : %d\n", ntohl(tcp->getAckNo()));
	fprintf(logFile, " |-Header Length : %d DWORDS or %d BYTES\n"
		, tcp->getTcpLength(), tcp->getTcpLength() * 4);
	fprintf(logFile, " |-Urgent Flag : %d\n", tcp->getUrg());
	fprintf(logFile, " |-Acknowledgement Flag : %d\n", tcp->getAck());
	fprintf(logFile, " |-Push Flag : %d\n", tcp->getPush());
	fprintf(logFile, " |-Reset Flag : %d\n", tcp->getRes());
	fprintf(logFile, " |-Synchronise Flag : %d\n", tcp->getSyn());
	fprintf(logFile, " |-Finish Flag : %d\n", tcp->getFin());
	fprintf(logFile, " |-Window : %d\n", ntohs(tcp->getWin()));
	fprintf(logFile, " |-Checksum : %d\n", ntohs(tcp->getChecksum()));
	fprintf(logFile, " |-Urgent Pointer : %d\n", tcp->getUrgPointer());
	fprintf(logFile, "\n");
}

void Print::fPrintUdp(IPHeader *ip, UDPHeader *udp) {
	fPrintIp(ip);
	fprintf(logFile, "\n");
	fprintf(logFile, "\nUDP Header\n");
	fprintf(logFile, " |-Source Port : %d\n", ntohs(udp->getSrcPort()));
	fprintf(logFile, " |-Destination Port : %d\n", ntohs(udp->getDesPort()));
	fprintf(logFile, " |-UDP Length : %d\n", ntohs(udp->getUdpLength()));
	fprintf(logFile, " |-UDP Checksum : %d\n", ntohs(udp->getUdpChecksum()));
	fprintf(logFile, "\n");
}

void Print::fPrintDns(DNSHeader *dns) {
	fprintf(logFile, "\nThe response contains : ");
	fprintf(logFile, "\n %d Questions.", ntohs(dns->getQCount()));
	fprintf(logFile, "\n %d Answers.", ntohs(dns->getAnsCount()));
	fprintf(logFile, "\n %d Authoritative Servers.", ntohs(dns->getAuthCount()));
	fprintf(logFile, "\n %d Additional records.\n\n", ntohs(dns->getAddCount()));

}

void Print::fPrintPayload(char *app) {
	fprintf(logFile, "\n%s\n", app);
}
void Print::fPrintDump(char *app, int size) {


	for (int i = 0; i < size; i++)
	{
		if (i != 0 && i % 16 == 0)   //if one line of hex printing is complete...
		{
			for (int j = i - 16; j < i; j++)
			{
				if (app[j] >= 32 && app[j] <= 128) {
					fprintf(logFile, "%c", (unsigned char)app[j]); //if its a number or alphabet
				}
				else {
					fprintf(logFile, "."); //otherwise print a dot

				}
			}
			fprintf(logFile, "\n");
		}

		if (i % 16 == 0) {
			fprintf(logFile, "	");
		}

		fprintf(logFile, " %02X", (unsigned int)app[i]);


		if (i == size - 1)  //print the last spaces
		{
			for (int j = 0; j < 15 - i % 16; j++) {
				fprintf(logFile, "   "); //extra spaces
			}

			fprintf(logFile, "         ");


			for (int j = i - i % 16; j <= i; j++)
			{
				if (app[j] >= 32 && app[j] <= 128) {
					fprintf(logFile, "%c", (unsigned char)app[j]);
				}
				else {
					fprintf(logFile, ".");

				}
			}
			fprintf(logFile, "\n");
		}
	}

}

void Print::printTcp(IPHeader *ip, TCPHeader *tcp) {
	SOCKADDR_IN source, dest;

	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = ip->getSrcaddr();

	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip->getDesaddr();

	printf("TCP		%s		%s		%d		%d		%d		%d\n", inet_ntoa(source.sin_addr), inet_ntoa(dest.sin_addr), ntohs(tcp->getSrcPort()), ntohs(tcp->getDesPort()), ntohs(tcp->getSeqNo()), ntohs(tcp->getAckNo()));
}
void Print::printUdp(IPHeader *ip, UDPHeader *udp) {
	SOCKADDR_IN source, dest;

	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = ip->getSrcaddr();

	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip->getDesaddr();

	printf("UDP		%s		%s		%d		%d\n", inet_ntoa(source.sin_addr), inet_ntoa(dest.sin_addr), ntohs(udp->getSrcPort()), ntohs(udp->getDesPort()));
}

void Print::printApp(IPHeader *ip, TCPHeader *tcp, const char *appHeader) {
	SOCKADDR_IN source, dest;

	memset(&source, 0, sizeof(source));
	source.sin_addr.s_addr = ip->getSrcaddr();

	memset(&dest, 0, sizeof(dest));
	dest.sin_addr.s_addr = ip->getDesaddr();

	printf("%s		%s		%s		%d		%d		%d		%d\n", appHeader, inet_ntoa(source.sin_addr), inet_ntoa(dest.sin_addr), ntohs(tcp->getSrcPort()), ntohs(tcp->getDesPort()), ntohs(tcp->getSeqNo()), ntohs(tcp->getAckNo()));
}

void Print::printMain() {
	printf("=======================================================================================================================\n");
	printf("프로토콜	출발IP			목적IP		    출발Port		목적Port	SeqNo		AckNo\n");
	printf("=======================================================================================================================\n\n");
}