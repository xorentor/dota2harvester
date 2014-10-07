#ifndef _CLIENT_H_
#define _CLIENT_H_

#ifndef UNICODE
#define UNICODE
#endif

#define DEFAULT_BUFLEN 	2048

class Client {

public:
    Client();
    ~Client();

    int sendData( char *data, const int lSize );
    int initClient( const char *ip, const int port );
    int closeClient();

    int connected;

private:
    int ConnectSocket;
};

#endif
