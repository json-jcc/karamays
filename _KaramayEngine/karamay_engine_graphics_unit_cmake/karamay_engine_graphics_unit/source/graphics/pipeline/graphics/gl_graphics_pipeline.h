#ifndef H_GRAPHICS_PIPELINE
#define H_GRAPHICS_PIPELINE

#include "graphics/pipeline/base/gl_pipeline.h"

class gl_vertex_shader;
class gl_fragment_shader;
class gl_geometry_shader;
class gl_tessellation_control_shader;
class gl_tessellation_evaluation_shader;

enum gl_stencil_op : GLenum
{
	so_keep = GL_KEEP, // keep current val
	so_zero = GL_ZERO, // set val to 0
	so_replace = GL_REPLACE, //set val to ref specified by glStencilFunc
	so_incr = GL_INCR, // 
	so_incr_wrap = GL_INCR_WRAP,
	so_decr = GL_DECR,
	so_decr_wrap = GL_DECR_WRAP,
	so_invert = GL_INVERT
};

enum gl_stencil_func : GLenum
{
	sf_never = GL_NEVER,
	sf_always = GL_ALWAYS,
	sf_less = GL_LESS,
	sf_less_equal = GL_LEQUAL,
	sf_greater = GL_GREATER,
	sf_greater_equal = GL_GEQUAL,
	sf_equal = GL_EQUAL,
	sf_not_equeal = GL_NOTEQUAL
};

enum class gl_logic_op : GLenum
{
    clear = GL_CLEAR,
    set = GL_SET,
    copy = GL_COPY,
    copy_inverted = GL_COPY_INVERTED,
    noop = GL_NOOP,
    invert = GL_INVERT,
    and = GL_AND,
    nand = GL_NAND,
    or = GL_OR,
    nor = GL_NOR,
    xor = GL_XOR,
    equiv = GL_EQUIV,
    and_reverse = GL_AND_REVERSE,
    and_inverted = GL_AND_INVERTED,
    or_reverse = GL_OR_REVERSE,
    or_inverted = GL_OR_INVERTED
};

enum gl_depth_func : GLenum
{
    df_never = GL_NEVER,
    df_less = GL_LESS,
    df_equeal = GL_EQUAL,
    df_less_equal = GL_LEQUAL,
    df_greater = GL_GREATER,
    df_not_equal = GL_NOTEQUAL,
    df_greater_equal = GL_GEQUAL,
    df_always = GL_ALWAYS
};

enum gl_provoke_mode : GLenum
{
    first_vertex_convention = GL_FIRST_VERTEX_CONVENTION,
    last_vertex_convention = GL_LAST_VERTEX_CONVENTION
};

enum gl_clip_control_origin : GLenum
{
    lower_left = GL_LOWER_LEFT,
    upper_left = GL_UPPER_LEFT
};

enum gl_clip_control_depth_mode : GLenum
{
    negative_one_to_one = GL_NEGATIVE_ONE_TO_ONE,
    zero_to_one = GL_ZERO_TO_ONE
};

// ����װ�䣬 ���㴦����ͼԪװ�䣬��դ����Ƭ�δ��������FB
struct gl_graphics_pipeline_descriptor
{
    struct gl_vertex_assembly
    {
       struct gl_vertex_specification{} vertex_specification;
       struct gl_primitive_restart
        {
            bool enabled;
            bool use_fixed_restart_primitive_index;
            std::uint32_t restart_primitive_index;
        } primitive_restart;
    } vertex_assembly; // organize vetex stream
    struct gl_vertex_processing
    {
        struct gl_vertex_shading
        {
            bool enabled;
            std::string vertex_shader_path;
        }vertex_shading;
        struct gl_tessellation
        {
            bool enabled;
            std::string tessellation_control_shader_path;
            std::string tessellation_evaluation_shader_path;
        } tessellation;
        struct gl_geometry_shading
        {
            bool enabled;
            std::string geometry_shader_path;
        } geometry_shading;
		struct gl_post_vertex_processing
		{
			struct gl_transform_feedback
			{
				
				std::string semantic_name;
			} transform_feedback;
            struct gl_flatshading
            {
                gl_provoke_mode provoke_mode;
            } flatshading;
			struct gl_primitive_clipping
			{
                std::uint32_t clip_plane_index{0};
                gl_clip_control_origin clip_control_origin{ gl_clip_control_origin::lower_left };
                gl_clip_control_depth_mode clip_control_depth_mode{};
                // 0, 1
                std::double_t near_clipping_distance, far_clipping_distance;
			} primitive_clipping;
			struct gl_coordinate_transformations
			{
                std::int32_t viewport_x, viewport_y;
                std::uint32_t viewport_width, viewport_height; // glViewport
			} coordinate_transformations;
		} post_vertex_processing;
    } vertex_processing; // vertex shading, tessellation, geometry shading, transform feedback, clipping, coordinates transformation
    struct gl_primitive_assembly 
    {
        bool discard_all_primitives; // discard all primitives, if true the pipeline wont go head
    } primitive_assembly; // collect primitives or discard all of them
    struct gl_rasterization
    {
        
    } rasterization; // the stage generate fragments from primitives (points, lines, polygons)
    struct gl_fragment_processing
    {
        /*
        * Once fragments are produced by rasterization, a number of per-fragment operations
        * are performed prior to fragment shader execution.
        * If a fragment is discarded during any of these operations, it will not be processed by any subsequent stage,
        * including fragment shader execution.
        * Three fragment operations are performed,
        * and a further three are optionally performed on each fragment.
        * (stencil_test, depth_test, occlusion_queries after fragment shading)
        * (which need to specify "early_fragment_tests layout" Qualifier in fs)
        */
        struct gl_pre_fragment_operations
        {
            struct gl_pixel_ownship_test {} pixel_ownship_test;
            struct gl_scissor_test
            {
                bool enabled;
            } scissor_test;
            struct gl_multisample_fragment_operations {} multisample_fragment_operations;
        } pre_fragment_operations;
        struct gl_fragment_shading
        {
            bool enabled;
            std::string fragment_shader_path;
        } fragment_shading;
        struct gl_post_fragment_operations
        {
            struct gl_alpha_to_coverage
            {
                bool enabled;

            } alpha_to_coverage;
            struct gl_advanceable_operations
            {
                struct gl_stencil_test
                {
                    bool enabled;
                    gl_stencil_func front_face_func;
                    gl_stencil_func back_face_func;
                    gl_stencil_op front_face_op;
                    gl_stencil_op back_face_op;
                } stencil_test; // can be advanced before fragment shading
                struct gl_depth_test
                {
                    bool enabled;
                    gl_depth_func func;
                    bool clamp_enabled;
                    std::double_t near_val, far_val;
                } depth_test; // can be advanced before fragment shading
                struct gl_occlusion_queries
                {

                } occlusion_queries; // can be advanced before fragment shading
                bool advanced;
            } advanceable_operations;
            struct gl_blending
            {

            } blending;
            struct gl_srgb_conversion
            {

            } srgb_conversion;
            struct gl_dithering
            {
                bool enabled;
            } dithering;
            struct gl_logical_operation
            {
                bool enabled;
                gl_logic_op op;
            } logical_operation;
            struct gl_addtional_multisample_fragment_operations
            {
                bool enabled;
                std::float_t sample_coverage_value;
                bool inverted;
            } addtional_multisample_fragment_operations;
        } post_fragment_operations;
    } fragment_processing; // process fragments
    struct gl_framebuffer
    {
        bool custom_enabled;
        struct gl_custom_framebuffer
        {

        } custom_framebuffer;
        struct gl_default_framebuffer
        {} default_framebuffer;
    } framebuffer;
};

class gl_graphics_pipeline : public gl_pipeline
{
private:

    gl_graphics_pipeline() = default;

public:
    
    explicit gl_graphics_pipeline(const gl_graphics_pipeline_descriptor& descriptor) :
        _descriptor(descriptor)
    {
        _initialize_graphics_pipeline();
    }

    ~gl_graphics_pipeline() = default;


public:

    bool initialize() override;

public:

    void set_primitive_clipping(gl_clip_control_origin origin, gl_clip_control_depth_mode depth_mode)
    {
        _descriptor.vertex_processing.post_vertex_processing.primitive_clipping.clip_control_origin = origin;
        _descriptor.vertex_processing.post_vertex_processing.primitive_clipping.clip_control_depth_mode = depth_mode;
    }

    void set_viewport(std::int32_t x, std::int32_t y, std::uint32_t width, std::uint32_t height)
    {
        _descriptor.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_x = x;
        _descriptor.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_y = y;
        _descriptor.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_width = width;
        _descriptor.vertex_processing.post_vertex_processing.coordinate_transformations.viewport_height = height;
    }

public:

    inline void draw_points(std::int32_t first, std::uint32_t count)
    {
        glDrawArrays(GL_POINTS, 0, 100);
    }

    inline void draw_lines() {}

    inline void draw_triangles() {}

    inline void draw_triangle_strips() {}

    inline void draw_rectangles() {}

private:
    
    gl_graphics_pipeline_descriptor _descriptor;

    std::shared_ptr<gl_program> _program;

    bool _check_shader_ext(const std::string& path, const std::string& ext)
    {
        return path.substr(path.find_first_of('.')) == ext;
    }

    void _initialize_graphics_pipeline();

    void _install();

    void _uninstall();

};

#endif
