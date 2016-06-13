#ifndef __WAVELET_TRANSFORMATION_H__
#define __WAVELET_TRANSFORMATION_H__


#include <vector>
#include "transformation.h"


//using Floats = std::vector<float>;
typedef std::vector<float> Floats;
typedef Floats::size_type size_t;


class OneDimTransformator : public Transformator<Floats>
{
	public:
		OneDimTransformator(const Transformation<Floats>& tr)
			: Transformator<Floats>(tr) {}

		void apply_forward(Floats& vec) override;
		void apply_backward(Floats& vec) override;
};


class DAUB4Transform : public Transformation<Floats>
{
	public:
		DAUB4Transform();

		virtual void forward(Floats& vec) const override;
		virtual void backward(Floats& vec) const override;

	private:
		static const double c0;
		static const double c1;
		static const double c2;
		static const double c3;
};


class PartlyTransform : public Transformation<Floats>
{
	public:
		class Filt;

		PartlyTransform(const Filt& wfilt);

		virtual void forward(Floats& vec) const override;
		virtual void backward(Floats& vec) const override;

	private:
		const Filt& _wfilt;
};


class PartlyTransform::Filt
{
	public:
		enum class Mode
		{
			first = 4,
			second = 12,
			third = 20
		};

		Filt(const Mode& mode);

		int ncof;
		int ioff;
		int joff;

		Floats cc;
		Floats cr;

	private:
		static const Floats c4;
		static const Floats c4r;
		static const Floats c12;
		static const Floats c12r;
		static const Floats c20;
		static const Floats c20r;
};


// __WAVELET_TRANSFORMATION_H__
#endif
