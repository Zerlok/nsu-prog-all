#ifndef __LIFEGAME_FIGURES_H__
#define __LIFEGAME_FIGURES_H__


void create_glider(const int x, const int y, Universe& space)
{
	space.init(x+1, y+1, ALIVE);
	space.init(x+2, y+2, ALIVE);
	space.init(x+2, y+3, ALIVE);
	space.init(x+3, y+2, ALIVE);
	space.init(x+3, y+1, ALIVE);
}


void create_blinker(const int x, const int y, Universe& space)
{
	space.init(x+1, y+2, ALIVE);
	space.init(x+2, y+2, ALIVE);
	space.init(x+3, y+2, ALIVE);
}


void create_toad(const int x, const int y, Universe& space)
{
	space.init(x+2, y+2, ALIVE);
	space.init(x+2, y+3, ALIVE);
	space.init(x+2, y+4, ALIVE);
	space.init(x+3, y+1, ALIVE);
	space.init(x+3, y+2, ALIVE);
	space.init(x+3, y+3, ALIVE);
}


void create_block(const int x, const int y, Universe& space)
{
	space.init(x+1, y+1, ALIVE);
	space.init(x+1, y+2, ALIVE);
	space.init(x+2, y+1, ALIVE);
	space.init(x+2, y+2, ALIVE);
}


// __LIFEGAME_FIGURES_H__
#endif