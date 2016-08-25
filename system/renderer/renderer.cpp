#include "renderer.hpp"
#include "ecs/ecs.hpp"
#include "component/camera.hpp"
#include "component/transform.hpp"
#include "component/drawable.hpp"
#include "component/light/point.hpp"

namespace game{

	Renderer::Renderer() : System(){
		context_controller_.Initialize();
		glm::ivec2 size = context_controller_.GetWindowSize();
		shader_controller_.Initialize(size.x, size.y);
		Require<Transform, Drawable>();
		max_lights = 12;
	}

	Renderer::~Renderer(){}

	void Renderer::BeforeUpdate(){
		camera_controller_.Update();
		context_controller_.SwapBuffers();
		shader_controller_.Enable(Program::G_BUFFER);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader_controller_.UniformMatrix4fv("View", camera_controller_.GetView());
		shader_controller_.UniformMatrix4fv("Projection", camera_controller_.GetProjection());
	}

	void Renderer::OnUpdate(Entity entity){
		ProcessLightIfAny(entity);
		RenderComponent node = GetComponentsFor(entity);
		if(!node.is_valid){ return; }

		if(node.texture){
			node.texture->Bind(GL_TEXTURE0);
		}

		glm::vec3 local_scale = glm::vec3(1.f, 1.f, 1.f);
		if(node.drawable->type == DrawableType::SPRITE){
			local_scale = node.texture->local_scale;
		}

		shader_controller_.Uniform2f("TexRatio", -1, -1);
		shader_controller_.UniformMatrix4fv("Model", GetModelMatrixFor(node.transform, local_scale));

		Draw(node.drawable);
	}

	void Renderer::AfterUpdate(){
		shader_controller_.Enable(Program::SSAO);
		shader_controller_.UniformMatrix4fv("projection", camera_controller_.GetProjection());
		shader_controller_.Uniform1i("kernelSize", 1);
		//shader_controller_.RenderToScreen();

		shader_controller_.Enable(Program::BLOOM);
		//shader_controller_.RenderToScreen();

		shader_controller_.Enable(Program::LIGHTING);
		shader_controller_.Uniform3f("viewPos", camera_controller_.GetPosition());
		SendLightsToShader();
		shader_controller_.RenderToScreen();
	}

	void Renderer::Draw(Drawable* drawable){
		glBindVertexArray(drawable->vao);
		glDrawElements(drawable->draw_type, drawable->vertex_amount,
				GL_UNSIGNED_INT, BUFFER_OFFSET(drawable->offset));
	}

	glm::mat4 Renderer::GetModelMatrixFor(Transform* transform, glm::vec3 local_scale){
		glm::mat4 translation = glm::translate(glm::mat4(1.0f),
																					 glm::vec3(transform->position));
		glm::mat4 rotation_x = glm::rotate(translation, transform->rotation.x*0.0174532925199433f,
																			 glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rotation_xy = glm::rotate(rotation_x, transform->rotation.y*0.0174532925199433f,
																				glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 rotation_xyz = glm::rotate(rotation_xy, transform->rotation.z*0.0174532925199433f,
																				glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scale = glm::scale(transform->scale * local_scale);
		return rotation_xyz * scale;
	}

	void Renderer::ProcessLightIfAny(Entity entity){
		if(lights_.size() >= max_lights){ return; }
		PointLight* pl = ecs::GetComponent<PointLight>(entity);
		if(pl == nullptr){ return; }
		Transform* t = ecs::GetComponent<Transform>(entity);

		glLight light;
		light.intensity = pl->power;
		light.position = t->position;
		light.color = pl->color;

		lights_.push_back(light);
	}

	void Renderer::SendLightsToShader(){
		std::vector<float> power;
		std::vector<glm::vec3> pos;
		std::vector<glm::vec3> col;

		for(glLight light : lights_){
			power.push_back(light.intensity);
			pos.push_back(glm::vec3(camera_controller_.GetView() * glm::vec4(light.position, 1.0)));
			col.push_back(light.color);
		}

		shader_controller_.Uniform1fv("lightsIntensity", power.size(), &power[0]);
		shader_controller_.Uniform3fv("lightsPos", pos.size(), &pos[0].x);
		shader_controller_.Uniform3fv("lightsCol", col.size(), &col[0].x);

		lights_.clear();
	}

	RenderComponent Renderer::GetComponentsFor(Entity entity){
		RenderComponent node;
		node.is_valid = false;
		node.drawable = ecs::GetComponent<Drawable>(entity);

		if(!node.drawable){ return node; }
		if(node.drawable->vao == 0){
			int err = drawable_builder_.UpdateDrawableOf(entity);
			if(err){ return node; }
		}
		node.transform = ecs::GetComponent<Transform>(entity);
		node.texture = ecs::GetComponent<Texture>(entity);
		node.mesh = ecs::GetComponent<Mesh>(entity);
		node.is_valid = true;
		return node;
	}

	GLFWwindow* Renderer::GetWindow(){
		return this->context_controller_.GetWindow();
	}
}
