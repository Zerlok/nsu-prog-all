#ifndef __TRIOD_H__
#define __TRIOD_H__


template <class Container>
class Triod
{
	public:
		typedef typename Container::iterator Iterator;

		Triod(Container& v) : _begin(v.begin()), _end(v.end())
		{
			reset();
		}

		void reset()
		{
			_stop = false;

			i1 = _begin;
			i2 = i1 + 1;
			i3 = i2 + 1;
		}

		Container get_next()
		{
			Container v = {(*i1), (*i2), (*i3)};

			if (i3 + 1 != _end)
			{
				i3++;
			}
			else if (i2 + 1 != i3)
			{
				i2++;
				i3 = i2 + 1;
			}
			else if (i1 + 1 != i2)
			{
				i1++;
				i2 = i1 + 1;
				i3 = i2 + 1;
			}
			else if (!_stop)
			{
				_stop = true;
			}
			else
			{
				return {};
			}

			return v;
		}

		bool is_gone() const
		{
			return _stop;
		}

		void show_trios()
		{
			Container v = get_next();

			while (v.size() != 0)
			{
				std::cout
					<< "{" << v[0] << " " << v[1] << " " << v[2] << "}" << std::endl;
				v = get_next();
			}
		}

	private:
		bool _stop;

		Iterator _begin;
		Iterator _end;
		Iterator i1;
		Iterator i2;
		Iterator i3;
};


// __TRIOD_H__
#endif