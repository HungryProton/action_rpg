#include <cstdlib>
#include <ctime>
#include <map>
#include <iostream>
#include <thread>
#include "core/modules/modules.hpp"
#include "tools/logger.hpp"

namespace game{

    void Game::Start(){
        log(INFO) << "Starting main thread" << std::endl;
        log(WARNING) << "Caution : error control is not implemented yet!" << std::endl;
        log(ERROR) << "ERROR : Some stuff have gone wrong!" << std::endl;

        //Render::Start();
        
        //Render::Stop();

    }

    int Game::ProcessSomeStuff(std::string msg){
        std::cout << "Game:: Asked to process this stuff : " << msg << std::endl;
        return EXIT_SUCCESS;
    }

}

