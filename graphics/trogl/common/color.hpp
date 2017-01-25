#ifndef __COLOR_HPP__
#define __COLOR_HPP__


class Color
{
	public:
		static const Color transparent;
		static const Color white;
		static const Color grey;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;

		static Color makeRGB(const int& r,
							 const int& g,
							 const int& b);
		static Color makeRGBA(const int& r,
							  const int& g,
							  const int& b,
							  const int& a);
		static Color makeHSV(const int& h,
							 const int& s,
							 const int& v);
//		static Color makeHEX(const std::string& hex);

		Color(const int& red = 0,
			  const int& green = 0,
			  const int& blue = 0,
			  const int& alpha = 255);
		Color(const Color& c);
		Color(Color&& c);
		~Color();

		Color& operator=(const Color& c);
		Color& operator=(Color&& c);

		Color& operator+=(const Color& c);
		Color& operator*=(const float& ratio);
		Color operator+(const Color& c) const;
		Color operator*(const float& ratio) const;

		const int& getRed() const;
		const int& getGreen() const;
		const int& getBlue() const;
		const int& getAlpha() const;

		float getRedF() const;
		float getGreenF() const;
		float getBlueF() const;
		float getAlphaF() const;

	private:
		int _red;
		int _green;
		int _blue;
		int _alpha;
};


#endif // __COLOR_HPP__
