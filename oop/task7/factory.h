#ifndef __FACTORY_H__
#define __FACTORY_H__


#include <string>
#include <unordered_map>


template<class Id, class AbstractClass>
class Factory
{
	public:
		class AbstractClassCreator
		{
			public:
				AbstractClassCreator() {}
				virtual ~AbstractClassCreator() {}
				virtual AbstractClass *create() const = 0;
				virtual AbstractClass *operator()() const = 0;
		};

	private:
		template <class C>
		class ClassCreator : public AbstractClassCreator
		{
			public:
				using Class = C;

				ClassCreator() {}
				~ClassCreator() {}
				Class *create() const override
				{
					return new Class();
				}
				Class *operator()() const override
				{
					return create();
				}
		};

	public:
		using ClassMap = std::unordered_map<Id, AbstractClassCreator*, std::hash<Id> >;

		Factory() {}
		~Factory()
		{
			clear();
		}

		// Getters.
		const AbstractClassCreator &get_creator(const Id &id) const
		{
			return *(_class_map.at(id).second);
		}

		// Methods.
		template<class Class>
		bool register_class(const Id &id)
		{
			_class_map.insert({id, new ClassCreator<Class>()});
			return true;
		}

		bool unregister_class(const Id &id)
		{
			_class_map.remove(id);
			return true;
		}

		AbstractClass *create(const Id &id)
		{
			auto it = _class_map.find(id);
			return ((it != _class_map.end())
					? ((*it).second->create())
					: nullptr);
		}

		void clear()
		{
			for (const auto c : _class_map)
				delete c.second;

			_class_map.clear();
		}

	private:
		ClassMap _class_map;
};


// __FACTORY_H__
#endif
