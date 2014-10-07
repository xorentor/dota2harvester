dota2harvester
==============

Dota2 memory reader for win32.

This software was used by www.dota2mobile.com during Valve Dota2 The International 2013.

It must be ran simultaneously with valve dota2 game while client is in the observer mode.
When it's executed, it creates a gamedata dump file that can be parsed and used for various purposes.

Offsets must be updated, as they change after every client update ( approximately each Friday ).

There is a guide explaining how to find offsets on https://vimeo.com/100057000 .

./src/client_win32cli - use mingw to build it
./src/client_win32QTgui - use qmake to build it

List of information you can retrieve:
- gametime
- score radiant
- score dire
- radiant fortress hp
- dire fortress hp
- towers
- raxes
- roshan
- wards
- couriers

All 10 players' info:
- maxhp
- X/Y axis on the map
- side
- modelname
- hero dead seconds
- hero ulti cd seconds
- current hp
- playername
- hero id
- assists
- deaths
- level
- creeps killed
- creeps denied
- total gold
- total exp
- kills
- all inventory/stash items

Hopefully, this will help to create some amazing projects.