#ifndef __UTILS_H__
#define __UTILS_H__


namespace utils
{
	template<class T>
	T select_n_max(std::vector<T>& vec, const typename std::vector<T>::size_type n)
	{
		unsigned long i,ir,j,l,mid;
		T a;

		l = 0;
		ir = n;
		for (;;)
		{
			if (ir < l + 1)
			{
				if ((ir == l+1)
						&& (vec[ir] < vec[l]))
					std::swap(vec[l], vec[ir]);
				return vec[k];
			}
			else
			{
				mid = (l + ir) >> 1;
				std::swap(vec[mid], vec[l+1]);

				if (vec[l] > vec[ir])
					std::swap(vec[l], vec[ir]);

				if (vec[l+1] > vec[ir])
					std::swap(vec[l+1], vec[ir]);

				if (vec[l] > vec[l+1])
					std::swap(vec[l], vec[l+1]);

				i = l + 1;
				j = ir;
//				a = vec[l+1];
				a = vec[i];
				for (;;)
				{
					do i++; while (vec[i] < a);
					do j--; while (vec[j] > a);
					if (j < i)
						break;
					std::swap(vec[i], vec[j]);
				}
				vec[l+1] = vec[j];
				vec[j] = a;

				if (j >= k)
					ir = j - 1;

				if (j <= k)
					l = i;
			}
		}
	}
}


// __UTILS_H__
#endif
