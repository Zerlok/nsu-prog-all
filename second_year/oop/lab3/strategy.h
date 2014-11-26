class Strategy
{
	public:
		Strategy() {}
		~Strategy() {}

		virtual Decision get_decision() = 0;
};


class TrustfullStrategy : public Strategy
{
	public:
		TrustfullStrategy() {}
		~TrustfullStrategy() {}

		virtual Decision get_decision()
		{
			std::cout << "coop" << std::endl;
			return cooperate;
		}
};


class MistrustfullStrategy : public Strategy
{
	public:
		MistrustfullStrategy() {}
		~MistrustfullStrategy() {}

		virtual Decision get_decision()
		{
			std::cout << "betr" << std::endl;
			return betray;
		}
};


class CrazyStrategy : public Strategy
{
	public:
		CrazyStrategy() {}
		~CrazyStrategy() {}

		virtual Decision get_decision()
		{
			if (rand() % 2) return cooperate;
			return betray;
		}
};