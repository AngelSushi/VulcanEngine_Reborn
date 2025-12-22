
#pragma once
#include <any>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <stdexcept>

namespace VUI {
   
class Binding {

public:
    Binding() = default;

    using FnType = std::function<std::any(const std::vector<std::any>&)>;

    Binding(std::string name, FnType fn) : BindingName(std::move(name)), Fn(std::move(fn)) {}

    template<typename... Args>
    std::any Invoke(Args&&... args) const {
        if (!Fn) {
            return {};
        }
        
        std::vector<std::any> packed;
        packed.reserve(sizeof...(Args));
        (packed.emplace_back(std::forward<Args>(args)), ...);
        return Fn(packed);
    }

    template<typename T, typename... Args>
    T& InvokeAs(Args&&... args) const {
        std::any result = Invoke(std::forward<Args>(args)...);
        return std::any_cast<std::reference_wrapper<T>>(result);
    }

    template<typename C, typename R, typename... Args>
    static std::unique_ptr<Binding> Register(const std::string& name, C* instance, R(C::*method)(Args...)) {
        auto fn = [instance, method](const std::vector<std::any>& args) -> std::any {
            return invokeMember<C, R, Args...>(instance, method, args, std::index_sequence_for<Args...>{});
        };
        return std::make_unique<Binding>(name, fn);
    }

    
    template<typename T>
    static std::unique_ptr<Binding> Register(const std::string& InName, T& InRef) {
        auto fn = [&InRef](const std::vector<std::any>& args) -> std::any {
            return std::reference_wrapper<T>(InRef);
        };

        return std::make_unique<Binding>(InName, fn);
    }

    template<typename C, typename R>
    static std::unique_ptr<Binding> Register(const std::string& name, C* instance, R(C::*getter)()) {
        auto fn = [instance, getter](const std::vector<std::any>& args) -> std::any {
            if (!args.empty()) {
                throw std::invalid_argument("Getter-only binding cannot take arguments");
            }
            
            if constexpr (std::is_void_v<R>) {
                (instance->*getter)();
                return std::any{};
            }
            else {
                R ref = (instance->*getter)();
                return std::reference_wrapper<std::remove_reference_t<R>>(ref);
            }
        };
        return std::make_unique<Binding>(name, fn);
    }
    
    template<typename C,typename T,typename SetterArg>
    static std::unique_ptr<Binding> Register(const std::string& InName,C* Instance, T(C::*getter)() const,void (C::*setter)(SetterArg)) {
        auto fn = [Instance,getter,setter](const std::vector<std::any>& args) -> std::any {
            if (args.size() == 1) {
                const T& v = std::any_cast<const T&>(args[0]);
                (Instance->*setter)(v);
                T after = (Instance->*getter)();
                return std::any(std::move(after));
            }
            if (args.empty()) {
                T v = (Instance->*getter)(); // Return by value
                return std::any(std::move(v));
            } 

            throw std::invalid_argument("Invalid number of arguments for property binding");
        };

        return std::make_unique<Binding>(InName, fn);
    }

    const std::string& GetName() const { return BindingName; }

private:
    std::string BindingName;
    FnType Fn;

    template<typename T>
    static const T& any_as_ref(const std::any& a) {
        if constexpr (std::is_same_v<T, std::any>) {
            if (a.type() == typeid(std::any)) {
                return std::any_cast<const std::any&>(a);
            }
            
            return a;
        }
        
        if (a.type() == typeid(std::any)) {
            const std::any& inner = std::any_cast<const std::any&>(a);
            if (inner.type() == typeid(T))
                return std::any_cast<const T&>(inner);
        }

        return std::any_cast<const T&>(a);
    }


    template<typename C, typename R, typename... Args, size_t... I>
    static std::any invokeMember(C* instance, R(C::*method)(Args...), const std::vector<std::any>& args, std::index_sequence<I...>) {
        if constexpr (std::is_void_v<R>) {
            (instance->*method)(any_as_ref<Args>(args[I])...);
            return std::any{};
        } else if constexpr (std::is_reference_v<R>) {
            R ref = (instance->*method)(any_as_ref<Args>(args[I])...);
            return std::reference_wrapper<std::remove_reference_t<R>>(ref);
        } else {
            R value = (instance->*method)(any_as_ref<Args>(args[I])...);
            return std::any(std::move(value));
        }
    }
};

} // namespace VUI
