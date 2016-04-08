#include <iostream>
#include <fstream>
#include "deps/lest.hpp"
#include "deps/lest-module.hpp"
#include "common/time.hpp"
#include "common/logger.hpp"
#include "test/context_util.hpp"

namespace game{

	const lest::test time[] = {

		SCENARIO("Time module should return basic information about time"){

			GIVEN("a valid GLFW context"){
				ContextUtil::CreateOpenGLContext();

				WHEN("the current date is requested"){
					float date = Time::GetCurrentTime();

					THEN("It should return the seconds since application started"){
						EXPECT(date > 0);
					}
				}

				GIVEN("the begining of a frame was notified"){
					Time::NotifyFrameStart();

					WHEN("current frame advance is requested"){
						float current_advance = Time::GetCurrentFrameAdvance();

						THEN("it should return how much time passed since the begining"
								+ "of the frame"){
							EXPECT(current_advance > 0);
						}
					}
					WHEN("previous delta time is requested"){
						float previous_time = Time::GetPreviousDeltaTime();

						THEN("it should return how much time it took for the last frame"
								+ "to finish"){
							EXPECT(previous_time > 0);
						}
					}
				}

				ContextUtil::DestroyOpenGLContext();
			}
		}

	};

	extern lest::tests & specifications();
	lest_ADD_MODULE(specifications(), time);
}
