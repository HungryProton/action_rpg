#ifndef TOOLS_LOGGER_HPP
#define TOOLS_LOGGER_HPP

#define log(x) Logger(x, __FILE__, __FUNCTION__, __LINE__)
//#define log(x,y) Logger(x, __FILE__, __FUNCTION__, __LINE__, y)

#include <iostream>

namespace game{

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
        std::ostream& operator<<(std::ostream& os, Code code) {
            return os << "\033[" << static_cast<int>(code) << "m";
        }
    }

    enum Level{INFO, WARNING, ERROR};

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
                color::Code color_code;
                std::string identifier;

                switch(this->level){
                    case INFO:
                        color_code = color::FG_DEFAULT;
                        identifier = "info : ";
                        break; 
                    case WARNING:
                        color_code = color::FG_YELLOW;
                        identifier = "warning : ";
                        break;
                    case ERROR:
                        color_code = color::FG_RED;
                        identifier = "error : ";
                        break;
                    default:
                        color_code = color::FG_DEFAULT;
                }

                output << color_code;

                // Display message type
                if(this->begining){ 
                    output << this->file << " - ";
                    output << this->function << ":" << this->line << " "; 
                    output << identifier;
                    this->begining = false;
                }

                output << a << color::FG_DEFAULT;
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
