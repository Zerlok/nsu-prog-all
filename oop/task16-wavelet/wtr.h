#ifndef __WAVELET_TRANSFORMATION_H__
#define __WAVELET_TRANSFORMATION_H__


#include <vector>
#include "transformation.h"


using Floats = std::vector<float>;
using size_t = Floats::size_type;


class OneDimTransformator : public Transformator<Floats>
{
	public:
		OneDimTransformator(Transformation<Floats> *tr = nullptr)
			: Transformator<Floats>(tr) {}

		void apply_forward(Floats& vec) override;
		void apply_backward(Floats& vec) override;
};


class DAUB4Transform : public Transformation<Floats>
{
	public:
		DAUB4Transform() {}

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
		class Filt
		{
			public:
				enum class Mode
				{
					first = 4,
					second = 12,
					third = 20
				};

				Filt(const Mode& mode);
				Filt(const Filt& filt);

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

		PartlyTransform(const Filt::Mode& mode)
			: _wfilt(mode) {}
		PartlyTransform(const Filt& wfilt)
			: _wfilt(wfilt) {}

		virtual void forward(Floats& vec) const override;
		virtual void backward(Floats& vec) const override;

	private:
		const Filt _wfilt;
};


// __WAVELET_TRANSFORMATION_H__
#endif
