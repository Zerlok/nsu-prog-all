#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__


#include <cmath>
#include <list>
#include <unordered_map>
#include <sharedpointer.h>
#include "common/utils.hpp"
#include "opengls.hpp"
#include "nameable.hpp"


class AnimationTransformation
{
	public:
		AnimationTransformation() {}
		virtual ~AnimationTransformation() {}
};


class LinearTransformation
{
	public:
		LinearTransformation() {}
		~LinearTransformation() {}

		template<class T>
		T calculate(const float& alpha,
					const T& previousValue,
					const T& nextValue);
};


class SmoothTransformation
{
	public:
		SmoothTransformation() {}
		~SmoothTransformation() {}

		template<class T>
		T calculate(const float& alpha,
					const T& previousValue,
					const T& nextValue)
		{
			const float ratio = std::pow(std::cos(alpha * M_PI_2), 2.0f);
			return (ratio*previousValue + (1.0 - ratio)*nextValue);
		}
};


class AbstractProperty
{
	public:
		AbstractProperty() {}
		AbstractProperty(const AbstractProperty&) {}
		virtual ~AbstractProperty() {}

		virtual AbstractProperty* clone() = 0;
		virtual bool equals(const AbstractProperty& prop) const = 0;
		virtual void fixValue(const size_t& frameNum) = 0;
		virtual void calculateValue(const size_t& curr,
									const size_t& prev,
									const size_t& next) = 0;
};


template<class T>
class Property : public AbstractProperty
{
	public:
		using Keyframes = std::list<size_t>;
		using States = std::unordered_map<size_t ,T>;

		Property(T& value)
			: AbstractProperty(),
			  _ref(value),
			  _states() {}
		~Property() {}

		AbstractProperty* clone() override
		{
			Property<T>* tmp = new Property<T>(_ref);
			tmp->_states = _states;
			return tmp;
		}

		bool equals(const AbstractProperty &prop) const override
		{
			return (&_ref == &reference(prop));
		}

		void fixValue(const size_t& frameNum) override
		{
			_states[frameNum] = _ref;
		}

		void calculateValue(const size_t& curr,
							const size_t& prev,
							const size_t& next)
		{
			const float& alpha = std::min(std::max((float(curr - prev) / float(next - prev)), 0.0f), 1.0f);
			T prevState = _states[prev];
			T nextState = _states[next];

			prevState *= (1.0 - alpha);
			nextState *= alpha;

			_ref = prevState + nextState;
//			_ref = (_states[prev]*alpha + _states[next]*(1.0 - alpha));
		}

	private:
		T& _ref;
		States _states;

		T& reference(const AbstractProperty& prop)
		{
			return ((Property<T>&)prop)._ref;
		}
		const T& reference(const AbstractProperty& prop) const
		{
			return ((const Property<T>&)prop)._ref;
		}
};


class Animatable : public Nameable
{
	public:
		using Properties = std::list<AbstractProperty*>;
		using Inners = std::list<Animatable*>;
		using Keyframes = std::list<size_t>;

		Animatable(const std::string& name);
		Animatable(const Animatable& anim);
		Animatable(Animatable&& anim);
		virtual ~Animatable();

		Animatable& operator=(const Animatable& anim);
		Animatable& operator=(Animatable&& anim);

		void addKeyframe(const size_t& frameNum);
		void setKeyframe(const size_t& frameNum);

	protected:
		void _regInnerProperty(Animatable* anim)
		{
			if (this == anim)
				return;

			for (Animatable* in : _inners)
				if (in == anim)
					return;

			_inners.push_back(anim);
		}

		template<class T>
		void _regProperty(T& value)
		{
			Property<T>* prop = new Property<T>(value);

			for (AbstractProperty* p : _properties)
			{
				if (prop->equals(*p))
				{
					delete prop;
					return;
				}
			}

			_properties.push_back(prop);
		}

		virtual void _regProperties() = 0;

	private:
		Keyframes _keyframes;
		Properties _properties;
		Inners _inners;

		size_t _getPrevious(const size_t& frameNum) const;
		size_t _getNext(const size_t& frameNum) const;
		void _clearProperties();
};

using AnimatablePtr = SharedPointer<Animatable, Nameable>;


class Animation : public Nameable
{
	public:
		enum class Transformation
		{
			LINEAR,
			SMOOTH,
		};

		using Components = std::list<AnimatablePtr>;

		Animation(const std::string& name);
		~Animation();

		size_t getFrame() const;

		void add(Animatable* anim);

		template<class T>
		void add(SharedPointer<T>& ptr)
		{
			add(ptr.get_pointer());
		}

		void applyFrame(const size_t& num);

		void setTransformation(const Transformation& tr);
		void setLength(const size_t& len);

		void nextFrame();

	private:
		Components _components;
		Transformation _transformation;
		size_t _cntr;
		size_t _length;
};

using AnimationPtr = SharedPointer<Animation, Nameable>;
using Animations = std::list<AnimationPtr>;


#endif // __ANIMATION_HPP__
