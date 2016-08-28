#include "drawable_builder.hpp"
#include "ecs/ecs.hpp"
#include "service/geometry_helper.hpp"
#include "service/service.hpp"
#include "component/texture.hpp"
#include "component/mesh.hpp"

namespace game{

	DrawableBuilder::DrawableBuilder(){ }

	DrawableBuilder::~DrawableBuilder(){ }

	int DrawableBuilder::UpdateDrawableOf(Entity entity){
		Drawable* drawable = ecs::GetComponent<Drawable>(entity);
		if(drawable == nullptr){ return 1; }

		switch(drawable->type){
			case DrawableType::SPRITE:
				return UpdateSpriteDrawable(drawable, entity);
			case DrawableType::MESH:
				return UpdateMeshDrawable(drawable, entity);
			case DrawableType::NONE:
			default:
				return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	int DrawableBuilder::UpdateSpriteDrawable(Drawable* drawable,
																						Entity entity){
		Texture* texture = ecs::GetComponent<Texture>(entity);
		if(!texture){ return EXIT_FAILURE; }	// Fail if no texture found

		GeometryHelper* geometry_helper = Service::Get<GeometryHelper>();
		geometry_helper->MakeDrawableUseBoxBuffer(drawable);
		return EXIT_SUCCESS;
	}

	int DrawableBuilder::UpdateMeshDrawable(Drawable* drawable,
																					Entity entity){
		Mesh* mesh = ecs::GetComponent<Mesh>(entity);
		if(!mesh){ return EXIT_FAILURE; }	 // Fail if no mesh found

		GeometryHelper* geometry_helper = Service::Get<GeometryHelper>();
		geometry_helper->MakeDrawableUseMeshBuffer(mesh, drawable);
		return EXIT_SUCCESS;
	}
}
