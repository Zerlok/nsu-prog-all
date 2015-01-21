#ifndef __STRATEGY_H__
#define __STRATEGY_H__


class Strategy
{
	public:
		Strategy() {}
		virtual ~Strategy() {}

		virtual Decision get_decision() = 0;
		virtual void learn_choices(
				std::vector<Decision>& opponents_decisions) = 0;
};


class TrustfulStrategy : public Strategy
{
	public:
		TrustfulStrategy(
				const ScoreMatrix& matrix,
				const std::string& configs_dir) {}

		~TrustfulStrategy() {}

		virtual Decision get_decision() { return cooperate; }
		virtual void learn_choices(
				std::vector<Decision>& opponents_decisions) {}
};


class MistrustfulStrategy : public Strategy
{
	public:
		MistrustfulStrategy(
				const ScoreMatrix& matrix,
				const std::string& configs_dir) {}

		~MistrustfulStrategy() {}

		virtual Decision get_decision() { return defect; }
		virtual void learn_choices(
				std::vector<Decision>& opponents_decisions) {}
};


class CrazyStrategy : public Strategy
{
	public:
		CrazyStrategy(
				const ScoreMatrix& matrix,
				const std::string& configs_dir) {}

		~CrazyStrategy() {}

		virtual Decision get_decision()
		{
			return (rand() % 2) ? defect : cooperate;
		}

		virtual void learn_choices(
				std::vector<Decision>& opponents_decisions) {}
};


// __STRATEGY_H__
#endif