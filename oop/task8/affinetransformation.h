#ifndef __AFFINETRANSFORMATION_H__
#define __AFFINETRANSFORMATION_H__


#include <math.h>


// C = A*x + B
class AffineTransformation
{
	public:
		AffineTransformation(
				const double a00 = 1.0,
				const double a01 = 0.0,
				const double a10 = 0.0,
				const double a11 = 1.0,
				const double b0 = 0.0,
				const double b1 = 0.0
		);
		AffineTransformation(const AffineTransformation &tr);
		virtual ~AffineTransformation();

		// Methods.
		void transform(double &x, double &y) const;
		void transform(double &x, const double &y) const;
		void transform(const double &x, double &y) const;

		void transform(int &x, int &y) const;
		void transform(int &x, const int &y) const;
		void transform(const int &x, int &y) const;

		// Operators.
		AffineTransformation &operator=(const AffineTransformation &tr);
		AffineTransformation operator+(const AffineTransformation &tr);
		AffineTransformation &operator+=(const AffineTransformation &tr);

	protected:
		double _a00;
		double _a01;
		double _a10;
		double _a11;
		double _b0;
		double _b1;
};


class TranslationTransformation : public AffineTransformation
{
	public:
		TranslationTransformation(const int dx, const int dy);
		TranslationTransformation(const double dx, const double dy);
		TranslationTransformation(const AffineTransformation &tr);
		~TranslationTransformation() {}
};


class RotationTransformation : public AffineTransformation
{
	public:
		static double get_radians(const int degrees);

		RotationTransformation(const int degrees);
		RotationTransformation(const double radians);
		RotationTransformation(const AffineTransformation &tr);
		~RotationTransformation() {}

	private:
		static const double round_ratio;
		static const double radian;
};


class ScalingTransformation : public AffineTransformation
{
	public:
		ScalingTransformation(const int sx, const int sy);
		ScalingTransformation(const double sx, const double sy);
		ScalingTransformation(const AffineTransformation &tr);
		~ScalingTransformation() {}
};


// __AFFINETRANSFORMATION_H__
#endif
