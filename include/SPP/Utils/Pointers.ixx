module;
#include <memory>


export module spp.utils.pointers;


namespace SPP::Utils {
    export template <typename Derived, typename Base>
    auto cast_unique(std::unique_ptr<Base> &&base) -> std::unique_ptr<Derived>;
}


template <typename Derived, typename Base>
auto SPP::Utils::cast_unique(std::unique_ptr<Base> &&base) -> std::unique_ptr<Derived> {
    auto d = dynamic_cast<Derived*>(base.get());
    if (d != nullptr) {
        base.release();
        return std::unique_ptr<Derived>(d);
    }
    return nullptr;
}
