#include <QDebug>
#include <QThread>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <TlHelp32.h>
#include <time.h>

#include "d2h.h"
#include "client.h"
#include "worker.h"

static int ward_index;
static int courier_index;
static Ward_t wards[ 16 ];
static Tower_t towers[ 22 ];
static Rax_t rax[ 12 ];
static Courier_t couriers[ 8 ];
static GeneralInfo_t gi;
static Player0_t p[ HEROES_GAME_TOTAL ];
static const Hero_t heroes[] = {
    {	"npc_dota_hero_antimage", 1 },
    {	"npc_dota_hero_axe", 2 },
    {	"npc_dota_hero_bane", 3 },
    {	"npc_dota_hero_bloodseeker", 4 },
    {	"npc_dota_hero_crystal_maiden", 5 },
    {	"npc_dota_hero_drow_ranger", 6, },
    {	"npc_dota_hero_earthshaker", 7 },
    {	"npc_dota_hero_juggernaut", 8 },
    {	"npc_dota_hero_mirana", 9 },
    {	"npc_dota_hero_morphling", 10 },
    {	"npc_dota_hero_nevermore", 11 },
    {	"npc_dota_hero_phantom_lancer", 12 },
    {	"npc_dota_hero_puck", 13 },
    {	"npc_dota_hero_pudge", 14 },
    {	"npc_dota_hero_razor", 15 },
    {	"npc_dota_hero_sand_king", 16 },
    {	"npc_dota_hero_storm_spirit", 17 },
    {	"npc_dota_hero_sven", 18 },
    {	"npc_dota_hero_tiny", 19 },
    {	"npc_dota_hero_vengefulspirit", 20 },
    {	"npc_dota_hero_windrunner", 21 },
    {	"npc_dota_hero_zuus", 22 },
    {	"npc_dota_hero_kunkka", 23 },
    {	"npc_dota_hero_lina", 25 },
    {	"npc_dota_hero_lich", 31 },
    {	"npc_dota_hero_lion", 26 },
    {	"npc_dota_hero_shadow_shaman", 27 },
    {	"npc_dota_hero_slardar", 28 },
    {	"npc_dota_hero_tidehunter", 29 },
    {	"npc_dota_hero_witch_doctor", 30 },
    {	"npc_dota_hero_riki", 32 },
    {	"npc_dota_hero_enigma", 33 },
    {	"npc_dota_hero_tinker", 34 },
    {	"npc_dota_hero_sniper", 35 },
    {	"npc_dota_hero_necrolyte", 36 },
    {	"npc_dota_hero_warlock", 37 },
    {	"npc_dota_hero_beastmaster", 38 },
    {	"npc_dota_hero_queenofpain", 39 },
    {	"npc_dota_hero_venomancer", 40 },
    {	"npc_dota_hero_faceless_void", 41 },
    {	"npc_dota_hero_skeleton_king", 42 },
    {	"npc_dota_hero_death_prophet", 43 },
    {	"npc_dota_hero_phantom_assassin", 44 },
    {	"npc_dota_hero_pugna", 45 },
    {	"npc_dota_hero_templar_assassin", 46 },
    {	"npc_dota_hero_viper", 47 },
    {	"npc_dota_hero_luna", 48 },
    {	"npc_dota_hero_dragon_knight", 49 },
    {	"npc_dota_hero_dazzle", 50 },
    {	"npc_dota_hero_rattletrap", 51 },
    {	"npc_dota_hero_leshrac", 52 },
    {	"npc_dota_hero_furion", 53 },
    {	"npc_dota_hero_life_stealer", 54 },
    {	"npc_dota_hero_dark_seer", 55 },
    {	"npc_dota_hero_clinkz", 56 },
    {	"npc_dota_hero_omniknight", 57 },
    {	"npc_dota_hero_enchantress", 58 },
    {	"npc_dota_hero_huskar", 59 },
    {	"npc_dota_hero_night_stalker", 60 },
    {	"npc_dota_hero_broodmother", 61 },
    {	"npc_dota_hero_bounty_hunter", 62 },
    {	"npc_dota_hero_weaver", 63 },
    {	"npc_dota_hero_jakiro", 64 },
    {	"npc_dota_hero_batrider", 65 },
    {	"npc_dota_hero_chen", 66 },
    {	"npc_dota_hero_spectre", 67 },
    {	"npc_dota_hero_doom_bringer", 69 },
    {	"npc_dota_hero_ancient_apparition", 68 },
    {	"npc_dota_hero_ursa", 70 },
    {	"npc_dota_hero_spirit_breaker", 71 },
    {	"npc_dota_hero_gyrocopter", 72 },
    {	"npc_dota_hero_alchemist", 73 },
    {	"npc_dota_hero_invoker", 74 },
    {	"npc_dota_hero_silencer", 75 },
    {	"npc_dota_hero_obsidian_destroyer", 76 },
    {	"npc_dota_hero_lycan", 77 },
    {	"npc_dota_hero_brewmaster", 78 },
    {	"npc_dota_hero_shadow_demon", 79 },
    {	"npc_dota_hero_lone_druid", 80 },
    {	"npc_dota_hero_chaos_knight", 81 },
    {	"npc_dota_hero_meepo", 82 },
    {	"npc_dota_hero_treant", 83 },
    {	"npc_dota_hero_ogre_magi", 84 },
    {	"npc_dota_hero_undying", 85 },
    {	"npc_dota_hero_rubick", 86 },
    {	"npc_dota_hero_disruptor", 87 },
    {	"npc_dota_hero_nyx_assassin", 88 },
    {	"npc_dota_hero_naga_siren", 89 },
    {	"npc_dota_hero_keeper_of_the_l", 90 },
    {	"npc_dota_hero_wisp", 91 },
    {	"npc_dota_hero_visage", 92 },
    {	"npc_dota_hero_slark", 93 },
    {	"npc_dota_hero_medusa", 94 },
    {	"npc_dota_hero_troll_warlord", 95 },
    {	"npc_dota_hero_centaur", 96 },
    {	"npc_dota_hero_magnataur", 97 },
    {	"npc_dota_hero_shredder", 98 },
    {	"npc_dota_hero_bristleback", 99 },
    {	"npc_dota_hero_tusk", 100 },
    {	"npc_dota_hero_skywrath_mage", 101 },
    {	"npc_dota_hero_abaddon", 102 },
    {	"npc_dota_hero_elder_titan", 103 },
    {	"npc_dota_hero_legion_commander", 104 },
    {	"npc_dota_hero_ember_spirit", 106 },
    {	"npc_dota_hero_earth_spirit", 107 },
    {	"npc_dota_hero_abyssal_underlord", 108 },
    {	"npc_dota_hero_terrorblade", 109 },
    {	"npc_dota_hero_phoenix", 110 }
};
static const int HEROES_ALL	= sizeof(heroes)/sizeof(*heroes);

Worker::Worker( struct guiobj_s ***fs, Client *client, QLineEdit *ip, QLineEdit *port ) : edits(fs), cl(client), ip(ip), port(port) {
    startParser = 0;
    GetProcessList();
}

Worker::~Worker() {
}

int __cmp( WCHAR *w, char *s ) {
    int i;
    for( i = 0; *w != 0; i++ ) {
        if( *w++ != *s++ ) {
            return 1;
        }
    }
    return 0;
}

bool Worker::GetProcessList()
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

  if( !Process32First( hProcessSnap, &pe32 ) ) {
    printf( "error: Process32First");
    //CloseHandle( hProcessSnap );
    return( FALSE );
  }

  do
  {

    if( __cmp( pe32.szExeFile, "dota.exe" ) != 0 ) {
        continue;
    }

/*
    WCHAR *tmp = pe32.szExeFile;
    while( tmp != 0 ) {
        printf("proc name [%c]", *tmp++ );
   }

   */
    //if( pe32.th32ProcessID != 2772 )
    //			continue;

    printf( "\n\n=====================================================" );
    printf( "\n Dota2 Harvester beta, build 04082013" );
    printf( "\n=====================================================\n" );
    printf( "\n  Process ID        = 0x%08X\n", (unsigned int)pe32.th32ProcessID );

    // Retrieve the priority class.
    //dwPriorityClass = 0;
    hProcess = OpenProcess( PROCESS_VM_READ, false, pe32.th32ProcessID );

    //hProcess = OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE|PROCESS_QUERY_INFORMATION,FALSE,pe32.th32ProcessID);
    if( hProcess == NULL )
      //printError( TEXT("OpenProcess") );
      printf( "error: OpenProcess" );
    else
    {
        printf( "found handle %d\n", hProcess);
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

     //CloseHandle( hProcess );

  } while( Process32Next( hProcessSnap, &pe32 ) );

  //CloseHandle( hProcessSnap );
  return( TRUE );
}


bool Worker::ListProcessModules( DWORD dwPID, HANDLE *hnd )
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
    //CloseHandle( hModuleSnap );           // clean the snapshot object
    return( FALSE );
  }

  // Now walk the module list of the process,
  // and display information about each module
  do
  {
   //   printf("p [%c][%x]\n", me32.szModule, me32.modBaseAddr );
    if( __cmp( me32.szModule, "client.dll" ) == 0 ) {
        //printf( "dll name: [%c] [%x]\n", me32.szModule, me32.modBaseAddr );
        //D2H( hnd, &me32.modBaseAddr );
        dhandle = *hnd;
        daddr = *(int*)&me32.modBaseAddr;
        startParser = 1;
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

  //CloseHandle( hModuleSnap );
  return( TRUE );
}

bool Worker::ListProcessThreads( DWORD dwOwnerPID )
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
    //CloseHandle( hThreadSnap );          // clean the snapshot object
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

  //CloseHandle( hThreadSnap );
  return( TRUE );
}

void Worker::run() {
    QString qs;

    while( 1==1 ) {
        if( startParser == 1 ) {
            parseData( dhandle, daddr );
        }

        sleep(1);
    }
}

void Worker::setGUI()
{
    int i, ptr;
    char tmp[ 128 ];
/*
    for( i = 0; i < 256; i++ ) {
        if( edits[0][i] != NULL ) {
            edits[0][i]->qe->setText("pl");
        }
    }

    for( i = 0; i < 256; i++ ) {
        if( edits[1][i] != NULL ) {
            edits[1][i]->qe->setText("tw");
        }
    }
    */

    ptr = 0;
#define GI(s)\
    memset( tmp, 0, sizeof( tmp ));\
    _itoa( s, tmp, 10 );\
    edits[0][ptr++]->qe->setText( tmp );

    GI(gi.score_rad);
    GI(gi.score_dire);
    GI(gi.gametime);
    GI(gi.roshan_hp);

    for( i = 0; i < 10; i++ ) {

        edits[0][ptr++]->qe->setText("playername");
        edits[0][ptr++]->qe->setText("hero");

        GI(p[ i ].misc_heroid);
        GI((int)p[ i ].x);
        GI((int)p[ i ].y);
        GI(p[i].side);
        GI(p[i].maxhp);
        GI(p[i].currenthp);
        GI(p[i].misc_kills);
        GI(p[i].misc_assists);
        GI(p[i].misc_deaths);
        GI(p[i].misc_level);
        GI(p[i].misc_ck);
        GI(p[i].misc_cd);
        GI(p[i].misc_totalgold);
        GI(p[i].misc_totalexp);
        GI(p[i].misc_currentg0);
        GI(p[i].misc_currentg1);
    }

    ptr = 0;
#define GI(s)\
    memset( tmp, 0, sizeof( tmp ));\
    _itoa( s, tmp, 10 );\
    edits[1][ptr++]->qe->setText( tmp );

    for( i = 0; i < 22; i++ ) {
        GI(towers[i].hp);
    }
}

void Worker::parseData( HANDLE hnd, int clientdll )
{
        int ptr = 0;
        char buff[ 32 ], buff1[ 32 ];
        int i;

        int offsets[ 16 ];
        int mem_herobasic;
        int mem_heroadv;
        int mem_heromisc;
        int mem_items;
        int mem_herogold_r;
        int mem_herogold_d;
        char gameid[ 32 ];

        printf( "handle [%x] base [%x]\n", hnd, clientdll );
        mem_herobasic = MEM_HEROBASIC;
        mem_heroadv = MEM_HEROADV;
        mem_heromisc = MEM_HEROMISC;
        mem_items = MEM_ITEMS;
        mem_herogold_r = MEM_HEROGOLD_R;
        mem_herogold_d = MEM_HEROGOLD_D;

#ifndef _TEST
        GetGameID( gameid );
#ifndef _DEBUG
        //if( initClient() != 0 )
        //    exit(0);
#endif


#ifndef _DEBUG
        while( 1==1 ) {
#else
        {
#endif
            memset( buff, 0, sizeof( buff ) );
            memset( buff1, 0, sizeof( buff1 ) );
            memset( p, 0, sizeof( p ) );
            memset( &gi, 0, sizeof( gi ) );
            memset( wards, 0, sizeof( wards ) );
            memset( towers, 0, sizeof( towers ) );
            memset( rax, 0, sizeof( rax ) );
            memset( couriers, 0, sizeof( couriers ) );
            ward_index = 0;
            courier_index = 0;

            offsets[ 0 ] = 0x308;
            gi.score_rad = ReadInt( &hnd, (void*)(clientdll + mem_herobasic), offsets, 1 );

            //printf( "score radiant %x %x %d\n", clientdll, (int)(clientdll + mem_herobasic), gi.score_rad);
            offsets[ 0 ] = 0x30c;
            gi.score_dire = ReadInt( &hnd, (void*)(clientdll + mem_herobasic), offsets, 1 );

            offsets[ 0 ] = 0x54;
            gi.gametime = ReadInt( &hnd, (void*)(clientdll + mem_herobasic), offsets, 1 );

#ifdef _DEBUG
            printf( "score radiant/dire: '%d' '%d' gametime: %d\n", gi.score_rad, gi.score_dire, gi.gametime );
            exit(0);
#endif
            ReadH( &hnd, (void*)(clientdll + mem_herobasic) );
            ReadMisc( &hnd, (void*)(clientdll + mem_heromisc) );

            for( i = 0; i < 2048; i++ ) {

                ptr = 0;
                ReadProcessMemory(hnd, (void*)(clientdll + mem_heroadv), &ptr , 4, NULL);
                ReadProcessMemory(hnd, (void*)((int)ptr + i * 8), &ptr , 4, NULL);
                ReadProcessMemory(hnd, (void*)((int)ptr + NPC_DOTA_HERO), buff, 32, NULL);

                if( memcmp( buff, "npc_dota_hero", 13 ) == 0 ) {
                    ReadHAdv( &hnd, (void*)(clientdll + mem_heroadv), i * 8 );
                } else if( memcmp( buff, "npc_dota_roshan", 15 ) == 0 ) {
                    ReadProcessMemory(hnd, (void*)(clientdll + mem_heroadv), &ptr , 4, NULL);
                    ReadProcessMemory(hnd, (void*)((int)ptr + i * 8), &ptr , 4, NULL);
                    ReadProcessMemory(hnd, (void*)((int)ptr + 0xf4), &gi.roshan_hp, 4, NULL);
                } else if( memcmp( buff, "npc_dota_goodguys_fort", 22 ) == 0 ) {
                    ReadProcessMemory(hnd, (void*)(clientdll + mem_heroadv), &ptr , 4, NULL);
                    ReadProcessMemory(hnd, (void*)((int)ptr + i * 8), &ptr , 4, NULL);
                    ReadProcessMemory(hnd, (void*)((int)ptr + 0xf4), &gi.rad_fort_hp, 4, NULL);
                } else if( memcmp( buff, "npc_dota_badguys_fort", 21 ) == 0 ) {
                    ReadProcessMemory(hnd, (void*)(clientdll + mem_heroadv), &ptr , 4, NULL);
                    ReadProcessMemory(hnd, (void*)((int)ptr + i * 8), &ptr , 4, NULL);
                    ReadProcessMemory(hnd, (void*)((int)ptr + 0xf4), &gi.dire_fort_hp, 4, NULL);
                } else if( memcmp( buff, "npc_dota_observer_wards", 23 ) == 0 ) {
                    ReadWard( &hnd, (void*)(clientdll + mem_heroadv), i * 8, 1 );
                } else if( memcmp( buff, "npc_dota_sentry_wards", 21 ) == 0 ) {
                    ReadWard( &hnd, (void*)(clientdll + mem_heroadv), i * 8, 2 );
                } else if( memcmp( buff, "npc_dota_courier", 16 ) == 0 ) {
                    ReadCourier( &hnd, (void*)(clientdll + mem_heroadv), i * 8 );
                } else {
                    ReadAncients( &hnd, (void*)(clientdll + mem_heroadv), i * 8, buff );
                }
            }


#ifdef _DEBUG
            printf( "towers: '%d'\n", gi.towers );
            printf( "rax: '%d'\n", gi.rax );
            printf( "fort: '%d'\n", gi.fort );
            printf( "fort0hp: '%d'\n", gi.rad_fort_hp );
            printf( "fort1hp: '%d'\n", gi.dire_fort_hp );
            printf( "roshan hp: '%d'\n", gi.roshan_hp );

            printf( "towers:\n");
            for( i = 0; i < 22; i++ ) {
                    printf("side: %d hp: %d x:%f y:%f\n", towers[ i ].side, towers[ i ].hp, towers[ i ].x, towers[ i ].y);
            }
            printf( "rax:\n");
            for( i = 0; i < 12; i++ ) {
                    printf("side: %d hp: %d x:%f y:%f\n", rax[ i ].side, rax[ i ].hp, rax[ i ].x, rax[ i ].y);
            }
            printf( "wards:\n");
            for( i = 0; i < 16; i++ ) {
                    printf("side: %d hp: %d x:%f y:%f\n", wards[ i ].side, wards[ i ].hp, wards[ i ].x, wards[ i ].y);
            }
            printf( "couriers:\n");
            for( i = 0; i < 8; i++ ) {
                    printf("side: %d hp: %d x:%f y:%f\n", couriers[ i ].side, couriers[ i ].hp, couriers[ i ].x, couriers[ i ].y);
            }
#endif

            ReadGold( &hnd, (void*)(clientdll + mem_herogold_r), (void*)(clientdll + mem_herogold_d) );

            // to actually get items dump, you must keep the ingame tab called ' ITEMS ' open
            // they are no present in the memory unless you ask for them or I just couldn't find them
            //
            // to get the correct item id, you have to subtract the number from dump by 637 ( this number changes, just double check it )
            // and compare it against http://dota2mobile.com/js/items.js
            ReadItems( &hnd, (void*)(clientdll + mem_items), 0x75 * 8 + 0x14 );

            //ExportAll( gameid );
            setGUI();

            Sleep( 50 );	// .5s
        }

        //closeClient();
        exit(0);
#else
        // testing here
        /*
        for( i = 0; i < 16384; i++ ) {
            ReadProcessMemory(*hnd, (void*)(clientdll + mem_heromisc), &ptr , 4, NULL);
            ReadProcessMemory(*hnd, (void*)((int)ptr + i * 4), &ptr , 4, NULL);
            printf( "T memory: %x value: \"%d\"\n", i*4, ptr);
        }
        */
        /*
        for( i = 0; i < 16384; i++ ) {
            ReadProcessMemory(*hnd, (void*)(clientdll + mem_herobasic), &ptr , 4, NULL);
            ReadProcessMemory(*hnd, (void*)((int)ptr + i * 4), &ptr , 4, NULL);
            printf( "T memory: %x value: \"%d\"\n", i*4, ptr);
        }
        */
        for( i = 0; i < 16384; i++ ) {
            ReadProcessMemory(*hnd, (void*)(clientdll + mem_heroadv), &ptr , 4, NULL);
            ReadProcessMemory(*hnd, (void*)((int)ptr + 0x1E8 *8), &ptr , 4, NULL);
            ReadProcessMemory(*hnd, (void*)((int)ptr + i * 4), buff , 32, NULL);
            printf( "T memory: %x value: %s\n", i*4, buff);
        }
#endif

}

void Worker::GetGameID( char *gameid )
{printf("Get last error: %d\n",GetLastError());
    int random_x = 0;

    memset( gameid, 0, sizeof( *gameid ) );
    srand( time(NULL) );
    random_x = rand() % 0xffff + 1;
    itoa( random_x, gameid, 10 );
}

int Worker::ReadInt( HANDLE *hnd, void *addr, int *ost, const int ost_num )
{
    int i;
    int value = 0;

    ReadProcessMemory( *hnd, addr, &value, 4, NULL);
    for( i = 0; i < ost_num; i++ ) {
        ReadProcessMemory( *hnd, (void *)((int )value + ost[ i ]), &value , 4, NULL);
    }

    return value;
}

float Worker::ReadFloat( HANDLE *hnd, void *addr, int *ost, const int ost_num )
{
    int i;
    int value;
    float rval;

    ReadProcessMemory( *hnd, addr, &value, 4, NULL);

    for( i = 0; i < ( ost_num - 1 ); i++ ) {
        ReadProcessMemory( *hnd, (void *)((int )value + ost[ i ]), &value , 4, NULL);
    }

    ReadProcessMemory( *hnd, (void *)((int )value + ost[ i ]), &rval , 4, NULL);

    return rval;
}

void Worker::ReadString( HANDLE *hnd, void *addr, int *ost, const int ost_num, char *buffer )
{
    int i;
    int value = 0;

    ReadProcessMemory( *hnd, addr, &value, 4, NULL);

    for( i = 0; i < ( ost_num - 1 ); i++ ) {
        ReadProcessMemory( *hnd, (void *)((int )value + ost[ i ]), &value , 4, NULL);
    }

    ReadProcessMemory( *hnd, (void *)((int )value + ost[ i ]), buffer , 32, NULL);
}


void Worker::ReadH( HANDLE *hnd, void *addr )
{
    int i;
    int offset;

    offset = 0x5e8;

    for( i = 0; i < HEROES_GAME_TOTAL; i++ ) {
        p[ i ].hero_slot = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_level = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_kills = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_deaths = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_assists = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_gold = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_ck = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_cd = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_ulticd_sec = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
        p[ i ].hero_dead_sec = ReadInt( hnd, addr, &offset, 1 );
        offset += 6 * 4;
        p[ i ].hero_id = ReadInt( hnd, addr, &offset, 1 );
        offset += 4;
#ifdef _DEBUG
        printf("\n=============\n");
        printf( "hero_slot: '%d' '%d'\n", i, p[ i ].hero_slot );
        printf( "hero_level: '%d' '%d'\n", i, p[ i ].hero_level );
        printf( "hero_kills: '%d' '%d'\n", i, p[ i ].hero_kills );
        printf( "hero_deaths: '%d' '%d'\n", i, p[ i ].hero_deaths );
        printf( "hero_assists: '%d' '%d'\n", i, p[ i ].hero_assists );
        printf( "hero_gold: '%d' '%d'\n", i, p[ i ].hero_gold );
        printf( "hero_ck: '%d' '%d'\n", i, p[ i ].hero_ck );
        printf( "hero_cd: '%d' '%d'\n", i, p[ i ].hero_cd );
        printf( "hero_id: '%d' '%d'\n", i, p[ i ].hero_id );
        printf( "hero_dead_sec: '%d' '%d'\n", i, p[ i ].hero_dead_sec );
        printf( "hero_ulticd_sec: '%d' '%d'\n", i, p[ i ].hero_ulticd_sec );
#endif
    }
}


Player0_t *Worker::GetHeroByID( const int id )
{
    int i;
    for( i = 0; i < HEROES_GAME_TOTAL; i++ ) {
        if( p[ i ].misc_heroid == id ) {
            return &p[ i ];
        }
    }

    return NULL;
}

void Worker::ReadGold( HANDLE *hnd, void *addr, void *addr1 )
{
    int i;
    int offsets[ 2 ];
    void *ca;

    offsets[ 0 ] = 0x760;
    offsets[ 1 ] = 0x7e0;

    for( i = 0; i < HEROES_GAME_TOTAL; i++ ) {
        if( i < 5 ) {
            ca = addr;
        } else {
            ca = addr1;
        }

        p[ i ].misc_currentg0 = ReadInt( hnd, ca, &offsets[ 0 ], 1 );
        offsets[ 0 ] += 4;

        p[ i ].misc_currentg1 += ReadInt( hnd, ca, &offsets[ 1 ], 1 );	// special reward gold
        offsets[ 1 ] += 4;

#ifdef _DEBUG
        printf( "misc_currentg0: '%d' '%d'\n", i, p[ i ].misc_currentg0 );
        printf( "misc_currentg1: '%d' '%d'\n", i, p[ i ].misc_currentg1 );
#endif
    }
}

void Worker::ReadMisc( HANDLE *hnd, void *addr )
{
    int i;
    char buffer[ 64 ];
    int offsets[ 16 ];

    offsets[ 0 ] = 0x76a;
    for( i = 0; i < HEROES_GAME_TOTAL; i++ ) {
        memset( buffer, 0, sizeof( buffer ) );
        ReadString( hnd, addr, offsets, 1, buffer );
        memcpy( p[ i ].playername, buffer, strlen( buffer ) );
        offsets[ 0 ] += 0x104;
#ifdef _DEBUG
//		printf( "playername: %s\n", p[ i ].playername );
#endif
    }
/*
*	these have been changed quite often lately
*   especially, reliable and unreliable gold figures have been moved somewhere else
*	and are no longer part of this structure ( someone needs to do the grunt work on these )
*/
    offsets[ 0 ] = 0x3214; 	// hero id
    offsets[ 1 ] = 0x32e4;	// assists
    offsets[ 2 ] = 0x330c;	// deaths
    offsets[ 3 ] = 0x335c;	// dead secs
    offsets[ 4 ] = 0x349c;	// hero level
    offsets[ 5 ] = 0x34ec; 	// creeps killed
    offsets[ 6 ] = 0x34c4;	// creeps denied
    offsets[ 7 ] = 0x45ec; 	// total gold
    offsets[ 8 ] = 0x45f4;  // total exp
    offsets[ 9 ] = 0x4c80;
    offsets[ 10 ] = 0x32bc;	// kills
    offsets[ 11 ] = 0x4d00;

    for( i = 0; i < HEROES_GAME_TOTAL; i++ ) {
        p[ i ].misc_heroid = ReadInt( hnd, addr, &offsets[ 0 ], 1 );
        offsets[ 0 ] += 4;

        p[ i ].misc_assists = ReadInt( hnd, addr, &offsets[ 1 ], 1 );
        offsets[ 1 ] += 4;

        p[ i ].misc_deaths = ReadInt( hnd, addr, &offsets[ 2 ], 1 );
        offsets[ 2 ] += 4;

        p[ i ].misc_dead_sec = ReadInt( hnd, addr, &offsets[ 3 ], 1 );
        offsets[ 3 ] += 4;

        p[ i ].misc_level = ReadInt( hnd, addr, &offsets[ 4 ], 1 );
        offsets[ 4 ] += 4;

        p[ i ].misc_ck = ReadInt( hnd, addr, &offsets[ 5 ], 1 );
        offsets[ 5 ] += 4;

        p[ i ].misc_cd = ReadInt( hnd, addr, &offsets[ 6 ], 1 );
        offsets[ 6 ] += 4;

        p[ i ].misc_totalgold = ReadInt( hnd, addr, &offsets[ 7 ], 1 );
        offsets[ 7 ] += 4;

        p[ i ].misc_totalexp = ReadInt( hnd, addr, &offsets[ 8 ], 1 );
        offsets[ 8 ] += 4;

        p[ i ].misc_kills = ReadInt( hnd, addr, &offsets[ 10 ], 1 );
        offsets[ 10 ] += 4;

#ifdef _DEBUG
        printf("\n=============\n");
        printf( "playername: %s\n", p[ i ].playername );
        printf( "misc_heroid: '%d' '%d'\n", i, p[ i ].misc_heroid );
        printf( "misc_assists: '%d' '%d'\n", i, p[ i ].misc_assists );
        printf( "misc_deaths: '%d' '%d'\n", i, p[ i ].misc_deaths );
        printf( "misc_level: '%d' '%d'\n", i, p[ i ].misc_level );
        printf( "misc_ck: '%d' '%d'\n", i, p[ i ].misc_ck );
        printf( "misc_cd: '%d' '%d'\n", i, p[ i ].misc_cd );
        printf( "misc_totalgold: '%d' '%d'\n", i, p[ i ].misc_totalgold );
        printf( "misc_totalexp: '%d' '%d'\n", i, p[ i ].misc_totalexp );
        printf( "misc_dead_sec: '%d' '%d'\n", i, p[ i ].misc_dead_sec );
        printf( "misc_kills: '%d' '%d'\n", i, p[ i ].misc_kills );

#endif
    }
}
#define READVARIOUS( b, i, s )\
    int o[ 2 ];\
    o[ 0 ] = s;\
    o[ 1 ] = 0xec;\
    b[ i ].side = ReadInt( hnd, addr, o, 2 );\
    o[ 1 ] = 0xf4;\
    b[ i ].hp = ReadInt( hnd, addr, o, 2 );\
    o[ 1 ] = 0xa8;\
    b[ i ].x = ReadFloat( hnd, addr, o, 2 );\
    o[ 1 ] = 0xac;\
    b[ i ].y = ReadFloat( hnd, addr, o, 2 );
void Worker::ReadCourier( HANDLE *hnd, void *addr, const int offset ) {
    if( courier_index == 7 ) {
        return;
    }
    READVARIOUS( couriers, courier_index, offset );
    courier_index++;
}

void Worker::ReadWard( HANDLE *hnd, void *addr, const int offset, const int type ) {
    if( ward_index == 15 ) {
        return;
    }
    READVARIOUS( wards, ward_index, offset );
    wards[ ward_index ].type = type;
    ward_index++;
}

void Worker::ReadRax( HANDLE *hnd, void *addr, const int offset, const int index ) {
    READVARIOUS( rax, index, offset );
}

void Worker::ReadTower( HANDLE *hnd, void *addr, const int offset, const int index ) {
    READVARIOUS( towers, index, offset );
}

void Worker::ReadAncients( HANDLE *hnd, void *addr, const int offset, char *buffer )
{
#define GIR(d) gi.rax |= (1<<d);
#define GIT(d) gi.towers |= (1<<d);

    if( memcmp( buffer, "npc_dota_goodguys_range_rax_bot", 31 ) == 0 ) {
        GIR(0);
        ReadRax( hnd, addr, offset, 0 );
    } else if( memcmp( buffer, "npc_dota_goodguys_melee_rax_bot", 31 ) == 0 ) {
        GIR(1);
        ReadRax( hnd, addr, offset, 1 );
    } else if( memcmp( buffer, "npc_dota_goodguys_range_rax_top", 31 ) == 0 ) {
        GIR(2);
        ReadRax( hnd, addr, offset, 2 );
    } else if( memcmp( buffer, "npc_dota_goodguys_melee_rax_top", 31 ) == 0 ) {
        GIR(3);
        ReadRax( hnd, addr, offset, 3 );
    } else if( memcmp( buffer, "npc_dota_goodguys_range_rax_mid", 31 ) == 0 ) {
        GIR(4);
        ReadRax( hnd, addr, offset, 4 );
    } else if( memcmp( buffer, "npc_dota_goodguys_melee_rax_mid", 31 ) == 0 ) {
        GIR(5);
        ReadRax( hnd, addr, offset, 5 );
    } else if( memcmp( buffer, "npc_dota_badguys_range_rax_bot", 30 ) == 0 ) {
        GIR(6);
        ReadRax( hnd, addr, offset, 6 );
    } else if( memcmp( buffer, "npc_dota_badguys_melee_rax_bot", 30 ) == 0 ) {
        GIR(7);
        ReadRax( hnd, addr, offset, 7 );
    } else if( memcmp( buffer, "npc_dota_badguys_range_rax_top", 30 ) == 0 ) {
        GIR(8);
        ReadRax( hnd, addr, offset, 8 );
    } else if( memcmp( buffer, "npc_dota_badguys_melee_rax_top", 30 ) == 0 ) {
        GIR(9);
        ReadRax( hnd, addr, offset, 9 );
    } else if( memcmp( buffer, "npc_dota_badguys_range_rax_mid", 30 ) == 0 ) {
        GIR(10);
        ReadRax( hnd, addr, offset, 10 );
    } else if( memcmp( buffer, "npc_dota_badguys_melee_rax_mid", 30 ) == 0 ) {
        GIR(11);
        ReadRax( hnd, addr, offset, 11 );
    } else if( memcmp( buffer, "npc_dota_goodguys_fort", 22 ) == 0 ) {
        gi.fort |= 0x1;
    } else if( memcmp( buffer, "npc_dota_badguys_fort", 21 ) == 0 ) {
        gi.fort |= 0x2;
    } else if( memcmp( buffer, "npc_dota_goodguys_tower4", 24 ) == 0 && !(gi.towers & 1) ) {
        GIT(0);
        ReadTower( hnd, addr, offset, 0 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower4", 24 ) == 0 ) {
        GIT(1);
        ReadTower( hnd, addr, offset, 1 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower3_bot", 28 ) == 0 ) {
        GIT(2);
        ReadTower( hnd, addr, offset, 2 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower3_top", 28 ) == 0 ) {
        GIT(3);
        ReadTower( hnd, addr, offset, 3 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower3_mid", 28 ) == 0 ) {
        GIT(4);
        ReadTower( hnd, addr, offset, 4 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower2_bot", 28 ) == 0 ) {
        GIT(5);
        ReadTower( hnd, addr, offset, 5 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower2_top", 28 ) == 0 ) {
        GIT(6);
        ReadTower( hnd, addr, offset, 6 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower2_mid", 28 ) == 0 ) {
        GIT(7);
        ReadTower( hnd, addr, offset, 7 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower1_bot", 28 ) == 0 ) {
        GIT(8);
        ReadTower( hnd, addr, offset, 8 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower1_top", 28 ) == 0 ) {
        GIT(9);
        ReadTower( hnd, addr, offset, 9 );
    } else if( memcmp( buffer, "npc_dota_goodguys_tower1_mid", 28 ) == 0 ) {
        GIT(10);
        ReadTower( hnd, addr, offset, 10 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower4", 23 ) == 0 && !(gi.towers & 0x800) ) {
        GIT(11);
        ReadTower( hnd, addr, offset, 11 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower4", 23 ) == 0 ) {
        GIT(12);
        ReadTower( hnd, addr, offset, 12 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower3_bot", 27 ) == 0 ) {
        GIT(13);
        ReadTower( hnd, addr, offset, 13 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower3_top", 27 ) == 0 ) {
        GIT(14);
        ReadTower( hnd, addr, offset, 14 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower3_mid", 27 ) == 0 ) {
        GIT(15);
        ReadTower( hnd, addr, offset, 15 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower2_bot", 27 ) == 0 ) {
        GIT(16);
        ReadTower( hnd, addr, offset, 16 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower2_top", 27 ) == 0 ) {
        GIT(17);
        ReadTower( hnd, addr, offset, 17 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower2_mid", 27 ) == 0 ) {
        GIT(18);
        ReadTower( hnd, addr, offset, 18 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower1_bot", 27 ) == 0 ) {
        GIT(19);
        ReadTower( hnd, addr, offset, 19 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower1_top", 27 ) == 0 ) {
        GIT(20);
        ReadTower( hnd, addr, offset, 20 );
    } else if( memcmp( buffer, "npc_dota_badguys_tower1_mid", 27 ) == 0 ) {
        GIT(21);
        ReadTower( hnd, addr, offset, 21 );
    }
}

void Worker::ReadHAdv( HANDLE *hnd, void *addr, const int offset )
{
    int i;
    int offsets[ 2 ];
    char buffer[ 64 ];
    char heroname[ 64 ];
    Player0_t *hero;
    int duplicate = 0;

    memset( heroname, 0, sizeof( heroname ) );
    memset( buffer, 0, sizeof( buffer ) );
    offsets[ 0 ] = offset;
    offsets[ 1 ] = NPC_DOTA_HERO;

    ReadString( hnd, addr, offsets, 2, buffer );

    for( i = 0; i < HEROES_ALL; i++ ) {
        if( memcmp( buffer, heroes[ i ].name, strlen( heroes[ i ].name ) ) == 0 ) {
            hero = GetHeroByID( heroes[ i ].id );
            if( hero != NULL ) {
                // ignore illusions
                // **this used to work, basically you don't want to display multiple instances of the same hero,
                // if you do, you still want to know the actual hero
                /*
                offsets[ 1 ] = 0x1800;	// FIXME: most likely wrong offset
                duplicate = ReadInt( hnd, addr, offsets, 2 );
                if( duplicate != 0 || hero->maxhp > 0 )
                    return;
                */
                offsets[ 1 ] = 0x10fc;
                hero->maxhp = ReadInt( hnd, addr, offsets, 2 );
                offsets[ 1 ] = 0xA8;
                hero->x = ReadFloat( hnd, addr, offsets, 2 );
                offsets[ 1 ] = 0xAC;
                hero->y = ReadFloat( hnd, addr, offsets, 2 );
                offsets[ 1 ] = 0xEC;
                hero->side = ReadInt( hnd, addr, offsets, 2 );
                offsets[ 1 ] = 0xF4;
                hero->currenthp = ReadInt( hnd, addr, offsets, 2 );
                hero->duplicate = duplicate;
                memcpy( hero->modelname, heroes[ i ].name, strlen( heroes[ i ].name ) );
#ifdef _DEBUG
                printf("ReadHAdv buffer:'%s' maxhp:%d x:%f y:%f side:%d currenthp:%d duplicate: %d offset: %x\n", buffer, hero->maxhp, hero->x, hero->y, hero->side, hero->currenthp, duplicate, offset );
#endif
            }
        }
    }
}

// for this to work you have to keep the in-game tab 'ITEMS' open
void Worker::ReadItems( HANDLE *hnd, void *addr, int offset )
{
    int i;
    int offsets[ 2 ];

    offsets[ 0 ] = offset;

    for( i = 0; i < HEROES_GAME_TOTAL; i++ ) {
        offsets[ 1 ] = i * 0x40 + 0x3c;
        p[ i ].i0 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].i1 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].i2 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].i3 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].i4 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].i5 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].s0 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].s1 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].s2 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].s3 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].s4 = ReadInt( hnd, addr, offsets, 2 );
        offsets[ 1 ] += 4;
        p[ i ].s5 = ReadInt( hnd, addr, offsets, 2 );
#ifdef _DEBUG
        printf( "player item:%d id:%d\n", i, p[ i ].i0 );
        printf( "player item:%d id:%d\n", i, p[ i ].i1 );
        printf( "player item:%d id:%d\n", i, p[ i ].i2 );
        printf( "player item:%d id:%d\n", i, p[ i ].i3 );
        printf( "player item:%d id:%d\n", i, p[ i ].i4 );
        printf( "player item:%d id:%d\n", i, p[ i ].i5 );
        printf( "player item stash:%d id:%d\n", i, p[ i ].s0 );
        printf( "player item stash:%d id:%d\n", i, p[ i ].s1 );
        printf( "player item stash:%d id:%d\n", i, p[ i ].s2 );
        printf( "player item stash:%d id:%d\n", i, p[ i ].s3 );
        printf( "player item stash:%d id:%d\n", i, p[ i ].s4 );
        printf( "player item stash:%d id:%d\n", i, p[ i ].s5 );
#endif
    }
}

void Worker::doWrite( void *var, const int type, char *buffer, FILE *f )
{
    int *x;
    float *y;
    char *z;

    if( type == T_INT ) {
        x = (int *)var;
        memset( buffer, 0, sizeof( *buffer ) );
        sprintf( buffer, "%d\n", *x );
        fwrite( buffer, 1, strlen( buffer ), f );
    } else if( type == T_FLOAT ) {
        y = (float *)var;
        memset( buffer, 0, sizeof( *buffer ) );
        sprintf( buffer, "%f\n", *y );
        fwrite( buffer, 1, strlen( buffer ), f );
    } else if( type == T_STRING ) {
        z = (char *)var;
        memset( buffer, 0, sizeof( *buffer ) );
        sprintf( buffer, "%s\n", z );
        fwrite( buffer, 1, strlen( buffer ), f );
    }
}

void Worker::ExportAll( char *gameId )
{
    FILE *pFile;
    char buffer[ 64 ];
    char *outputbuff;
    int lSize;
    int i;
    const char *tmp = "gamedata";
    char bufferf[ 128 ];

    memset( bufferf, 0, sizeof( bufferf ) );

    pFile = fopen( tmp, "w" );
    if( pFile == NULL ) {
        printf("file error\n");
    }
    fseek( pFile, 0, SEEK_END );

    // gameid
    doWrite( gameId, T_STRING, buffer, pFile );
    // general
    doWrite( &gi.score_rad, T_INT, buffer, pFile );
    doWrite( &gi.score_dire, T_INT, buffer, pFile );
    doWrite( &gi.gametime, T_INT, buffer, pFile );
    doWrite( &gi.fort, T_INT, buffer, pFile );
    doWrite( &gi.rax, T_INT, buffer, pFile );
    doWrite( &gi.towers, T_INT, buffer, pFile );
    doWrite( &gi.roshan_hp, T_INT, buffer, pFile );
    doWrite( &gi.rad_fort_hp, T_INT, buffer, pFile );
    doWrite( &gi.dire_fort_hp, T_INT, buffer, pFile );

    for( i = 0; i < HEROES_GAME_TOTAL; i++ ) {
        doWrite( &i, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_heroid, T_INT, buffer, pFile );
        doWrite( &p[ i ].maxhp, T_INT, buffer, pFile );
        doWrite( &p[ i ].x, T_FLOAT, buffer, pFile );
        doWrite( &p[ i ].y, T_FLOAT, buffer, pFile );
        doWrite( &p[ i ].side, T_INT, buffer, pFile );
        doWrite( &p[ i ].modelname, T_STRING, buffer, pFile );
        doWrite( &p[ i ].misc_dead_sec, T_INT, buffer, pFile );
        doWrite( &p[ i ].hero_ulticd_sec, T_INT, buffer, pFile );
        doWrite( &p[ i ].currenthp, T_INT, buffer, pFile );
        doWrite( &p[ i ].playername, T_STRING, buffer, pFile );
        doWrite( &p[ i ].misc_heroid, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_assists, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_deaths, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_level, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_ck, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_cd, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_totalgold, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_totalexp, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_dead_sec, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_kills, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_currentg0, T_INT, buffer, pFile );
        doWrite( &p[ i ].misc_currentg1, T_INT, buffer, pFile );

        doWrite( &p[ i ].i0, T_INT, buffer, pFile );
        doWrite( &p[ i ].i1, T_INT, buffer, pFile );
        doWrite( &p[ i ].i2, T_INT, buffer, pFile );
        doWrite( &p[ i ].i3, T_INT, buffer, pFile );
        doWrite( &p[ i ].i4, T_INT, buffer, pFile );
        doWrite( &p[ i ].i5, T_INT, buffer, pFile );
        doWrite( &p[ i ].s0, T_INT, buffer, pFile );
        doWrite( &p[ i ].s1, T_INT, buffer, pFile );
        doWrite( &p[ i ].s2, T_INT, buffer, pFile );
        doWrite( &p[ i ].s3, T_INT, buffer, pFile );
        doWrite( &p[ i ].s4, T_INT, buffer, pFile );
        doWrite( &p[ i ].s5, T_INT, buffer, pFile );
    }

    // towers
    for( i = 0; i < 22; i++ )
        doWrite( &towers[ i ].hp, T_INT, buffer, pFile );

    // rax
    for( i = 0; i < 12; i++ )
        doWrite( &rax[ i ].hp, T_INT, buffer, pFile );

    // wards
    for( i = 0; i < 16; i++ ) {
        doWrite( &wards[ i ].side, T_INT, buffer, pFile );
        doWrite( &wards[ i ].hp, T_INT, buffer, pFile );
        doWrite( &wards[ i ].x, T_INT, buffer, pFile );
        doWrite( &wards[ i ].y, T_INT, buffer, pFile );
        doWrite( &wards[ i ].type, T_INT, buffer, pFile );
    }

    // couriers
    for( i = 0; i < 8; i++ ) {
        doWrite( &couriers[ i ].side, T_INT, buffer, pFile );
        doWrite( &couriers[ i ].hp, T_INT, buffer, pFile );
        doWrite( &couriers[ i ].x, T_INT, buffer, pFile );
        doWrite( &couriers[ i ].y, T_INT, buffer, pFile );
    }

    fclose( pFile );

    pFile = fopen( tmp , "r" );
    fseek( pFile, 0, SEEK_END );
    lSize = ftell( pFile );
    lSize += sizeof(int); 	// add header length
    rewind( pFile );

    outputbuff = (char *)malloc( sizeof(char) * lSize + sizeof(int) );
    *(int *)outputbuff = lSize;
    fread( outputbuff + sizeof(int), 1, lSize, pFile );

    for( i = 0; i < lSize; i++ ) {
        if( outputbuff[ i ] == 13 )
            outputbuff[ i ] = 0;
    }

again:
    if( cl->sendData( outputbuff, lSize ) != 0 ) {
        if( cl->initClient( ip->text().toLocal8Bit().data(), port->text().toInt() ) != 0 ) {
            printf( "reconnect failed\n" );
            exit(0);
        }
        goto again;
    }

    fclose( pFile );
    free( outputbuff );
}
