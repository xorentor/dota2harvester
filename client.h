/*
M$ file
*/
#ifndef _CLIENT_H_
#define _CLIENT_H_

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#define DEFAULT_BUFLEN 	2048
#define DEFAULT_PORT 	5778	
#define DEFAULT_IP 		"192.168.11.57"	

int sendData( char *data, const int lSize );
int initClient();
int closeClient();

#endif