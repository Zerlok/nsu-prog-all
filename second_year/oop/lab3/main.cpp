#include "main.h"

#include "strategy.h"
#include "factory.h"
#include "mode.h"
#include "game.h"


int main(const int argc, const char **argv)
{
	StrategyFactory factory;

	factory.register_id<TrustfulStrategy>("trustful");
	factory.register_id<MistrustfulStrategy>("mistrustful");
	factory.register_id<CrazyStrategy>("randomized");

	Game dilemma(argc, argv, factory);

	dilemma.run();

	return 0;
}
