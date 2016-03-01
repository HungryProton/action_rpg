#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "physic.hpp"
#include "core/entity/game_object.hpp"
#include "core/component/transform.hpp"
#include "core/component/collider.hpp"
#include "core/component/shapes/box.hpp"
#include "core/component/shapes/circle.hpp"
#include "tools/time.hpp"
#include "tools/math.hpp"

namespace game{

	Physic::~Physic(){

	}

	void Physic::ClearMemory(){

	}

	void Physic::Update(){
		this->ProcessReceivedMessages();
		this->UpdatePositions();
		this->ResolveCollisions();
	}

	void Physic::ProcessReceivedMessages(){
		for(PhysicIntent message : this->MessageHandler<PhysicIntent>::messages_){
			switch(message.action){
				case PhysicAction::APPLY_FORCE:
					this->ApplyForce(message.force, message.game_object);
					break;
				case PhysicAction::ADD_COLLIDER:
					this->AddGameObjectToColliderPool(message.game_object);
					break;
			}
		}
		this->MessageHandler<PhysicIntent>::messages_.clear();
	}

	void Physic::AddGameObjectToColliderPool(GameObject* object){
		if(!object){ return; }
		if(!(object->GetComponent<Collider>())){ return; }
		if(!(object->GetComponent<Transform>())){ return; }

		this->collider_pool_.push_back(object);
	}

	void Physic::ApplyForce(glm::vec3 force, GameObject* object){
		Transform* transform = object->GetComponent<Transform>();
		Collider* collider = object->GetComponent<Collider>();
		transform->target_velocity += force * collider->inv_mass * Time::GetDeltaTime();
	}

	void Physic::UpdatePositions(){
		for(GameObject* object : this->collider_pool_){
			Transform* transform = object->GetComponent<Transform>();
			//transform->position += transform->target_velocity*Time::GetDeltaTime();
		}
	}

	void Physic::ResolveCollisions(){

		for(auto it_a = this->collider_pool_.begin();
				it_a != this->collider_pool_.end();
				it_a++){

			Collider* collider_a = (*it_a)->GetComponent<Collider>();

			auto it_b = it_a;
			for(it_b++; it_b != this->collider_pool_.end(); it_b++){

				Collider* collider_b = (*it_b)->GetComponent<Collider>();

				// early return if both objects are static
				if((collider_a->mass == 0) && (collider_b->mass == 0)){ continue; }

				if(collider_a->shape_type == typeid(Circle)){

					if( collider_b->shape_type == typeid(Circle)){
						this->CirclevsCircle(*it_a, *it_b);
					} else if (collider_b->shape_type == typeid(Box)){
						this->BoxvsCircle(*it_a, *it_b);
					}
				} else if(collider_a->shape_type == std::type_index(typeid(Box))){

					if( collider_b->shape_type == std::type_index(typeid(Box))){
						this->BoxvsBox(*it_a, *it_b);
					} else if ( collider_b->shape_type == std::type_index(typeid(Circle))){
						this->BoxvsCircle(*it_a, *it_b);
					}
				}
			}
		}
		this->collider_pool_.clear();
	}

	// Resolve collision between the two objects and mark them as resolved
	// to avoid the other object trying to resolve the collisions once more
	// during the same frame.

	void Physic::BoxvsBox(GameObject* a, GameObject* b){

		Box* box_a = a->GetComponent<Box>();
		Box* box_b = b->GetComponent<Box>();

		Transform* transform_a = a->GetComponent<Transform>();
		Transform* transform_b = b->GetComponent<Transform>();

		float first_extent = box_a->width / 2;
		float second_extent = box_b->width / 2;

		float nx = transform_a->position.x - transform_b->position.x;
		float abs_nx = nx;
		if(nx < 0){ abs_nx *= -1; }

		float overlap_x = first_extent + second_extent - abs_nx;

		if(overlap_x < 0){ return; }

		float ny = transform_a->position.y - transform_b->position.y;
		float overlap_y;

		if(ny < 0){
			overlap_y = box_a->height + ny;
		} else {
			overlap_y = box_b->height - ny;
		}

		if(overlap_y < 0){ return; }

		// If we reach that place, a collision occured

		glm::vec3 normal;
		float penetration;

		if( overlap_x < overlap_y){
			(nx < 0) ? normal = glm::vec3(1, 0, 0) : normal = glm::vec3(-1, 0, 0);
			penetration = overlap_x;
		} else {
			(ny > 0) ? normal = glm::vec3(0, -1, 0) : normal = glm::vec3(0, 1, 0);
			penetration = overlap_y;
		}

		Manifold m;
		m.penetration = penetration;
		m.collider_a = a->GetComponent<Collider>();
		m.collider_b = b->GetComponent<Collider>();
		m.transform_a = transform_a;
		m.transform_b = transform_b;
		m.normal = normal;

		ApplyImpulse(m);
		ApplyFriction(m);
		PositionalCorrection(m);
	}

	void Physic::CirclevsCircle(GameObject* a, GameObject* b){

		Transform* transform_a = a->GetComponent<Transform>();
		Transform* transform_b = b->GetComponent<Transform>();

		Circle* circle_a = a->GetComponent<Circle>();
		Circle* circle_b = b->GetComponent<Circle>();

		glm::vec3 normal = transform_b->position - transform_a->position;
		float r = circle_b->radius + circle_a->radius;
		float r2 = r * r;

		if(glm::length2(normal) > r2){ return; }

		float distance = glm::length(normal);
		float penetration;

		if(distance != 0){
			penetration = r - distance;
			normal = glm::normalize(normal);
		} else {
			penetration = circle_a->radius;
			normal = glm::vec3(0, 0, 1);
		}

		Manifold m;
		m.penetration = penetration;
		m.collider_a = a->GetComponent<Collider>();
		m.collider_b = b->GetComponent<Collider>();
		m.transform_a = transform_a;
		m.transform_b = transform_b;
		m.normal = normal;

		ApplyImpulse(m);
		ApplyFriction(m);
		PositionalCorrection(m);
	}

	void Physic::BoxvsCircle(GameObject* a, GameObject* b){

		// First, determine wheter a or b is a circle or a box
		Circle* circle;
		Box* box;

		Transform* transform_circle;
		Transform* transform_box;

		Collider* collider_circle = a->GetComponent<Collider>();
		Collider* collider_box;

		if(collider_circle->shape_type == typeid(Circle)){
			circle = a->GetComponent<Circle>();
			box = b->GetComponent<Box>();
			collider_box = b->GetComponent<Collider>();
			transform_box = b->GetComponent<Transform>();
			transform_circle = a->GetComponent<Transform>();
		} else {
			circle = b->GetComponent<Circle>();
			box = a->GetComponent<Box>();
			collider_box = collider_circle;
			collider_circle = b->GetComponent<Collider>();
			transform_box = a->GetComponent<Transform>();
			transform_circle = b->GetComponent<Transform>();
		}

		glm::vec3 V_AB = transform_circle->position - transform_box->position;

		glm::vec3 closest;

		float x_extent = box->width/2;
		float y_extent = box->height/2;

		closest.x = Math::clamp(V_AB.x, -x_extent, x_extent);
		closest.y = Math::clamp(V_AB.y, -y_extent, y_extent);

		bool inside = false;

		if( V_AB == closest ){
			inside = true;

			if(std::abs(V_AB.x) > std::abs(V_AB.y)){
				(closest.x > 0) ? closest.x = x_extent : closest.x = -x_extent;
			}else{
				(closest.y > 0) ? closest.y = x_extent : closest.y = -y_extent;
			}
		}

		glm::vec3 normal = V_AB - closest;
		float distance = glm::length2( normal );
		float r = circle->radius;
		r *= r;

		if( (distance > r) && !inside ){ return; }

		// Collision occured

		if(inside){
			normal = -normal;
		}

		Manifold m;
		m.penetration = std::abs(circle->radius - glm::length(normal));
		m.normal = normal;
		m.collider_a = collider_box;
		m.collider_b = collider_circle;
		m.transform_a = transform_box;
		m.transform_b = transform_circle;

		ApplyImpulse(m);
		ApplyFriction(m);
		PositionalCorrection(m);
	}

	void Physic::ApplyImpulse(Manifold m){
		// Relative velocity
		glm::vec3 relative_velocity = m.transform_b->velocity - m.transform_a->velocity;

		float velocity_along_normal = glm::dot( relative_velocity, m.normal );

		// If the objects are already moving appart, do not resolve collision
		if (velocity_along_normal > 0){ return; }

		float e = std::min(m.collider_a->restitution_factor,
							 m.collider_b->restitution_factor);

		// Impulse scalar
		float j = -(1+e) * velocity_along_normal;
		j /= m.collider_a->inv_mass + m.collider_b->inv_mass;

		// Apply Impulse
		glm::vec3 impulse = j * m.normal;

		float mass_sum = m.collider_a->mass + m.collider_b->mass;
		float ratio = m.collider_a->mass / mass_sum;
		m.transform_a->target_velocity -= ratio * impulse;

		ratio = m.collider_b->mass / mass_sum;
		m.transform_b->target_velocity += ratio * impulse;
	}

	void Physic::ApplyFriction(Manifold m){
		glm::vec3 rv = m.transform_b->velocity - m.transform_a->velocity;
		glm::vec3 tangent;
		tangent.x = -m.normal.z;
		tangent.y = 0;
		tangent.z = m.normal.x;

		float jt = -glm::dot(rv, tangent);
		jt /= (m.collider_b->inv_mass + m.collider_a->inv_mass);

		glm::vec3 friction = jt * tangent;

		m.transform_a->target_velocity -= m.collider_a->inv_mass * friction;
		m.transform_b->target_velocity += m.collider_b->inv_mass * friction;
	}

	void Physic::PositionalCorrection(Manifold m){
		// Positionnal correction :
		// Prevent objects from sinking into infinite mass objects

		const float percent = 1.0f;
		const float slop = 0.002f;
		float correction_ratio = std::max(m.penetration-slop, 0.f) / (m.collider_a->inv_mass + m.collider_b->inv_mass) * percent;
		glm::vec3 correction = m.normal;
		correction *= correction_ratio;

		m.transform_a->position += (-1 * m.collider_a->inv_mass * correction);
		m.transform_b->position += (m.collider_b->inv_mass * correction);
	}
}
