#pragma once
#include "gl_renderer.h"
#include "graphics/pipeline/gl_pipeline_base.h"
#include "graphics/commands/gl_commands.h"
#include "graphics/mesh/gl_mesh.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"
#include "graphics/buffer/customization/gl_uniform_buffer.h"
#include "graphics/buffer/customization/gl_shader_storage_buffer.h"
#include "graphics/buffer/customization/gl_atomic_counter_buffer.h"




#define ctt(CLASSNAME)\
std::make_shared<CLASSNAME>()

#define add_pip(PIPName)\
_pipelines_map.emplace("pipeline0", std::make_shared<gl_pipeline_base>()).first->second\

#define find_pip(PIPName)\
_pipelines_map.find(PIPName)->second


#define add_fb(FB_NAME)\
_framebuffers_map.emplace(FB_NAME, std::make_shared<gl_framebuffer>())\

#define find_fb(FB_NAME)\
_framebuffers_map.find(FB_NAME)->second\

#define graphics_pipeline(NAME)\
find_pipeline(NAME)\


class gl_pbr_std_renderer : public gl_renderer
{
private:

	std::shared_ptr< gl_mesh> _mesh;

	std::float_t _view_field;
	std::float_t _view_distance;
	std::float_t _width, height;

	glm::mat4 get_projection_matrix()
	{
		return glm::perspective(glm::radians(_view_field), (float)_width / (float)-height, 0.1f, _view_distance);
	}

public:
	
	gl_pipeline_base& find_pipeline(const std::string name)
	{
		return *_pipelines_map.find(name)->second;
	}


	virtual void construct() override
	{
		
		auto vao = std::make_shared<gl_vertex_array>();
		vao->fill(nullptr, 1024, 
			{ 
				{0, 100, GL_UNSIGNALED, 0}, 
				{1, 100, GL_UNSIGNALED, 100} 
			});



		auto ebo = std::make_shared<gl_element_array_buffer>();
		ebo->fill(nullptr, 100);


		auto ubo0 = std::make_shared<gl_uniform_buffer>();
		
		auto uniform_color = std::make_shared<gl_uniform<glm::vec4>>();


		auto ubo1 = std::make_shared<gl_uniform_buffer>();
		auto ubo2 = std::make_shared<gl_uniform_buffer>();

		auto sso0 = std::make_shared<gl_shader_storage_buffer>();
		auto sso1 = std::make_shared<gl_shader_storage_buffer>();

		auto aco = std::make_shared<gl_atomic_counter_buffer>();
		aco->fill({ "ato_red", "ato_green", "ato_blue" });

		auto transfo = std::make_shared<gl_transform_feedback>();

		int first = 10;
		int count = 100;
		

		graphics_pipeline("pbr_mesh_pip")
		.construct(
			{ 
				"shaders/pbr_mesh.vert", 
				"shaders/pbr_mesh.tesc", "shaders/pbr_mesh.tese", "shaders/pbr_mesh.geom", 
				"shaders/pbr_mesh.frag" 
			})
		.set_vertex_array(vao)
		.set_element_array(ebo)
		.set_transform_feedback(transfo)
		.add_uniforms({uniform_color})
		.add_uniform_buffers({ ubo0, ubo1, ubo2 })
		.add_shader_storage_buffers({ sso0, sso1 })
		.add_atomic_counter_buffers({ aco })
		.set_framebuffer()
		.set_commands([&first, &count]()
		{
			glDrawArrays(GL_TRIANGLES, first, count);
		});

	}

	virtual void render(std::float_t delta_time) final override
	{
		for (auto pair : _pipelines_map)
		{
			if (auto pipeline = pair.second)
			{
				pipeline->render(delta_time);
			}
		}
	}

};
