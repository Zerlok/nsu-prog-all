#ifndef __COLOR_HPP__
#define __COLOR_HPP__


class Color
{
	public:
		static const Color white;
		static const Color grey;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;

		static Color makeRGB(const unsigned char& r,
							 const unsigned char& g,
							 const unsigned char& b);
		static Color makeRGBA(const unsigned char& r,
							  const unsigned char& g,
							  const unsigned char& b,
							  const unsigned char& a);
		static Color makeHSV(const unsigned char& h,
							 const unsigned char& s,
							 const unsigned char& v);
//		static Color makeHEX(const std::string& hex);

		Color(const unsigned char& red = 0,
			  const unsigned char& green = 0,
			  const unsigned char& blue = 0,
			  const unsigned char& alpha = 255);
		Color(const Color& c);
		Color(Color&& c);
		~Color();

		Color& operator=(const Color& c);
		Color& operator=(Color&& c);

		const unsigned char& getRed() const;
		const unsigned char& getGreen() const;
		const unsigned char& getBlue() const;
		const unsigned char& getAlpha() const;

		float getRedF() const;
		float getGreenF() const;
		float getBlueF() const;
		float getAlphaF() const;

	private:
		unsigned char _red;
		unsigned char _green;
		unsigned char _blue;
		unsigned char _alpha;
};


#endif // __COLOR_HPP__
