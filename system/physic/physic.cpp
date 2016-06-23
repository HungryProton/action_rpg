#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "physic.hpp"
#include "ecs/entity.hpp"
#include "component/transform.hpp"
#include "component/collider.hpp"
#include "component/shapes/box.hpp"
#include "component/shapes/circle.hpp"
#include "common/time.hpp"
#include "common/math.hpp"

namespace game{

	Physic::Physic() : System(){}
	Physic::~Physic(){}

	void Physic::BeforeUpdate(){
		this->MessageHandler<PhysicIntent>::PollMessages();
	}

	void Physic::OnUpdate(unsigned long entity){
		PhysicComponents* components = this->GetComponentsFor(entity);
		if(components != nullptr){
			this->UpdatePositions(components);
			this->ResolveCollisions(entity, components);
		}
	}

	PhysicComponents* Physic::GetComponentsFor(unsigned long id){
		auto pair = this->entities_.find(id);
		if(pair == this->entities_.end()){
			PhysicComponents c;
			c.transform = Entity::GetComponent<Transform>(id);
			c.collider = Entity::GetComponent<Collider>(id);
			if(c.transform == nullptr || c.collider == nullptr){ return nullptr; }
			switch(c.collider->shape_type){
				case Shape::BOX:
					c.shape = Entity::GetComponent<Box>(id);
					break;
				case Shape::CIRCLE:
					c.shape = Entity::GetComponent<Circle>(id);
			}
			if(c.shape == nullptr){ return nullptr; }
			this->entities_.insert(std::make_pair(id, c));
		}
		return &(this->entities_.find(id)->second);
	}

	void Physic::OnMessage(PhysicIntent message){
		switch(message.action){
			case PhysicAction::APPLY_FORCE:
				this->ApplyForce(message.force, message.dest_id);
				break;
		}
	}

	void Physic::ApplyForce(glm::vec3 force, unsigned long object){
		PhysicComponents* c = this->GetComponentsFor(object);
		if(c == nullptr){ return; }
		c->collider->target_velocity += force
			* c->collider->inv_mass
			* Time::GetPreviousDeltaTime()
			* 0.5f;
	}

	void Physic::UpdatePositions(PhysicComponents* c){
		c->transform->position += c->collider->target_velocity*Time::GetPreviousDeltaTime();
		float friction_modifier = 0.1; // Retrieve that from material when possible
		glm::vec3 friction_vector = glm::normalize(c->collider->target_velocity)
			* friction_modifier
			* Time::GetPreviousDeltaTime();
		c->collider->target_velocity -= friction_vector;
	}

	void Physic::ResolveCollisions(unsigned long id, PhysicComponents* ca){
		Collider* collider_a = ca->collider;

		for(auto pair : this->entities_){
			if(pair.first == id){ continue; }
			PhysicComponents* cb = &(pair.second);

			Collider* collider_b = cb->collider;

			// early return if both objects are static
			if((collider_a->mass == 0) && (collider_b->mass == 0)){ continue; }

			if(collider_a->shape_type == Shape::CIRCLE){

				if(collider_b->shape_type == Shape::CIRCLE){
					this->CirclevsCircle(ca, cb);
				} else if(collider_b->shape_type == Shape::BOX){
					this->BoxvsCircle(ca, cb);
				}
			} else if(collider_a->shape_type == Shape::BOX){

				if(collider_b->shape_type == Shape::BOX){
					this->BoxvsBox(ca, cb);
				} else if(collider_b->shape_type == Shape::CIRCLE){
					this->BoxvsCircle(ca, cb);
				}
			}
		}
	}

	// Resolve collision between the two objects and mark them as resolved
	// to avoid the other object trying to resolve the collisions once more
	// during the same frame.

	void Physic::BoxvsBox(PhysicComponents* a, PhysicComponents* b){

		Box* box_a = (Box*)a->shape;
		Box* box_b = (Box*)b->shape;

		Transform* transform_a = a->transform;
		Transform* transform_b = b->transform;

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

		PhysicManifold m;
		m.penetration = penetration;
		m.collider_a = a->collider;
		m.collider_b = b->collider;
		m.transform_a = transform_a;
		m.transform_b = transform_b;
		m.normal = normal;

		ApplyImpulse(m);
		ApplyFriction(m);
		PositionalCorrection(m);
	}

	void Physic::CirclevsCircle(PhysicComponents* a, PhysicComponents* b){

		Transform* transform_a = a->transform;
		Transform* transform_b = b->transform;

		Circle* circle_a = (Circle*)a->shape;
		Circle* circle_b = (Circle*)b->shape;

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

		PhysicManifold m;
		m.penetration = penetration;
		m.collider_a = a->collider;
		m.collider_b = b->collider;
		m.transform_a = transform_a;
		m.transform_b = transform_b;
		m.normal = normal;

		ApplyImpulse(m);
		ApplyFriction(m);
		PositionalCorrection(m);
	}

	void Physic::BoxvsCircle(PhysicComponents* a, PhysicComponents* b){

		// First, determine wheter a or b is a circle or a box
		Circle* circle;
		Box* box;

		Transform* transform_circle;
		Transform* transform_box;

		Collider* collider_circle = a->collider;
		Collider* collider_box;

		if(collider_circle->shape_type == Shape::CIRCLE){
			circle = (Circle*)a->shape;
			box = (Box*)b->shape;
			collider_box = b->collider;
			transform_box = b->transform;
			transform_circle = a->transform;
		} else {
			circle = (Circle*)b->shape;
			box = (Box*)a->shape;
			collider_box = collider_circle;
			collider_circle = b->collider;
			transform_box = a->transform;
			transform_circle = b->transform;
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

		PhysicManifold m;
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

	void Physic::ApplyImpulse(PhysicManifold m){
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
		m.collider_a->target_velocity -= ratio * impulse;

		ratio = m.collider_b->mass / mass_sum;
		m.collider_b->target_velocity += ratio * impulse;
	}

	void Physic::ApplyFriction(PhysicManifold m){
		glm::vec3 rv = m.transform_b->velocity - m.transform_a->velocity;
		glm::vec3 tangent;
		tangent.x = -m.normal.z;
		tangent.y = 0;
		tangent.z = m.normal.x;

		float jt = -glm::dot(rv, tangent);
		jt /= (m.collider_b->inv_mass + m.collider_a->inv_mass);

		glm::vec3 friction = jt * tangent;

		m.collider_a->target_velocity -= m.collider_a->inv_mass * friction;
		m.collider_b->target_velocity += m.collider_b->inv_mass * friction;
	}

	void Physic::PositionalCorrection(PhysicManifold m){
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
