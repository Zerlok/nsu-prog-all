#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__


#include <list>
#include "component.hpp"


template<class CompType, class AttrType>
class Attributer
{
	public:
		Attributer();
		virtual ~Attributer();

		virtual const AttrType& get(CompType const* comp) const = 0;
		virtual void set(CompType* comp, const AttrType& attr) const = 0;
};


class KeyFrame
{
	public:
		KeyFrame(const int& num = 0);
		virtual ~KeyFrame();

		const int& getNum() const;
		void setNum(const int& num);

		// fix(componentObj, fieldId)
		virtual void fix(Component& comp) = 0;
};


class Animation : public Component
{
	public:
		enum class Transformation
		{
			LINEAR,
			SINUSOIDAL,
		};

		using KeyFrames = std::list<const KeyFrame*>;

		Animation(ComponentPtr& component);
		~Animation();

		void setTransformation(const Transformation& tr);

		void addKeyFrame(const KeyFrame& kf);
		void removeKeyFrames(const int& num);

		void applyFrame(const int& num);

	protected:
		ComponentPtr _component;
		Transformation _transformation;
		KeyFrames _keyFrames;
};


#endif // __ANIMATION_HPP__
