#ifndef __LIFEGAME_FIGURES_H__
#define __LIFEGAME_FIGURES_H__


void create_glider(const int x, const int y, Universe& space)
{
	space.init(x+1, y+1);
	space.init(x+2, y+2);
	space.init(x+2, y+3);
	space.init(x+3, y+2);
	space.init(x+3, y+1);
}


void create_blinker(const int x, const int y, Universe& space)
{
	space.init(x+1, y+2);
	space.init(x+2, y+2);
	space.init(x+3, y+2);
}


void create_toad(const int x, const int y, Universe& space)
{
	space.init(x+2, y+2);
	space.init(x+2, y+3);
	space.init(x+2, y+4);
	space.init(x+3, y+1);
	space.init(x+3, y+2);
	space.init(x+3, y+3);
}


void create_block(const int x, const int y, Universe& space)
{
	space.init(x+1, y+1);
	space.init(x+1, y+2);
	space.init(x+2, y+1);
	space.init(x+2, y+2);
}


// __LIFEGAME_FIGURES_H__
#endif
