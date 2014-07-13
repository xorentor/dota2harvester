/*
M$ file
*/
#include "common.h"
#include "d2h.h"
#include "client.h"

//  Forward declarations:
BOOL GetProcessList( );
BOOL ListProcessModules( DWORD dwPID, HANDLE *hnd );
BOOL ListProcessThreads( DWORD dwOwnerPID );
void printError( TCHAR* msg );

int main( void )
{
  GetProcessList( );
  return 0;
}

BOOL GetProcessList( )
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  //DWORD dwPriorityClass;

  // Take a snapshot of all processes in the system.
  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
  if( hProcessSnap == INVALID_HANDLE_VALUE )
  {
    //printError( TEXT("CreateToolhelp32Snapshot (of processes)") );
	printf( "error: CreateToolhelp32Snapshot (of processes)" );
    return( FALSE );
  }

  // Set the size of the structure before using it.
  pe32.dwSize = sizeof( PROCESSENTRY32 );

  if( !Process32First( hProcessSnap, &pe32 ) )
  {
	printf( "error: Process32First");
    CloseHandle( hProcessSnap );         
    return( FALSE );
  }

  do
  {
	if( strcmp( pe32.szExeFile, "dota.exe" ) != 0 )
		continue;
	
	//if( pe32.th32ProcessID != 420 )
	//		continue;	
	
	printf( "\n\n=====================================================" );
	printf( "\n Dota2 Harvester beta, build 04082013" );
	printf( "\n=====================================================\n" );
	printf( "\n  Process ID        = 0x%08X\n", (unsigned int)pe32.th32ProcessID );

    // Retrieve the priority class.
    //dwPriorityClass = 0;
    hProcess = OpenProcess( PROCESS_VM_READ, false, pe32.th32ProcessID );
    if( hProcess == NULL )
      //printError( TEXT("OpenProcess") );
	  printf( "error: OpenProcess" );
    else
    {
		//printf("OpenProcess fine");
		/*
      dwPriorityClass = GetPriorityClass( hProcess );
      if( !dwPriorityClass )
        printError( TEXT("GetPriorityClass") );
		*/
    }
	/*
	int addr0 = 0x64E30000 + 0x1EAFDA8;
	ReadProcessMemory(hProcess, (LPCVOID)addr_, &addr_ , 4, NULL); 
	int addr1 = addr_;
	ReadProcessMemory(hProcess, (LPCVOID)(addr1 + 14), &addr1 , 4, NULL); 
	printf( "addr1: %p\n", addr0 );
	
		int r = 0;
		int offset0 = 0x1EAFDA8;
		int offset1 = 0x14;
		int offset2 = 0;
		int offset3 = 0x824;
		int myaddr = FindPointerAddr(hProcess, 0x64E30000, 1, &r, offset0 );
	*/	
	
	
	/*
    _tprintf( TEXT("\n  Process ID        = 0x%08X"), pe32.th32ProcessID );
    _tprintf( TEXT("\n  Thread count      = %d"),   pe32.cntThreads );
    _tprintf( TEXT("\n  Parent process ID = 0x%08X"), pe32.th32ParentProcessID );
    _tprintf( TEXT("\n  Priority base     = %d"), pe32.pcPriClassBase );
	*/
	/*
    if( dwPriorityClass )
      _tprintf( TEXT("\n  Priority class    = %d"), dwPriorityClass );
	*/

    // List the modules and threads associated with this process
    ListProcessModules( pe32.th32ProcessID, &hProcess );
    ListProcessThreads( pe32.th32ProcessID );
	
	 CloseHandle( hProcess );

  } while( Process32Next( hProcessSnap, &pe32 ) );

  CloseHandle( hProcessSnap );
  return( TRUE );
}


BOOL ListProcessModules( DWORD dwPID, HANDLE *hnd )
{
  HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
  MODULEENTRY32 me32;

  // Take a snapshot of all modules in the specified process.
  hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, dwPID );
  if( hModuleSnap == INVALID_HANDLE_VALUE )
  {
    //printError( TEXT("CreateToolhelp32Snapshot (of modules)") );
	printf( "CreateToolhelp32Snapshot (of modules)" );
    return( FALSE );
  }

  // Set the size of the structure before using it.
  me32.dwSize = sizeof( MODULEENTRY32 );

  // Retrieve information about the first module,
  // and exit if unsuccessful
  if( !Module32First( hModuleSnap, &me32 ) )
  {
    //printError( TEXT("Module32First") );  // show cause of failure
	printf( "Module32First" );
    CloseHandle( hModuleSnap );           // clean the snapshot object
    return( FALSE );
  }

  // Now walk the module list of the process,
  // and display information about each module
  do
  {
  	if( strcmp( me32.szModule, "client.dll" ) == 0 ) {	
		//printf( "addr: %x\n", me32.modBaseAddr );
		D2H( hnd, &me32.modBaseAddr );
	}

		
	/*
    _tprintf( TEXT("\n\n     MODULE NAME:     %s"),   me32.szModule );
    _tprintf( TEXT("\n     Executable     = %s"),     me32.szExePath );
    _tprintf( TEXT("\n     Process ID     = 0x%08X"),         me32.th32ProcessID );
    _tprintf( TEXT("\n     Ref count (g)  = 0x%04X"),     me32.GlblcntUsage );
    _tprintf( TEXT("\n     Ref count (p)  = 0x%04X"),     me32.ProccntUsage );
    _tprintf( TEXT("\n     Base address   = 0x%08X"), (DWORD) me32.modBaseAddr );
    _tprintf( TEXT("\n     Base size      = %d"),             me32.modBaseSize );
	*/
  } while( Module32Next( hModuleSnap, &me32 ) );

  CloseHandle( hModuleSnap );
  return( TRUE );
}

BOOL ListProcessThreads( DWORD dwOwnerPID ) 
{ 
  HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
  THREADENTRY32 te32; 
 
  // Take a snapshot of all running threads  
  hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 ); 
  if( hThreadSnap == INVALID_HANDLE_VALUE ) 
    return( FALSE ); 
 
  // Fill in the size of the structure before using it. 
  te32.dwSize = sizeof(THREADENTRY32); 
 
  // Retrieve information about the first thread,
  // and exit if unsuccessful
  if( !Thread32First( hThreadSnap, &te32 ) ) 
  {
    //printError( TEXT("Thread32First") ); // show cause of failure
	printf( "Thread32First" );
    CloseHandle( hThreadSnap );          // clean the snapshot object
    return( FALSE );
  }

  // Now walk the thread list of the system,
  // and display information about each thread
  // associated with the specified process
  do 
  { 
    if( te32.th32OwnerProcessID == dwOwnerPID )
    {
	/*
      _tprintf( TEXT("\n\n     THREAD ID      = 0x%08X"), te32.th32ThreadID ); 
      _tprintf( TEXT("\n     Base priority  = %d"), te32.tpBasePri ); 
      _tprintf( TEXT("\n     Delta priority = %d"), te32.tpDeltaPri ); 
      _tprintf( TEXT("\n"));
		*/
    }
  } while( Thread32Next(hThreadSnap, &te32 ) ); 

  CloseHandle( hThreadSnap );
  return( TRUE );
}

void printError( TCHAR* msg )
{
  DWORD eNum;
  TCHAR sysMsg[256];
  TCHAR* p;

  eNum = GetLastError( );
  FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL, eNum,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         sysMsg, 256, NULL );

  // Trim the end of the line and terminate it with a null
  p = sysMsg;
  while( ( *p > 31 ) || ( *p == 9 ) )
    ++p;
  do { *p-- = 0; } while( ( p >= sysMsg ) &&
                          ( ( *p == '.' ) || ( *p < 33 ) ) );

  // Display the message
  _tprintf( TEXT("\n  WARNING: %s failed with error %lu (%s)"), msg, eNum, sysMsg );
}
