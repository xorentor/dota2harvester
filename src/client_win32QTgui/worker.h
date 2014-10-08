#ifndef WORKER_H
#define WORKER_H

#include <QVector>
#include <QThread>
#include <Windows.h>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <TlHelp32.h>

#include "d2h.h"

// these change everytime dota.exe is recompiled
// eg. general update is done, weekly or so..
#define MEM_HEROBASIC		0x1309850		// 0. we did this by searching for gametime
#define MEM_HEROADV			0x1201BD4		// 1. we did this by searching for full hp
#define MEM_HEROMISC		0x11f1be4		// 2. we did this by searching for a hero lvl
#define MEM_ITEMS			0x123776C
#define MEM_HEROGOLD_R		0x11DDBF0	// refer to stuff/gold.png; search for mov ecx,[ecx+edx*4+00000760]
#define MEM_HEROGOLD_D		0x11DDBEC	// ^^


#define		HEROES_GAME_TOTAL 10

#define		T_INT			1
#define		T_FLOAT			2
#define		T_STRING		4

#define NPC_DOTA_HERO		0x11b8

//#undef _DEBUG
#define _DEBUG

namespace Ui {
class Worker;
}

typedef struct GeneralInfo_s
{
    int score_rad;
    int score_dire;
    int gametime;
    int fort;
    int rax;
    int towers;
    int roshan_hp;
    int	rad_fort_hp;
    int dire_fort_hp;
} GeneralInfo_t;

typedef struct Player0_s
{
    int hero_slot;
    int hero_level;
    int hero_kills;
    int hero_deaths;
    int hero_assists;
    int hero_gold;
    int hero_ck;
    int hero_cd;
    int hero_dead_sec;
    int hero_ulticd_sec;

    int hero_id;
    int maxhp;
    float x;
    float y;
    int side;
    char modelname[ 64 ];
    int currenthp;
    int duplicate;
    char playername[ 64 ];
    int misc_heroid;
    int misc_assists;
    int misc_deaths;
    int misc_dead_sec;
    int misc_level;
    int misc_ck;
    int misc_cd;
    int misc_totalgold;
    int misc_totalexp;
    int misc_currentg0;
    int misc_currentg1;
    int misc_kills;

// items
    int i0;
    int i1;
    int i2;
    int i3;
    int i4;
    int i5;
    int s0;
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
} Player0_t;

typedef struct Hero_s
{
    char name[ 64 ];
    int id;
} Hero_t;

typedef struct Ward_s
{
    int side;
    int hp;
    int x;
    int y;
    int type;
} Ward_t;

typedef struct Tower_s
{
    int side;
    int hp;
    float x;
    float y;
} Tower_t;

typedef struct Rax_s
{
    int side;
    int hp;
    float x;
    float y;
} Rax_t;

typedef struct Courier_s
{
    int side;
    int hp;
    int x;
    int y;
} Courier_t;

class Worker : public QThread {
public:
    Worker( struct guiobj_s ***fs, Client *cl, QLineEdit *ip, QLineEdit *port );
    ~Worker();

protected:
    void run();

private:
    struct guiobj_s ***edits;
    int startParser;
    HANDLE dhandle;
    int daddr;
    Client *cl;
    QLineEdit *ip, *port;

    bool GetProcessList();
    bool ListProcessModules( DWORD dwPID, HANDLE *hnd );
    bool ListProcessThreads( DWORD dwOwnerPID );
    void parseData( HANDLE hnd, int clientdll );

    void setGUI();

    void GetGameID( char *gameid );
    int ReadInt( HANDLE *hnd, void *addr, int *ost, const int ost_num );
    float ReadFloat( HANDLE *hnd, void *addr, int *ost, const int ost_num );
    void ReadString( HANDLE *hnd, void *addr, int *ost, const int ost_num, char *buffer );
    void ReadH( HANDLE *hnd, void *addr );
    Player0_t *GetHeroByID( const int id );
    void ReadGold( HANDLE *hnd, void *addr, void *addr1 );
    void ReadMisc( HANDLE *hnd, void *addr );

    void ReadCourier( HANDLE *hnd, void *addr, const int offset );
    void ReadWard( HANDLE *hnd, void *addr, const int offset, const int type );
    void ReadRax( HANDLE *hnd, void *addr, const int offset, const int index );
    void ReadTower( HANDLE *hnd, void *addr, const int offset, const int index );
    void ReadAncients( HANDLE *hnd, void *addr, const int offset, char *buffer );
    void ReadHAdv( HANDLE *hnd, void *addr, const int offset );
    void ReadItems( HANDLE *hnd, void *addr, int offset );
    void doWrite( void *var, const int type, char *buffer, FILE *f );
    void ExportAll( char *gameId );

};


#endif // WORKER_H
