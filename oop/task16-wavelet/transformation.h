#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__


#include <vector>
using Floats = std::vector<float>;
using size_t = Floats::size_type;


template<class T>
class Transformation
{
	public:
		virtual ~Transformation() {}
		virtual void forward(T& vec) const = 0;
		virtual void backward(T& vec) const = 0;
};


template<class T>
class Transformator
{
	public:
		Transformator(const Transformation<T>& tr)
			: _tr(tr) {}
		virtual ~Transformator() {}

		virtual void apply_forward(Floats& vec) = 0;
		virtual void apply_backward(Floats& vec) = 0;

	protected:
		const Transformation<T>& _tr;
};


// __TRANSFORMATION_H__
#endif
