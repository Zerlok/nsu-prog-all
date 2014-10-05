void init_glider(const int x, const int y, Universe& space)
{
	space.init(x+1, y+1, ALIVE);
	space.init(x+2, y+2, ALIVE);
	space.init(x+2, y+3, ALIVE);
	space.init(x+3, y+2, ALIVE);
	space.init(x+3, y+1, ALIVE);
}


void init_blinker(const int x, const int y, Universe& space)
{
	space.init(x+1, y+2, ALIVE);
	space.init(x+2, y+2, ALIVE);
	space.init(x+3, y+2, ALIVE);
}


void init_toad(const int x, const int y, Universe& space)
{
	space.init(x+2, y+2, ALIVE);
	space.init(x+2, y+3, ALIVE);
	space.init(x+2, y+4, ALIVE);
	space.init(x+3, y+1, ALIVE);
	space.init(x+3, y+2, ALIVE);
	space.init(x+3, y+3, ALIVE);
}