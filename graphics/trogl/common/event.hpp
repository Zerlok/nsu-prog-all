#ifndef __EVENT_HPP__
#define __EVENT_HPP__


#include <vector>
#include <queue>
#include <list>
#include <unordered_map>


template<class I, class T = void, class P = void>
struct EventTraits
{
	using Id = I;
	using DerivedType = T;
	using EventParent = P;
};


template<class V, class T = EventTraits<size_t, void, void> >
class Event
{
	public:
		using Traits = T;
		using Value = V;

		class Hash
		{
			public:
				size_t operator()(const Event<V, T>& event) const
				{
					return std::hash<typename Traits::Id>()(event._id);
				}
		};

		Event(const typename Traits::Id& id,
			  const Value& value,
			  typename Traits::EventParent* parent = nullptr)
			: _id(id),
			  _value(value),
			  _parent(parent) {}
		Event(const Event& event)
			: _id(event._id),
			  _value(event._value),
			  _parent(event._parent) {}
		Event(Event&& event)
			: _id(std::move(event._id)),
			  _value(std::move(event._value)),
			  _parent(event._parent) {}
		virtual ~Event() {}

		bool operator==(const Event& event) const
		{
			return (_id == event._id);
		}

		bool operator!=(const Event& event) const
		{
			return (!this->operator==(event));
		}

		Event& operator=(const Event& event)
		{
			_id = event._id;
			_value = event._value;
			_parent = event._parent;

			return (*this);
		}

		Event& operator=(Event&& event)
		{
			_id = std::move(event._id);
			_value = std::move(event._value);
			_parent = event._parent;

			return (*this);
		}

		const typename Traits::Id& getId() const { return _id; }
		const Value& getValue() const { return _value; }
		typename Traits::EventParent* getParent() const { return _parent; }

		typename Traits::DerivedType* cast()
		{
			return this;
		}

	private:
		typename Traits::Id _id;

	protected:
		Value _value;
		typename Traits::EventParent* _parent;
};


template<class E>
class EventListener
{
	public:
		using Event = E;

		EventListener() = default;
		EventListener(const EventListener&) = default;
		EventListener(EventListener&&) =default ;
		virtual ~EventListener() {}

		EventListener& operator=(const EventListener& listener) = default;
		EventListener& operator=(EventListener&& listener) = default;

		virtual void onPerformed(const Event& event) = 0;
};


template<class E, class L>
class EventsHandler
{
	public:
		using Event = E;
		using Listener = L;
		using Events = std::list<Event>;
		using Listeners = std::list<Listener*>;
		using Map = std::unordered_map<Event, Listeners, typename Event::Hash>;

		EventsHandler()
			: _eventsQueue(),
			  _listenersMap() {}
		virtual ~EventsHandler()
		{
			for (Listener* l : _registeredListeners)
				delete l;
		}

		void registrate(const Event& event, Listener* eventListener)
		{
			Listeners& listeners = _listenersMap[event];

			for (Listener* l : listeners)
				if (l == eventListener)
					return;

			listeners.push_back(eventListener);

			for (Listener* l : _registeredListeners)
				if (l == eventListener)
					return;

			_registeredListeners.push_back(eventListener);
		}

		void push(Event&& event)
		{
			_eventsQueue.push_back(event);
		}

		void push(const Event& event)
		{
			_eventsQueue.push_back(event);
		}

		void handleEvents()
		{
			for (const Event& event : _eventsQueue)
				for (Listener* listener : _listenersMap[event])
					listener->onPerformed(event);

			_eventsQueue.clear();
		}

	private:
		Events _eventsQueue;
		Listeners _registeredListeners;
		Map _listenersMap;
};


#endif // __EVENT_HPP__
