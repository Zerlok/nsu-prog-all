#ifndef __STRATEGY_H__
#define __STRATEGY_H__


class Strategy
{
	public:
		Strategy() {}
		virtual ~Strategy() {}

		virtual Decision get_decision() = 0;
		virtual void learn_choices(int id, Decision decision[3]) {}
		virtual void setup(GameMatrix *matrix, std::string& config_path) {}
};


class TrustfulStrategy : public Strategy
{
	public:
		TrustfulStrategy() {}
		~TrustfulStrategy() {}

		virtual Decision get_decision() { return cooperate; }
};


class MistrustfulStrategy : public Strategy
{
	public:
		MistrustfulStrategy() {}
		~MistrustfulStrategy() {}

		virtual Decision get_decision() { return defect; }
};


class CrazyStrategy : public Strategy
{
	public:
		CrazyStrategy() {}
		~CrazyStrategy() {}

		virtual Decision get_decision()
		{
			srand(time(NULL));

			return (rand() % 2) ? cooperate : defect;
		}
};


// __STRATEGY_H__
#endif