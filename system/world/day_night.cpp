#include "day_night.hpp"
#include "component/light/directional.hpp"
#include "component/graphic/drawable.hpp"
#include "common/time.hpp"
#include <cmath>

namespace game{

	DayNightSystem::DayNightSystem(){
	}

	DayNightSystem::~DayNightSystem(){ }

	void DayNightSystem::Initialize(){
		day_duration_ = 20;
		night_duration_ = 10;
		light_ = ecs::CreateEntity();
		dlight_ = ecs::CreateComponent<DirectionalLight>(light_, glm::vec3(-1, 1, -0.1), 1.0);
		ecs::CreateComponent<Drawable>(light_);
		day_time_ = true;

		day_color_ramp_.insert(std::make_pair(0, glm::vec4(1.f, 0.62f, 0.85f, 1.f))); // Dawn
		day_color_ramp_.insert(std::make_pair(90, glm::vec4(0.81f, 0.92f, 0.90f, 1.f))); // Noon
		day_color_ramp_.insert(std::make_pair(180, glm::vec4(0.81f, 0.92f, 0.90f, 1.f))); // Dusk

		night_color_ramp_.insert(std::make_pair(180, glm::vec4(1.f, 0.62f, 0.85f, 1.f))); // Dawn
		night_color_ramp_.insert(std::make_pair(90, glm::vec4(0.36f, 0.26f, 0.72f, 0.5f))); // Noon
		night_color_ramp_.insert(std::make_pair(0, glm::vec4(0.81f, 0.92f, 0.90f, 1.f))); // Dusk
	}

	void DayNightSystem::BeforeUpdate(){
		if(light_.uid == 0){ Initialize(); }
		float angle = Time::GetPreviousDeltaTime();

		float x = dlight_->direction.x;
		float y = dlight_->direction.y;
		float z = dlight_->direction.z;

		if(day_time_){
			angle *= 3.1415f/day_duration_;
		} else {
			angle *= -3.1415f/night_duration_;
		}

		float cs = cos(angle);
		float sn = sin(angle);

		float px = x * cs - z * sn;
		float pz = x * sn + z * cs;

		if(pz >= 0){ day_time_ = !day_time_; }

		dlight_->direction = glm::vec3(px, y, pz);
		UpdateColor();
	}

	void DayNightSystem::UpdateColor(){
		float angle = abs(atan2(dlight_->direction.z, dlight_->direction.x) * (180.f/3.1415f));

		auto lower = day_color_ramp_.begin();
		auto higher = day_color_ramp_.begin();

		if(!day_time_){
			lower = night_color_ramp_.begin();
			higher = night_color_ramp_.begin();
		}

		while(higher->first < angle){
			higher++;
		}
		lower = higher;
		lower--;

		float distance_bounds = higher->first - lower->first;
		float d1 = (angle - lower->first) / distance_bounds;
		float d2 = (higher->first - angle) / distance_bounds;
		glm::vec4 res = lower->second * d2 + higher->second * d1;

		dlight_->color = glm::vec3(res);
		dlight_->power = res.a;
	}
}
