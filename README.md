dota2harvester
==============

Dota2 memory reader

This is unforunately only a win32 version as linux version of dota2 has been released just recently.

This software was used by www.dota2mobile.com during Valve Dota2 The International 2013

It must be ran simmultaneously with valve dota2 game while client is in the observer mode.
When it's executed, it creates a gamedata dump file that can be parsed and used for various purposes.

Offsets must be updated, as they change after every client update ( approximately each Friday ).

To compile it, get mingw: http://sourceforge.net/projects/mingw/files/ and just make it.

there are 2 .dll manadatory files:
libgcc_s_dw2-1.dll
libstdc++-6.dll

You can grab these from your mingw bin directory if you don't trust mine.

List of information you can retrive:
- gametime
- score radiant
- score dire
- gametime
- radiant fortress hp
- dire fortress hp
- towers' hp
- rax' hp
- roshan hp
- wards side/hp/location
- courier side/hp/location

All 10 players' info:
- maxhp
- X/Y axis on the map
- side
- modelname
- hero dead seconds
- hero ulti cd seconds
- current hp
- playername
- heroid
- assists
- deaths
- level
- creeps killed
- creeps denied
- totalgold
- totalexp
- kills
- all inventory/stash items

Hopefully, this will help to create some amazing projects.