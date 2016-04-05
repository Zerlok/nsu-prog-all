#ifndef __FACTORY_H__
#define __FACTORY_H__


#include <string>
#include <vector>
#include <unordered_map>
using Strings = std::vector<std::string>;


template<class BaseCls>
class AbstractClassCreator
{
	public:
		AbstractClassCreator() {}
		virtual ~AbstractClassCreator() {}
		virtual BaseCls* create(const Strings& args) = 0;
};


template<class BaseCls, class DerivedCls>
class DerivedClassCreator : public AbstractClassCreator<BaseCls>
{
	public:
		DerivedClassCreator() {}
		virtual ~DerivedClassCreator() {}

		BaseCls* create(const Strings& args)
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
				return nullptr;

			return ((it->second)->create());
		}

		BaseCls* create(const Key &key, const Strings& args)
		{
			typename CreatorsMap::iterator it = _creators.find(key);

			if (it == _creators.end())
				return nullptr;

			return ((it->second)->create(args));
		}

		const std::vector<Key> get_registred() const
		{
			std::vector<Key> keys;
			for (auto const kv_pair : _creators)
				keys.push_back(kv_pair.first);

			return std::move(keys);
		}

	private:
		CreatorsMap _creators;
};


// __FACTORY_H__
#endif

