#include "animation.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


Animatable::Animatable(const std::string& name)
	: Nameable(name),
	  _keyframes(),
	  _properties(),
	  _inners()
{
}


Animatable::Animatable(const Animatable& anim)
	: Nameable(anim),
	  _keyframes(anim._keyframes),
	  _properties(),
	  _inners()
{
}


Animatable::Animatable(Animatable&& anim)
	: Nameable(std::move(anim)),
	  _keyframes(std::move(anim._keyframes)),
	  _properties(),
	  _inners()
{
}


Animatable::~Animatable()
{
	_clearProperties();
}


Animatable& Animatable::operator=(const Animatable& anim)
{
	Nameable::operator=(anim);
	_keyframes = anim._keyframes;
//	_clearProperties();
//	_inners.clear();

	return (*this);
}


Animatable& Animatable::operator=(Animatable&& anim)
{
	Nameable::operator=(std::move(anim));
	_keyframes = std::move(anim._keyframes);
//	_clearProperties();
//	_inners.clear();

	return (*this);
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


void Animatable::setKeyframe(const size_t& frameNum)
{
	if (_keyframes.empty())
		return;

	const size_t prev = _getPrevious(frameNum);
	const size_t next = _getNext(frameNum);

	for (AbstractProperty* p : _properties)
		p->calculateValue(frameNum, prev, next);

	for (Animatable* in : _inners)
		in->setKeyframe(frameNum);
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
	: Nameable(name),
	  _components(),
	  _transformation(Transformation::LINEAR),
	  _cntr(0),
	  _length(0)
{
	logDebug << "Animation created."
			 << logEndl;
}


Animation::~Animation()
{
	logDebug << "animation removed." << logEndl;
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
		c->setKeyframe(n);
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
	_transformation = tr;
}

