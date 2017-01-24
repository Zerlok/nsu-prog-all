#include "animation.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLWarning, loggerDFull);


Animatable::Animatable(const Component::Type& type,
					   const std::string& name)
	: Component(type, name),
	  _keyframes(),
	  _properties(),
	  _inners()
{
}


Animatable::Animatable(const Animatable& anim)
	: Component(anim),
	  _keyframes(anim._keyframes),
	  _properties(),
	  _inners()
{
}


Animatable::Animatable(Animatable&& anim)
	: Component(std::move(anim)),
	  _keyframes(std::move(anim._keyframes)),
	  _properties(),
	  _inners()
{
}


Animatable::~Animatable()
{
	_clearProperties();
}


void Animatable::addKeyframe(const size_t& frameNum)
{
	Keyframes::iterator it;
	for (it = _keyframes.begin();
		 it != _keyframes.end();
		 ++it)
	{
		if ((*it) == frameNum)
			break;
		else if ((*it) > frameNum)
		{
			_keyframes.insert(it, frameNum);
			break;
		}
	}

	if (it == _keyframes.end())
		_keyframes.push_back(frameNum);

	for (AbstractProperty* p : _properties)
		p->fixValue(frameNum);

	for (Animatable* in : _inners)
		in->addKeyframe(frameNum);
}


void Animatable::setKeyframe(const size_t& frameNum, const AnimationTransformation* tr)
{
	if (_keyframes.empty())
		return;

	const size_t prev = _getPrevious(frameNum);
	const size_t next = _getNext(frameNum);
	const float& alpha = tr->calculate(frameNum, prev, next);

	for (AbstractProperty* p : _properties)
		p->calculateValue(alpha, prev, next);

	for (Animatable* in : _inners)
		in->setKeyframe(frameNum, tr);
}


size_t Animatable::_getPrevious(const size_t& frameNum) const
{
	size_t tmp;
	for (const size_t& kf : _keyframes)
	{
		if (kf >= frameNum)
			break;

		tmp = kf;
	}

	return tmp;
}


size_t Animatable::_getNext(const size_t& frameNum) const
{
	size_t tmp;
	for (const size_t& kf : _keyframes)
	{
		tmp = kf;
		if (kf >= frameNum)
			break;
	}

	return tmp;
}


void Animatable::_clearProperties()
{
	for (AbstractProperty* p : _properties)
		delete p;

	_properties.clear();
}


Animation::Animation(const std::string& name)
	: Component("ANIMATION", name),
	  _components(),
	  _transformation(new LinearTransformation()),
	  _cntr(0),
	  _length(0)
{
	logDebug << "Animation created."
			 << logEndl;
}


Animation::~Animation()
{
	delete _transformation;
	logDebug << getName() << " animation removed." << logEndl;
}


size_t Animation::getFrame() const
{
	return _cntr;
}


void Animation::add(Animatable* anim)
{
	for (const AnimatablePtr& c : _components)
		if (c == anim)
			return;

	_components.push_back(anim);
}


void Animation::applyFrame(const size_t& num)
{
	const size_t n = ((_length != 0) ? (num % _length) : num);

	for (AnimatablePtr& c : _components)
		c->setKeyframe(n, _transformation);
}


void Animation::setLength(const size_t& len)
{
	_length = len;
}


void Animation::nextFrame()
{
	applyFrame(++_cntr);
}


void Animation::setTransformation(const Animation::Transformation& tr)
{
	delete _transformation;

	switch (tr)
	{
		case Transformation::LINEAR:
			_transformation = new LinearTransformation();
			break;
		case Transformation::SMOOTH:
			_transformation = new SmoothTransformation();
			break;
	}
}


float clamp(const float& x, const float& a, const float& b)
{
	return std::min(std::max(x, a), b);
}


float LinearTransformation::calculate(const size_t& current,
									  const size_t& previous,
									  const size_t& next) const
{
	return clamp((float(current - previous) / float(next - previous)), 0.0, 1.0);
}


float SmoothTransformation::calculate(const size_t& current,
									  const size_t& previous,
									  const size_t& next) const
{
	const float& alpha = clamp((float(current - previous) / float(next - previous)), 0.0, 1.0);
	return std::pow(std::sin(alpha * M_PI_2), 2.0f);
}
