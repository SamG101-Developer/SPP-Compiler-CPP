module;
#include <string>


export module spp.utils.pretty_printer;


export namespace SPP::Utils::PrettyPrinter {
    namespace Foreground {
        const std::string Black = "\033[30m";
        const std::string Red = "\033[31m";
        const std::string Green = "\033[32m";
        const std::string Yellow = "\033[33m";
        const std::string Blue = "\033[34m";
        const std::string Magenta = "\033[35m";
        const std::string Cyan = "\033[36m";
        const std::string White = "\033[37m";
        const std::string LightBlackEx = "\033[90m";
        const std::string LightRedEx = "\033[91m";
        const std::string LightGreenEx = "\033[92m";
        const std::string LightYellowEx = "\033[93m";
        const std::string LightBlueEx = "\033[94m";
        const std::string LightMagentaEx = "\033[95m";
        const std::string LightCyanEx = "\033[96m";
        const std::string LightWhiteEx = "\033[97m";
    }

    namespace Background {
        const std::string Black = "\033[40m";
        const std::string Red = "\033[41m";
        const std::string Green = "\033[42m";
        const std::string Yellow = "\033[43m";
        const std::string Blue = "\033[44m";
        const std::string Magenta = "\033[45m";
        const std::string Cyan = "\033[46m";
        const std::string White = "\033[47m";
        const std::string LightBlackEx = "\033[100m";
        const std::string LightRedEx = "\033[101m";
        const std::string LightGreenEx = "\033[102m";
        const std::string LightYellowEx = "\033[103m";
        const std::string LightBlueEx = "\033[104m";
        const std::string LightMagentaEx = "\033[105m";
        const std::string LightCyanEx = "\033[106m";
        const std::string LightWhiteEx = "\033[107m";
    }

    namespace Style {
        const std::string Reset = "\033[0m";
        const std::string Bold = "\033[1m";
        const std::string Dim = "\033[2m";
        const std::string Italic = "\033[3m";
        const std::string Underline = "\033[4m";
        const std::string Strikethrough = "\033[9m";
        const std::string Normal = "\033[22m";
    }
}
