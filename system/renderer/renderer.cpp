#include "renderer.hpp"
#include "ecs/ecs.hpp"
#include "component/camera.hpp"
#include "component/transform.hpp"
#include "component/graphic/drawable.hpp"
#include "component/light/point.hpp"
#include "component/light/directional.hpp"
#include "shader/framebuffer.hpp"

namespace game{

	Renderer::Renderer() : System(){
		context_controller_.Initialize();
		glm::ivec2 size = context_controller_.GetWindowSize();
		shader_controller_.Initialize(size.x, size.y);
		Require<Drawable>();
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

		ProcessTextures(node);
		Draw(node.drawable);
	}

	void Renderer::AfterUpdate(){
		shader_controller_.Enable(Program::SSAO);
		shader_controller_.UniformMatrix4fv("projection", camera_controller_.GetProjection());
		shader_controller_.Uniform1i("kernelSize", 1);
		shader_controller_.RenderToScreen();

		//ApplyBlur(Program::SSAO_BLUR, 3.f);

		//shader_controller_.Enable(Program::BLOOM);
		//shader_controller_.RenderToScreen();

		shader_controller_.Enable(Program::LIGHTING);
		shader_controller_.Uniform3f("viewPos", camera_controller_.GetPosition());
		SendLightsToShader();
		shader_controller_.RenderToScreen();
	}

	void Renderer::ProcessLightIfAny(Entity entity){
		if(lights_.size() >= max_lights){ return; }
		PointLight* pl = ecs::GetComponent<PointLight>(entity);
		DirectionalLight* dl = ecs::GetComponent<DirectionalLight>(entity);
		if(pl == nullptr && dl == nullptr){ return; }

		glLight light;

		if(pl){
			Transform* t = ecs::GetComponent<Transform>(entity);
			light.intensity = pl->power;
			light.vector = t->position;
			light.color = pl->color;
			light.type = LightType::POINT;
		}else if(dl){
			light.intensity = dl->power;
			light.vector = dl->direction;
			light.color = dl->color;
			light.type = LightType::DIRECTIONAL;
		}
		lights_.push_back(light);
	}

	void Renderer::SendLightsToShader(){
		std::vector<float> power;
		std::vector<glm::vec3> vec;
		std::vector<glm::vec3> col;
		std::vector<int> type;

		for(glLight light : lights_){
			int t = (int)light.type;
			type.push_back(t);
			power.push_back(light.intensity);
			if(t == 0){
				vec.push_back(glm::vec3(camera_controller_.GetView() * glm::vec4(light.vector, 1.0)));
			} else {
				vec.push_back(glm::vec3(camera_controller_.GetView() * glm::vec4(-light.vector, 0.0)));
			}
			col.push_back(light.color);
		}

		shader_controller_.Uniform1fv("lightsIntensity", power.size(), &power[0]);
		shader_controller_.Uniform3fv("lightsVec", vec.size(), &vec[0].x);
		shader_controller_.Uniform3fv("lightsCol", col.size(), &col[0].x);
		shader_controller_.Uniform1iv("lightsType", type.size(), &type[0]);

		lights_.clear();
	}

	void Renderer::ProcessTextures(RenderComponent node){
		glm::vec2 tex_ratio = glm::vec2(-1.f, -1.f);
		glm::vec2 tex_shift = glm::vec2(0.f, 0.f);

		Texture* texture = nullptr;
		if(node.atlas){
			texture = node.atlas->current_animation->texture;
		} else if(node.texture){
			texture = node.texture;
		}

		if(texture){
			texture->Bind(GL_TEXTURE0);
			tex_ratio = texture->ratio;
			tex_shift = texture->shift;
		} else {
			glBindTexture(GL_TEXTURE0, 0);
		}

		glm::vec3 local_scale = glm::vec3(1.f, 1.f, 1.f);
		if(node.drawable->type == DrawableType::SPRITE){
			local_scale = texture->local_scale;
		}

		shader_controller_.Uniform2f("TexRatio", tex_ratio.x, tex_ratio.y);
		shader_controller_.Uniform2f("TexShift", tex_shift.x, tex_shift.y);
		shader_controller_.UniformMatrix4fv("Model", GetModelMatrixFor(node.transform, local_scale));
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

	RenderComponent Renderer::GetComponentsFor(Entity entity){
		RenderComponent node;
		node.is_valid = false;
		node.drawable = ecs::GetComponent<Drawable>(entity);

		if(!node.drawable){ return node; }
		if(node.drawable->invisible){ return node; } // Ignore invisible
		if(node.drawable->vao == 0){
			int err = drawable_builder_.UpdateDrawableOf(entity);
			if(err){ return node; }
		}
		node.transform = ecs::GetComponent<Transform>(entity);
		node.texture = ecs::GetComponent<Texture>(entity);
		node.mesh = ecs::GetComponent<Mesh>(entity);
		node.atlas = ecs::GetComponent<Atlas>(entity);
		node.is_valid = true;
		return node;
	}

	void Renderer::ApplyBlur(Program prg, int rad){
		glm::ivec2 size = context_controller_.GetWindowSize();
		shader_controller_.Enable(prg);
		shader_controller_.Uniform4f("dirResRad", glm::vec4(1.f, 0.f, size.x, rad));
		shader_controller_.RenderToScreen();
	}

	GLFWwindow* Renderer::GetWindow(){
		return this->context_controller_.GetWindow();
	}
}
