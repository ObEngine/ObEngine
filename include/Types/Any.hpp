#pragma once

#include <type_traits>
#include <typeinfo>

namespace obe 
{
	namespace Types
	{
		class Any 
		{
			public:
				Any() : _value(nullptr) { }
				template<typename T> Any(T& value) : _value(new erasure_impl<typename std::decay<T&>::type>(value)) {}
				Any(Any const& value) : _value(value._value->clone()) {}
				Any(Any& value) : _value(value._value->clone()) {}
				template<typename T> Any(T const& value) : _value(new erasure_impl<typename std::decay<T const&>::type>(value)) {}
				template<typename T> Any(T* value) : _value(new erasure_impl<typename std::decay<T*>::type>(value)) {}
				template<typename T> Any(T const* value) : _value(new erasure_impl<typename std::decay<T const*>::type>(value)) {}
				~Any() { if (_value) { delete _value; } }
				template<typename T> Any& operator=(T& value) {
					if (_value) { delete _value; }
					_value = new erasure_impl<typename std::decay<T&>::type>(value);
					return *this;
				}
				template<typename T> Any& operator=(T const& value) {
					if (_value) { delete _value; }
					_value = new erasure_impl<typename std::decay<T const&>::type>(value);
					return *this;
				}
				template<typename T> Any& operator=(T* value) {
					if (_value) { delete _value; }
					_value = new erasure_impl<typename std::decay<T*>::type>(value);
					return *this;
				}
				template<typename T> Any& operator=(T const* value) {
					if (_value) { delete _value; }
					_value = new erasure_impl<typename std::decay<T const*>::type>(value);
					return *this;
				}
				Any& operator=(Any const& value) {
					if (_value) { delete _value; }
					_value = value._value->clone();
					return *this;
				}
				template<typename T> T& as() const {
					if (_value) return static_cast<erasure_impl<T>*>(_value)->value();
					throw std::bad_cast();
				}
				std::type_info const& type() const {
					if (_value) return _value->type();
					return typeid(nullptr);
				}

			private:
				struct erasure {
					virtual ~erasure();
					virtual erasure* clone() = 0;
					virtual std::type_info const& type() const = 0;
				};

				template<typename T> class erasure_impl : public erasure {
				public:
					erasure_impl(T value) : _value(value) { }
					virtual erasure* clone() { return new erasure_impl<T>(_value); }
					virtual std::type_info const& type() const { return typeid(T); }
					T& value() { return _value; }
				private:
					T _value;
				};
				erasure* _value;
		};
	}
}