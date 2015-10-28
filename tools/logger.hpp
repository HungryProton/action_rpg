#ifndef TOOLS_LOGGER_HPP
#define TOOLS_LOGGER_HPP

#include <iostream>

namespace game{

#define LOG(x) Logger(x, __FILE__, __FUNCTION__, __LINE__)
#define FLOG(x,y) Logger(x, __FILE__, __FUNCTION__, __LINE__, y)

    namespace color {
        enum Code {
            FG_RED      = 31,
            FG_GREEN    = 32,
            FG_YELLOW   = 33,
            FG_BLUE     = 34,
            FG_DEFAULT  = 39,
            BG_RED      = 41,
            BG_GREEN    = 42,
            BG_BLUE     = 44,
            BG_DEFAULT  = 49
        };
        inline std::ostream& operator<<(std::ostream& os, Code code) {
            return os << "\033[" << static_cast<int>(code) << "m";
        }
    }

    enum Level{SILENT, INFO, WARNING, ERROR};

    class Logger{
        public:
            Logger( Level l,
                    const char* file,
                    const char* function,
                    int line,
                    std::ostream &o = std::cout) : output(o){

                this->level = l;
                this->begining = true;
                this->file = file;
                this->function = function;
                this->line = line;
            }

            template <typename T>
            Logger& operator<<(const T &a) {
                color::Code id_color_code;
                color::Code text_color_code;
                std::string identifier;

                switch(this->level){
                    case INFO:
                        id_color_code = color::FG_GREEN;
                        text_color_code = color::FG_DEFAULT;
                        identifier = "info : ";
                        break;
                    case WARNING:
                        id_color_code = text_color_code = color::FG_YELLOW;
                        identifier = "warning : ";
                        break;
                    case ERROR:
                        id_color_code = text_color_code = color::FG_RED;
                        identifier = "error : ";
                        break;
                    case SILENT:
                        id_color_code = color::FG_DEFAULT;
                        text_color_code = color::FG_DEFAULT;
                        this->begining = false;
                    default:
                        id_color_code = color::FG_YELLOW;
                        text_color_code = color::FG_DEFAULT;
                        identifier = "unknow :";
                }

                // Display message type
                if(this->begining){
                    output << this->file << " - ";
                    output << this->function << ":" << this->line << " ";
                    output << id_color_code;
                    output << identifier;
                    this->begining = false;
                }

                output << text_color_code << a << color::FG_DEFAULT;
                return *this;
            }

            Logger& operator<<(std::ostream& (*pf) (std::ostream&)){
                output<<pf;
                return *this;
            }

        private:
            std::ostream &output;
            Level level;
            bool begining;
            int line;
            const char* file;
            const char* function;
    };
}

#endif //TOOLS_LOGGER_HPP
