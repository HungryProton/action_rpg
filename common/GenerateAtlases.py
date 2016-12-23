import bpy

class TextureAtlasOperator(bpy.types.Operator):
    bl_label = "Generate all atlases"
    bl_idname = "ta.generator"
    bl_description = "Generate all atlases"
 
    def execute(self, context):
        self.report({'INFO'}, "Generating sprites")
        return {'FINISHED'}
 
def register():
    bpy.utils.register_module(__name__)
 
def unregister():
    bpy.utils.unregister_module(__name__)
 
if __name__ == "__main__":
    register()