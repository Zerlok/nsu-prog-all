#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__


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
		Transformator(Transformation<T>* tr = nullptr)
			: _tr(tr) {}
		virtual ~Transformator() { delete _tr; }

		virtual void apply_forward(T& vec) = 0;
		virtual void apply_backward(T& vec) = 0;

		void set_transformation(Transformation<T>* tr)
		{
			delete _tr;
			_tr = tr;
		}

	protected:
		const Transformation<T>* _tr;
};


// __TRANSFORMATION_H__
#endif
