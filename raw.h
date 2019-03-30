#pragma once
#ifndef RAW_H
#define RAW_H
//각각의 프로토콜 헤더 구조체와
//프로토콜 별로 사용하는 포트 번호가 정의되어 있습니다.

#include <vector>

#define HTTP 80
#define DNS 53
#define FTP_DATA 20
#define FTP_CONTROLL 21
#define TELNET 23
#define TCP 6
#define UDP 17

typedef struct ip
{
	unsigned char ipHeaderLength : 4; // 4-bit header length (in 32-bit words) normally=5 (Means 20 Bytes may be 24 also)
	unsigned char ipVer : 4; // 4-bit IPv4 version
	unsigned char ipTos; // IP type of service
	unsigned short ipTotalLength; // Total length
	unsigned short ipId; // Unique identifier

	unsigned char ipFragOffset : 5; // Fragment offset field

	unsigned char ipMoreFragment : 1;
	unsigned char ipDontFragment : 1;
	unsigned char ipReservedZero : 1;

	unsigned char ipFragOffset1; //fragment offset

	unsigned char ipTTL; // Time to live
	unsigned char ipProtocol; // Protocol(TCP,UDP etc)
	unsigned short ipChecksum; // IP checksum
	unsigned int ipSrcaddr; // Source address
	unsigned int ipDestaddr; // Source address
} IPV4H;

typedef struct tcp
{
	unsigned short sourcePort; // source port
	unsigned short destPort; // destination port
	unsigned int sequence; // sequence number - 32 bits
	unsigned int acknowledge; // acknowledgement number - 32 bits

	unsigned char ns : 1; //Nonce Sum Flag Added in RFC 3540.
	unsigned char reservedPart1 : 3; //according to rfc
	unsigned char dataOffset : 4; /*The number of 32-bit words in the TCP header.
	This indicates where the data begins.
	The length of the TCP header is always a multiple
	of 32 bits.*/

	unsigned char fin : 1; //Finish Flag
	unsigned char syn : 1; //Synchronise Flag
	unsigned char rst : 1; //Reset Flag
	unsigned char psh : 1; //Push Flag
	unsigned char ack : 1; //Acknowledgement Flag
	unsigned char urg : 1; //Urgent Flag

	unsigned char ecn : 1; //ECN-Echo Flag
	unsigned char cwr : 1; //Congestion Window Reduced Flag

	////////////////////////////////

	unsigned short window; // window
	unsigned short checksum; // checksum
	unsigned short urgentPointer; // urgent pointer
} TCPH;

typedef struct udp
{
	unsigned short sourcePort; // Source port no.
	unsigned short destPort; // Dest. port no.
	unsigned short udpLength; // Udp packet length
	unsigned short udpChecksum; // Udp checksum (optional)
} UDPH;

typedef struct dns
{
	unsigned short id; // identification number

	unsigned char rd : 1; // recursion desired
	unsigned char tc : 1; // truncated message
	unsigned char aa : 1; // authoritive answer
	unsigned char opcode : 4; // purpose of message
	unsigned char qr : 1; // query/response flag

	unsigned char rcode : 4; // response code
	unsigned char cd : 1; // checking disabled
	unsigned char ad : 1; // authenticated data
	unsigned char z : 1; // its z! reserved
	unsigned char ra : 1; // recursion available

	unsigned short qCount; // number of question entries
	unsigned short ansCount; // number of answer entries
	unsigned short authCount; // number of authority entries
	unsigned short addCount; // number of resource entries
} DNSH;
#endif