#ifndef __FACTORY_H__
#define __FACTORY_H__


#include <string>
#include <vector>
#include <unordered_map>
using Strings = std::vector<std::string>;


template<class K, class B>
class PrototypeFactory
{
	public:
		using Key = K;
		using BaseCls = B;
		using BaseCreator = typename BaseCls::AbstractPrototype;
		using CreatorsMap = std::unordered_map<Key, BaseCreator*>;

		PrototypeFactory() {}
		PrototypeFactory(const PrototypeFactory<Key, BaseCls>&) = delete;
		~PrototypeFactory()
		{
			for (const std::pair<Key, BaseCreator*>& kv_pair : _creators)
				delete kv_pair.second;
		}

		template<class DerivedCls>
		bool registerate(const Key& key)
		{
			if (_creators.find(key) != _creators.end())
				return false;

			using DerivedPrototype = typename DerivedCls::Prototype;
			_creators.insert({key, new DerivedPrototype() });
			return true;
		}

		BaseCreator* get(const Key& key)
		{
			typename CreatorsMap::iterator it = _creators.find(key);
			return ((it != _creators.end())
					? (it->second)
					: nullptr);
		}

		std::vector<Key> get_registred() const
		{
			std::vector<Key> keys;
			for (const std::pair<Key, BaseCreator*>& kv_pair : _creators)
				keys.push_back(kv_pair.first);

			return std::move(keys);
		}

	private:
		CreatorsMap _creators;
};


// __FACTORY_H__
#endif

