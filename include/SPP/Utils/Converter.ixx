module;
#include <string>

export module spp.utils.converter;


export namespace SPP::Utils {
    struct JsonConverter;
    struct StringConverter;
}


struct SPP::Utils::JsonConverter {
    virtual ~JsonConverter() = default;
    virtual auto to_json() const -> std::u8string = 0;
};


struct SPP::Utils::StringConverter {
    virtual ~StringConverter() = default;
    virtual auto to_string() const -> std::u8string = 0;
};
