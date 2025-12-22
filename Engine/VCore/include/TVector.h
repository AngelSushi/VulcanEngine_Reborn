#pragma once
#include <chrono>
#include <cstdint>

namespace VulcanEngine {

	
	template<typename T>
	class TVector {
		using iterator = typename std::vector<T>::iterator;
		using const_iterator = typename std::vector<T>::const_iterator;
		
	public:
		using value_type = T;
		
		TVector() = default;
		TVector(std::initializer_list<value_type> init) : data(init) {}

		template<typename U, std::enable_if_t<std::is_base_of_v<U,value_type>>>
		operator TVector<U>() const {
			TVector<U> result;
			result.reserve(data.size());
			for (const auto& item : data) {
				if constexpr  (std::is_pointer_v<value_type> && std::is_pointer_v<U>) { // Derived* -> Base*
					result.push_back(Cast<U>(item));
				}
				else if constexpr (is_shared_ptr<value_type>::value && is_shared_ptr<U>::value) { // shared_ptr<Derived> -> shared_ptr<Base>
					result.push_back(std::static_pointer_cast<typename U::element_type>(item));
				}
				else {
					result.push_back(item);
				}
			}
			return result;
		}

		void Add(const T& v) { data.push_back(v); }
		void Add(T&& v) { data.push_back(std::move(v)); }

		void push_back(T v) { data.push_back(std::move(v)); }

		template<typename... Args>
		void emplace_back(Args&&... args) {
			data.emplace_back(std::forward<Args>(args)...);
		}

		template<typename It>
		void insert(iterator pos, It first, It last) {
			data.insert(pos, first, last);
		}

		void erase(iterator pos) { data.erase(pos); }
		void remove(const value_type& value) {
			data.erase(std::remove(data.begin(), data.end(), value), data.end());
		}
		void removeAt(size_t index) {
			if (index < data.size()) {
				data.erase(data.begin() + index);
			}
		}
		
		void  clear() { data.clear(); }

		void reserve(size_t n) { data.reserve(n); }
		size_t size() const { return data.size(); }
		bool empty() const { return data.empty(); }


		iterator begin() noexcept { return data.begin(); }
		iterator end() noexcept { return data.end(); }
		const_iterator begin() const noexcept { return data.begin(); }
		const_iterator end() const noexcept { return data.end(); }

		const_iterator cbegin() const noexcept { return data.cbegin(); }
		const_iterator cend() const noexcept { return data.cend(); }
		

		value_type& operator[](size_t i) { return data[i]; }
		const value_type& operator[](size_t i) const { return data[i]; }
		
	private:
		std::vector<value_type> data;

		template<typename X>
		struct is_shared_ptr : std::false_type {};

		template<typename X>
		struct is_shared_ptr<std::shared_ptr<X>> : std::true_type {};
	};


}
