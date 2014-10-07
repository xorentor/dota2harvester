/*
M$ file
*/
#include "common.h"
#include "client.h"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

static SOCKET ConnectSocket = INVALID_SOCKET;

int initClient()
{
    int iResult;
    WSADATA wsaData;
    
    struct sockaddr_in clientService; 
    
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //----------------------
    // Create a SOCKET for connecting to server
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr( DEFAULT_IP );
    clientService.sin_port = htons( DEFAULT_PORT );

    //----------------------
    // Connect to server.
    iResult = connect( ConnectSocket, (SOCKADDR*) &clientService, sizeof(clientService) );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"connect failed with error: %d\n", WSAGetLastError() );
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
  }
	return 0;
}

int sendData( char *data, const int lSize ) {
	int iResult;
	//char recvbuf[DEFAULT_BUFLEN];
	//int recvbuflen = DEFAULT_BUFLEN;
    //----------------------
    // Send an initial buffer
    iResult = send( ConnectSocket, data, lSize, 0 );
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %d\n", iResult);


	/*
    // Receive until the peer closes the connection
    do {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
            wprintf(L"Bytes received: %d\n", iResult);
        else if ( iResult == 0 )
            wprintf(L"Connection closed\n");
        else
            wprintf(L"recv failed with error: %d\n", WSAGetLastError());

    } while( iResult > 0 );
	*/
	
    return 0;
}

int closeClient()
{
	int iResult;

	// shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
	
    // close the socket
    iResult = closesocket(ConnectSocket);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"close failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    WSACleanup();
	return 0;
}

/*
// do this later
char *GameIDFile( char *gameId )
{
	FILE *pFile;
	int lSize;

	pFile = fopen( tmp , "r" );
	if( pFile == NULL )
		return NULL;
		
	fseek( pFile, 0, SEEK_END );
	lSize = ftell( pFile );
	rewind( pFile );	
	
	// maxsize of gameId
	if( lSize > 32 )
		lSize = 32;
	
	result = fread( gameId, 1, lSize, pFile );
	
	fclose( pFile );
	
	return gameId;
}

void GetGameID( char *gameId )
{	
	
	if( ( GameIDFile( gameId ) ) == NULL ) {
		
	}

}
*/