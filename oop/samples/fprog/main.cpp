#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>


/*
 * WAT: pointer to class field.
 *
 * class A { public: int x, y, z; };
 * int A::* p;
 * p = &A::x;
 *
 * A a;
 * a.x == a.*p;
 */


template<typename Tp>
class ClassChecker
{
	private:
		typedef char One;
		typedef struct _S { char c[2]; } Two;

		template<typename Cls>
		static One test(int Cls::*); // pointer to class filed.

		template<typename Cls>
		static Two test(...);

	public:
		enum { True = (sizeof(ClassChecker<Tp>::test<Tp>(0)) == sizeof(One)) };
		enum { False = !True };
};


template<typename Tp>
bool isinstance()
{
	return ClassChecker<Tp>::True;
}


class A
{
	public:
		int x;
		char c;
		std::vector<int> vect;

		A() {}
		~A() {}

		void foo() {}
		int bar() { return x; }

	private:
		const int priv = 19;
};


int main()
{
	/*
	 * functional like programing example.
	 */
//	std::vector<int> values = {1, -22, -3, 4, 5, -346, -7, 83, 0, 93, 10};
//	std::cout << std::count_if(values.begin(), values.end(), std::bind(std::greater<int>(), std::placeholders::_1, 0)) << std::endl;

	/*
	 * Lambda example.
	 */
//	auto bool_f_int_generator = [](int x) -> std::function<bool (int)> {
//		return [x](int n) -> bool {
//			return x + n;
//		};
//	};

//	auto plus100 = bool_f_int_generator(100);

	std::cout << isinstance<int>() << std::endl;
	std::cout << isinstance<A>() << std::endl;
	std::cout << isinstance<std::vector<int> >() << std::endl;

	A a;
	auto A::* p = &A::foo;

	std::cout << &a << " " << p << std::endl;

	return 0;
}
