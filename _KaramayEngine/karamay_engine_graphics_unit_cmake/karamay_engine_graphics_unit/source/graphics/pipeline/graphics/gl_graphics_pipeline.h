#ifndef GRAPHICS_PIPELINE_H
#define GRAPHICS_PIPELINE_H

#include "graphics/glsl/glsl_class.h"
#include "graphics/glsl/glsl_shader.h"
#include "graphics/resource/program/gl_program.h"
#include "graphics/resource/buffers/common_buffer/gl_element_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_uniform_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_shader_storage_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_atomic_counter_buffer.h"
#include "graphics/resource/buffers/Indexed_buffer/gl_transform_feedback_buffer.h"

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
    CLEAR = GL_CLEAR,
    SET = GL_SET,
    COPY = GL_COPY,
    COPY_INVERTED = GL_COPY_INVERTED,
    NOOP = GL_NOOP,
    INVERT = GL_INVERT,
    AND = GL_AND,
    NAND = GL_NAND,
    OR = GL_OR,
    NOR = GL_NOR,
    XOR = GL_XOR,
    EQUIV = GL_EQUIV,
    AND_REVERSE = GL_AND_REVERSE,
    AND_INVERTED = GL_AND_INVERTED,
    OR_REVERSE = GL_OR_REVERSE,
    OR_INVERTED = GL_OR_INVERTED
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

enum class gl_primitive_mode
{

};

/*
 * for dynamical modifying
 * */
struct gl_graphics_pipeline_state
{
    struct gl_vertex_assembly
    {
        struct gl_primitive_restart
        {
            bool enabled;
            bool use_fixed_restart_primitive_index;
            std::uint32_t restart_primitive_index;
        } primitive_restart;
    } vertex_assembly; // organize vertex stream
    struct gl_vertex_processing
    {
        struct gl_post_vertex_processing
        {
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
    struct gl_rasterisation
    {

    } rasterisation; // the stage generate fragments from primitives (points, lines, polygons)
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
            } additional_multisample_fragment_operations;
        } post_fragment_operations;
    } fragment_processing; // process fragments
};

/*
 * descriptor for graphics pipeline construction
 * */
struct gl_graphics_pipeline_descriptor{
    // pipeline state
    std::shared_ptr<gl_graphics_pipeline_state> state;
    // vertex stream which input into program by vertex puller
    std::shared_ptr<gl_vertex_array> attributes;
    // program body
    struct glsl_graphics_pipeline_program{
        // must have impl
        std::shared_ptr<glsl_vertex_shader> vertex_shader;
        // optional stage
        std::shared_ptr<glsl_tessellation_shader> tessellation_shader;
        // optional stage
        std::shared_ptr<glsl_geometry_shader> geometry_shader;
        // must have impl
        std::shared_ptr<glsl_fragment_shader> fragment_shader;

        glsl_graphics_pipeline_program() : 
            vertex_shader(nullptr), tessellation_shader(nullptr), geometry_shader(nullptr), 
            fragment_shader(nullptr) 
        {}
    } program;
    // optional transform feedback 
    std::shared_ptr<gl_transform_feedback> tramsform_feedback;
    // where program final color output
    std::shared_ptr<gl_framebuffer> framebuffer;

    gl_graphics_pipeline_descriptor() : 
        state(nullptr), 
        attributes(nullptr), program(), framebuffer(nullptr)
    {}
};

/*
 * graphics pipeline
 * vertex shader [+ tessellation control shader + tessellation evaluation shader] [+ geometry shader] + fragment shader
 * */
class gl_graphics_pipeline{
public:
    gl_graphics_pipeline() = default;
    gl_graphics_pipeline(const std::shared_ptr<gl_graphics_pipeline_descriptor>& desc)
    {
        try
        {
            if (!_validate_descriptor(desc) || !_construct(desc)) {
                throw std::exception("desc is not validate");
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    gl_graphics_pipeline(const gl_graphics_pipeline&) = delete;
    gl_graphics_pipeline& operator=(const gl_graphics_pipeline&) = delete;

    ~gl_graphics_pipeline() = default;
   
public:

    void enable() noexcept
    {
        if (!_program) return;
        _program->enable();
        _bind_resources();
    }

    void disable() noexcept
    {
        if (!_program) return;
        _unbind_resources();
        _program->disable();
    }

public:

    void draw_arrays(gl_primitive_mode mode, std::int32_t first, std::int32_t count) noexcept
    {
        if(!_program) return;
        glDrawArrays(static_cast<GLenum>(mode), first, count);
    }

    void draw_indices(gl_primitive_mode mode, std::int32_t first, std::int32_t count) noexcept
    {
        if(_program) return;
        glDrawElements(static_cast<GLenum>(mode), first, count, nullptr);
    }

private:

    bool _validate_descriptor(const std::shared_ptr<gl_graphics_pipeline_descriptor>& descriptor)
    {
        if (!descriptor) return false;

        if (!descriptor->program.vertex_shader || !descriptor->program.fragment_shader)
        {
            std::cerr << "graphics pipeline program must have vertex and fragment stage impl." << std::endl;
            return false;
        }

        if (!descriptor->attributes || !descriptor->framebuffer || !descriptor->state)
        {
            std::cerr << "graphics pipeline must have state, attributes and framebuffer." << std::endl;
            return false;
        }
    }

    /*
     * generate shader code
     * create program object, compile shaders and attach them to program
     * pre-link actions:
     * link program
     * query resource state info
     * generate resource
     * */
    bool _construct(const std::shared_ptr<gl_graphics_pipeline_descriptor>& descriptor) noexcept
    {
        if (!descriptor) return false;

        // generate shader code
        // load and complie shaders
        std::vector<std::shared_ptr<glsl_shader>> _glsl_shaders;
        std::vector<std::shared_ptr<gl_shader>> _shaders;

        const auto& _glsl_vs = descriptor->program.vertex_shader;
        if (_glsl_vs)
        {
           
            auto _vs = std::make_shared<gl_shader>(gl_shader_type::VERTEX_SHADER, "");
            _shaders.push_back(_vs);
            _glsl_shaders.push_back(_glsl_vs);
        }

        const auto& _glsl_tess = descriptor->program.tessellation_shader;
        if (_glsl_tess)
        {
            auto _tesc = std::make_shared<gl_shader>(gl_shader_type::TESS_CONTROL_SHADER, "");
            auto _tese = std::make_shared<gl_shader>(gl_shader_type::TESS_EVALUATION_SHADER, "");

            _shaders.push_back(_tesc);
            _shaders.push_back(_tese);
            _glsl_shaders.push_back(_glsl_tess);
        }

        const auto& _glsl_gs = descriptor->program.geometry_shader;
        if (_glsl_gs)
        {
            auto _gs = std::make_shared<gl_shader>(gl_shader_type::GEOMETRY_SHADER, "");

            _shaders.push_back(_gs);
            _glsl_shaders.push_back(_glsl_gs);
        }

        const auto& _glsl_fs = descriptor->program.fragment_shader;
        if (_glsl_fs)
        {
            auto _fs = std::make_shared<gl_shader>(gl_shader_type::FRAGMENT_SHADER, "");
            _shaders.push_back(_fs);
            _glsl_shaders.push_back(_glsl_fs);
        }

        // construct shader program
        _program = std::make_unique<gl_program>();
        if (!_program) return false;
        _program->construct(_shaders);

        // query state settings and generate settings cache
       // _program->get_resource();
        std::uint32_t _index = 0;
        _program->get_resource_index(gl_program_interface::ATOMIC_COUNTER_BUFFER, "test", _index);
        
        // generate resources
        {
            // collect uniform blocks and generate uniform buffer
            std::vector<std::shared_ptr<glsl_uniform_block_t>> _uniform_blocks;
            for (const auto& _glsl_shader : _glsl_shaders)
            {
                
            }

            if (_uniform_blocks.size() != 0)
            {
                _uniform_buffer = std::make_unique<gl_uniform_buffer>(gl_uniform_buffer_descriptor{ _uniform_blocks });
            }

            // collect shader storage blocks and generate shader storage buffer
            std::vector<std::shared_ptr<glsl_shader_storage_block_t>> _shader_storage_blocks;
            if (_shader_storage_blocks.size() != 0)
            {
                _shader_storage_buffer = std::make_unique<gl_shader_storage_buffer>(gl_shader_storage_buffer_descriptor{ _shader_storage_blocks });
            }

            // collect atomic counters and genrate atomic counter buffer
            std::vector<std::shared_ptr<glsl_atomic_counter_t>> _atomic_counters;
            if (_atomic_counters.size() != 0)
            {
                _atomic_counter_buffer = std::make_unique<gl_atomic_counter_buffer>(gl_atomic_counter_buffer_descriptor{ _atomic_counters });
            }
        }

    }

private:

    std::unique_ptr<gl_program> _program;

    std::shared_ptr<const gl_graphics_pipeline_descriptor> _descriptor;

    struct gl_graphics_pipeline_resource_pool{

        std::unique_ptr<gl_uniform_buffer> uniform_buffer;
        std::unique_ptr<gl_shader_storage_buffer> shader_storage_buffer;
        std::unique_ptr<gl_atomic_counter_buffer> atomic_counter_buffer;
        
        std::vector<std::shared_ptr<glsl_sampler_t>> _samplers;
        std::vector<std::shared_ptr<glsl_image_t>> _images;
        
        std::shared_ptr<gl_transform_feedback> transform_feedback;

        std::shared_ptr<gl_framebuffer> framebuffer;

    } _resource_pool;

    std::unique_ptr<gl_uniform_buffer> _uniform_buffer;
    std::unique_ptr<gl_shader_storage_buffer> _shader_storage_buffer;
    std::unique_ptr<gl_atomic_counter_buffer> _atomic_counter_buffer;
 

private:

    void _bind_resources()
    {
        if(_uniform_buffer)
        {
            _uniform_buffer->bind();
        }
        if(_shader_storage_buffer)
        {
            _shader_storage_buffer->bind();
        }
        if(_atomic_counter_buffer)
        {
            _atomic_counter_buffer->bind();
        }
    }

    void _unbind_resources()
    {

    }

    void flush_resources()
    {
        GLint MaxVertexAtomicCounterBuffers(0);
        GLint MaxControlAtomicCounterBuffers(0);
        GLint MaxEvaluationAtomicCounterBuffers(0);
        GLint MaxGeometryAtomicCounterBuffers(0);
        GLint MaxFragmentAtomicCounterBuffers(0);
        GLint MaxCombinedAtomicCounterBuffers(0);

        glGetIntegerv(GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS, &MaxVertexAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS, &MaxControlAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS, &MaxEvaluationAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS, &MaxGeometryAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS, &MaxFragmentAtomicCounterBuffers);
        glGetIntegerv(GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS, &MaxCombinedAtomicCounterBuffers);
    }

    void _update_pipeline_state()
    {
        // vertex specification
        {
            glEnable(GL_PRIMITIVE_RESTART);
            glPrimitiveRestartIndex(0);
            // or
            glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);// 2^N - 1
        }

        // vertex process
        {
            //shading

            // flatshading
            glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

            // clipping
            glEnable(GL_CLIP_DISTANCE0); // [0, GL_MAX_CLIP_DISTANCES-1]
            glClipControl(GL_LOWER_LEFT, GL_NEGATIVE_ONE_TO_ONE);
            // glEnable(GL_DEPTH_CLAMP);
            glDepthRange(1.0l, 1.1l);
            //glDepthRangeArrayv();
            //glDepthRangef();
//            glViewport();
//            glDepthRangeIndexed();
//            glViewportArrayv();
//            glViewportIndexedf();
//            glViewportIndexedfv();


        }

        // primitive assmebly
        {

        }
        // rasterization
        {
            // 到达光栅化之前抛弃所有图元, 使得光栅化包括光栅化之后的阶段全部失效
            if (true)
                glEnable(GL_RASTERIZER_DISCARD);
            else
                glDisable(GL_RASTERIZER_DISCARD);

            // multisampling
            glEnable(GL_MULTISAMPLE);
            glEnable(GL_SAMPLE_SHADING);
//            glMinSampleShading();
//            glGetMultisamplefv();

            // points
            glEnable(GL_PROGRAM_POINT_SIZE);
            glDisable(GL_PROGRAM_POINT_SIZE);
            glPointSize(0);
//            glPointParameteri();
//            glPointParameteriv();
//            glPointParameterf();
//            glPointParameterfv();

            // line segments
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(1.0f);

            // polygons
            glEnable(GL_POLYGON_SMOOTH);

            glEnable(GL_CULL_FACE);
            glFrontFace(GL_CCW);
            glCullFace(GL_FRONT_AND_BACK);

            // polygon rast & depth offset
            glEnable(GL_POLYGON_OFFSET_FILL);
            glEnable(GL_POLYGON_OFFSET_LINE);
            glEnable(GL_POLYGON_OFFSET_POINT);
            glEnable(GL_POLYGON_SMOOTH);
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            //glPolygonOffsetClamp();
            glPolygonOffset(1.2f, 0);

        }

        // pre frag operations
        {

            // scissor test
            glEnable(GL_SCISSOR_TEST);
            glDisable(GL_SCISSOR_TEST);

            glEnablei(GL_SCISSOR_TEST, 0);
            glDisablei(GL_SCISSOR_TEST, 0);
            glScissor(0, 0, 0, 0);
            glScissorArrayv(0, 100, nullptr);
            //glScissorIndexed();
            //glScissorIndexedv();

            // multisample fragment ops

        }

        // fragment shading
        {

        }

        glEnable(GL_SAMPLE_COVERAGE);

        // alpha to coverage
        {
            glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
            glEnable(GL_SAMPLE_ALPHA_TO_ONE); // or
        }
        // Stencil test
        {
            // do stencil test and update the stencil buffer
            glEnable(GL_STENCIL_TEST);
            gl_stencil_func _stencil_func;
            glStencilFunc(_stencil_func, 0, 1); // set front-face and back-face function and
            glStencilFuncSeparate(static_cast<GLenum>(_stencil_func), static_cast<GLenum>(_stencil_func), 0, 1);

            gl_stencil_op _stencil_op;
            // stencil test fail , stencil stencil test pass but depth test fail, both pass
            glStencilOpSeparate(GL_FRONT, _stencil_op, _stencil_op, _stencil_op);
            glStencilOpSeparate(GL_BACK, _stencil_op, _stencil_op, _stencil_op);
            glStencilOpSeparate(GL_FRONT_AND_BACK, _stencil_op, _stencil_op, _stencil_op);
            //glStencilOp(_stencil_op, _stencil_op, _stencil_op);
            glStencilMaskSeparate(GL_FRONT, 1);
            glStencilMaskSeparate(GL_BACK, 1);
            glStencilMaskSeparate(GL_FRONT_AND_BACK, 1);
            //glStencilMask(1);
        }
        // Depth test
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(df_never);
        }
        // occlusion queries
        {

        }
        // blending
        {
            glEnable(GL_BLEND);
//            glBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
//            glBlendFunc();
//            glBlendFuncSeparate();
//            glBlendFunci();
//            glBlendFuncSeparatei();
//            glBlendEquation();
//            glBlendEquationi();
//            glBlendEquationSeparate();
//            glBlendEquationSeparatei();
        }
        // sRGB Conversion
        {
            glEnable(GL_FRAMEBUFFER_SRGB);

        }
        //Dithering
        {
            glEnable(GL_DITHER);
        }
        // color logic operations
        {

            gl_logic_op _logic_op;
            glEnable(GL_COLOR_LOGIC_OP);
            glDisable(GL_COLOR_LOGIC_OP);
            glLogicOp(static_cast<GLenum>(_logic_op));
        }
        // additional multisample fragment operations
        {
            glEnable(GL_MULTISAMPLE);
            //glSampleCoverage();
        }

        glEnable(GL_SAMPLE_MASK);
        //glSampleMaski();

        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    }

    bool _check_shader_ext(const std::string& path, const std::string& ext)
    {
        return path.substr(path.find_first_of('.')) == ext;
    }

};


class gl_vertex_processing_pipeline_descriptor
{
    std::shared_ptr<glsl_vertex_shader> vertex_shader;
    std::shared_ptr<glsl_tessellation_shader> tessellation_shader;
    std::shared_ptr<glsl_geometry_shader> geometry_shader;
};

/*
 * vertex processing pipeline, optimized for vertex processing.
 * fetch data from transform feedback buffer, after vertex processing, all primitives will be discard.
 * vertex shader [+ tessellation control shader + tessellation evaluation shader] [+geometry shader]
 * */
class gl_vertex_processing_pipeline{
public:
    gl_vertex_processing_pipeline() = default;
    gl_vertex_processing_pipeline(const gl_vertex_processing_pipeline&) = delete;
    gl_vertex_processing_pipeline& operator=(const gl_vertex_processing_pipeline&) = delete;

    ~gl_vertex_processing_pipeline() = default;

public:

    void construct(const gl_vertex_processing_pipeline_descriptor& descriptor){}

};



#define DEFINE_GRAPHICS_PIPELINE_PARAMETERS(PIPELINE_NAME)\
struct gl_##PIPELINE_NAME##_graphics_pipeline_parameters : public gl_graphics_pipeline_parameters\

#define CLASS_NAME(__CLASS__)  #__CLASS__



#define DEFINE_PROGRAM_PARAMETER_IMAGE(GLSL_IMAGE_T, V_NAME) \
glsl_##GLSL_IMAGE_T V_NAME{CLASS_NAME(V_NAME)};\

#define DEFINE_PROGRAM_PARAMETER_SAMPLER(GLSL_SAMPLER_T, V_NAME)\
glsl_##GLSL_SAMPLER_T V_NAME;\


#define DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER(V_NAME)\
glsl_atomic_uint V_NAME;\

#define DEFINE_PROGRAM_PARAMETER_ATOMIC_COUNTER_ARRAY(V_NAME, ARRAY_SIZE)\
glsl_atomic_uint V_NAME[ARRAY_SIZE];\

#define DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK(GLSL_UNIFORM_BLOCK_T, V_NAME)\
GLSL_UNIFORM_BLOCK_T V_NAME;

#define DEFINE_PROGRAM_PARAMETER_UNIFORM_BLOCK_ARRAY(GLSL_UNIFORM_BLOCK_T, V_NAME, ARRAY_SIZE)\
GLSL_UNIFORM_BLOCK_T V_NAME[ARRAY_SIZE];\

#define DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK(GLSL_SHADER_STORAGE_BLOCK_T, V_NAME)\
GLSL_SHADER_STORAGE_BLOCK_T V_NAME; \

#define DEFINE_PROGRAM_PARAMETER_SHADER_STORAGE_BLOCK_ARRAY(GLSL_SHADER_STORAGE_BLOCK_T, V_NAME, ARRAY_SIZE)\
GLSL_SHADER_STORAGE_BLOCK_T V_NAME[ARRAY_SIZE];\


// Shader Parameters Definition
#define SHADER_PARAMETER_REF(TOKEN_NAME)\

#define INPUT_STREAM() \

#define OUTPUT_STREAM() \

#define DEFINE_VERTEX_SHADER_PARAMETERS_BEGIN()
#define DEFINE_VERTEX_SHADER_PARAMETERS_END()

#define DEFINE_TESC_SHADER_PARAMETERS_BEGIN()
#define DEFINE_TESC_SHADER_PARAMETERS_END()

#define DEFINE_TESE_SHADER_PARAMETERS_BEGIN()
#define DEFINE_TESE_SHADER_PARAMETERS_END()

#define DEFINE_GEOMETRY_SHADER_PARAMETERS_BEGIN()
#define DEFINE_GEOMETRY_SHADER_PARAMETERS_END()

#define DEFINE_FRAGMENT_SHADER_PARAMETERS_BEGIN()
#define DEFINE_FRAGMENT_SHADER_PARAMETERS_END()


// Shader Stream Definition
#define DEFINE_STREAM_INPUT_BEGIN()
#define DEFINE_STREAM_INPUT_END()
#define DEFINE_VERTEX_FRAGMENT_STREAM_BEGIN()
#define DEFINE_VERTEX_FRAGMENT_STREAM_END()
#define DEFINE_VERTEX_TESC_STREAM_BEGIN()
#define DEFINE_VERTEX_TESC_STREAM_END()
#define DEFINE_VERTEX_GEOMETRY_STREAM_BEGIN()
#define DEFINE_VERTEX_GEOMETRY_STREAM_END()
#define DEFINE_TESC_TESE_STREAM_BEGIN()
#define DEFINE_TESC_TESE_STREAM_END()
#define DEFINE_TESE_GEOMETRY_STREAM_BEGIN()
#define DEFINE_TESE_GEOMETRY_STREAM_END()
#define DEFINE_TESE_FRAGMENT_STREAM_BEGIN()
#define DEFINE_TESE_FRAGMENT_STREAM_END()
#define DEFINE_GEOMETRY_FRAGMENT_STREAM_BEGIN()
#define DEFINE_GEOMETRY_FRAGMENT_STREAM_END()
#define DEFINE_STREAM_OUTPUT_BEGIN()
#define DEFINE_STREAM_OUTPUT_END()

#endif

