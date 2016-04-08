#ifndef TOOLS_LOGGER_HPP
#define TOOLS_LOGGER_HPP

#include <iostream>

namespace game{

#define LOG(x) Logger(x, __FILE__, __FUNCTION__, __LINE__)
#define FLOG(x,y) Logger(x, __FILE__, __FUNCTION__, __LINE__, y)

	namespace color {
		enum Code {
			FG_RED		= 31,
			FG_GREEN	= 32,
			FG_YELLOW	= 33,
			FG_BLUE		= 34,
			FG_DEFAULT	= 39,
			BG_RED		= 41,
			BG_GREEN	= 42,
			BG_BLUE		= 44,
			BG_DEFAULT	= 49
		};
		inline std::ostream& operator<<(std::ostream& os, Code code) {
			return os << "\033[" << static_cast<int>(code) << "m";
		}
	}

	enum Level{SILENT=0, INFO=1, DEBUG=2, WARNING=3, ERROR=4, CRITICAL=5, NONE=6};

	class Logger{
		public:
			Logger( Level l,
					const char* file,
					const char* function,
					int line,
					std::ostream &o = std::cout) : output_(o){

				this->level_ = l;
				this->begining_ = true;
				this->file_ = file;
				this->function_ = function;
				this->line_ = line;
			}

			template <typename T>
			Logger& operator<<(const T &a) {

				color::Code id_color_code;
				color::Code text_color_code;
				std::string identifier;

				switch(this->level_){
					case INFO:
						id_color_code = color::FG_GREEN;
						text_color_code = color::FG_DEFAULT;
						identifier = "info : ";
						break;
					case WARNING:
						id_color_code = color::FG_YELLOW;
						text_color_code = color::FG_DEFAULT;
						identifier = "warning : ";
						break;
					case DEBUG:
						id_color_code = color::FG_BLUE;
						text_color_code = color::FG_DEFAULT;
						identifier = "debug : ";
						break;
					case ERROR:
						id_color_code = color::FG_RED;
						text_color_code = color::FG_YELLOW;
						identifier = "error : ";
						break;
					case CRITICAL:
						id_color_code = text_color_code = color::FG_RED;
						identifier = "critical : ";
						break;
					case SILENT:
						id_color_code = color::FG_DEFAULT;
						text_color_code = color::FG_DEFAULT;
						this->begining_ = false;
						break;
					default:
						id_color_code = color::FG_YELLOW;
						text_color_code = color::FG_DEFAULT;
						identifier = "unknow :";
				}

				// Display message type
				if(this->begining_){
					output_ << this->file_ << " - ";
					output_ << this->function_ << ":" << this->line_ << " ";
					output_ << id_color_code;
					output_ << identifier;
					this->begining_ = false;
				}

				output_ << text_color_code << a << color::FG_DEFAULT;
				return *this;
			}

			Logger& operator<<(std::ostream& (*pf) (std::ostream&)){
				output_<<pf;
				return *this;
			}

		private:
			std::ostream &output_;
			Level level_;
			bool begining_;
			int line_;
			const char* file_;
			const char* function_;
	};

}

#endif //TOOLS_LOGGER_HPP
