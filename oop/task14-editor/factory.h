#ifndef __FACTORY_H__
#define __FACTORY_H__


#include <string>
#include <vector>
using Arguments = std::vector<std::string>;


#include <sstream>
#include <stdexcept>
#include <unordered_map>


static const std::string ERR_KEY_NOT_FOUND = "The key is not registered: ";


template<class BaseCls>
class AbstractClassCreator
{
	public:
		AbstractClassCreator() {}
		virtual ~AbstractClassCreator() {}
		virtual BaseCls* create() = 0;
		virtual BaseCls* create(const Arguments& args) = 0;
};


template<class BaseCls, class DerivedCls>
class DerivedClassCreator : public AbstractClassCreator<BaseCls>
{
	public:
		DerivedClassCreator() {}
		virtual ~DerivedClassCreator() {}

		BaseCls* create()
		{
			return new DerivedCls();
		}

		BaseCls* create(const Arguments& args)
		{
			return new DerivedCls(args);
		}
};


template<class K, class B>
class Factory
{
	public:
		using Key = K;
		using BaseCls = B;
		using BaseCreator = AbstractClassCreator<BaseCls>;
		using CreatorsMap = std::unordered_map<Key, BaseCreator*>;

		Factory() {}
		Factory(const Factory<Key, BaseCls>& factory) = delete;
		~Factory()
		{
			for (std::pair<Key, BaseCreator*> p : _creators)
				delete p.second;
		}

		template<class DerivedCls>
		bool registerate(const Key& key)
		{
			if (_creators.find(key) != _creators.end())
				return false;

			_creators.insert({key, new DerivedClassCreator<BaseCls, DerivedCls>()});
			return true;
		}

		BaseCls* create(const Key& key)
		{
			typename CreatorsMap::iterator it = _creators.find(key);

			if (it == _creators.end())
			{
				std::stringstream ss;
				ss << ERR_KEY_NOT_FOUND << key;
				throw std::invalid_argument(ss.str());
			}

			return ((it->second)->create());
		}

		BaseCls* create(const Key &key, const Arguments& args)
		{
			typename CreatorsMap::iterator it = _creators.find(key);

			if (it == _creators.end())
			{
				std::stringstream ss;
				ss << ERR_KEY_NOT_FOUND << key;
				throw std::invalid_argument(ss.str());
			}

			if (args.empty())
				return ((it->second)->create());

			else
				return ((it->second)->create(args));
		}

	private:
		CreatorsMap _creators;
};


// __FACTORY_H__
#endif

