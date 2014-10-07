/*
Dota2Harvester - Dota2 memory reader
Copyright (C) 08/2013 www.github.com/xorentor

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef _D2H_H_
#define _D2H_H_

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

void D2H( HANDLE *hnd, void *clientdll );

#endif
