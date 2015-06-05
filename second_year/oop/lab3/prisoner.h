#ifndef __PRISONER_H__
#define __PRISONER_H__


struct Prisoner
{
	std::string _name;
	int _score;
	Strategy *_strategy;
};


// __PRISONER_H__
#endif