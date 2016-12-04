#include "animation.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


Animation::Animation(ComponentPtr& component)
	: Component(Component::Type::ANIMATION),
	  _component(component),
	  _transformation(Transformation::LINEAR),
	  _keyFrames({})
{
	logDebug << getName() << " for "
			 << component->getName()<< " created."
			 << logEndl;
}


Animation::~Animation()
{
	logDebug << getName() << " removed." << logEndl;
}


void Animation::setTransformation(const Animation::Transformation& tr)
{
	_transformation = tr;
}


void Animation::addKeyFrame(const KeyFrame& kf)
{
	_keyFrames.push_back(&kf);
}


void Animation::removeKeyFrames(const int& num)
{

}


void Animation::applyFrame(const int& num)
{

}
