#ifndef GLSL_CLASS_H
#define GLSL_CLASS_H

#include "public/stl.h"
#include "public/glm.h"
#include "public/_glew.h"

enum class gl_uniform_type : GLenum
{
    FLOAT = GL_FLOAT,	//float
    FLOAT_VEC2 = GL_FLOAT_VEC2,	//vec2
    FLOAT_VEC3 = GL_FLOAT_VEC3,	//vec3
    FLOAT_VEC4 = GL_FLOAT_VEC4,	//vec4
    DOUBLE = GL_DOUBLE,	//double
    DOUBLE_VEC2 = GL_DOUBLE_VEC2,	//dvec2
    DOUBLE_VEC3 = GL_DOUBLE_VEC3,	//dvec3
    DOUBLE_VEC4 = GL_DOUBLE_VEC4,	//dvec4
    INT = GL_INT,	//int
    INT_VEC2 = GL_INT_VEC2,	//ivec2
    INT_VEC3 = GL_INT_VEC3,	//ivec3
    INT_VEC4 = GL_INT_VEC4,	//ivec4
    UNSIGNED_INT = GL_UNSIGNED_INT,	//unsigned int
    UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,	//uvec2
    UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,	//uvec3
    UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,	//uvec4
    BOOL = GL_BOOL,	//bool
    BOOL_VEC2 = GL_BOOL_VEC2,	//bvec2
    BOOL_VEC3 = GL_BOOL_VEC3,	//bvec3
    BOOL_VEC4 = GL_BOOL_VEC4,	//bvec4
    FLOAT_MAT2 = GL_FLOAT_MAT2,	//mat2
    FLOAT_MAT3 = GL_FLOAT_MAT3,	//mat3
    FLOAT_MAT4 = GL_FLOAT_MAT4,	// mat4
    FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,	//mat2x3
    FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,	//mat2x4
    FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,	//mat3x2
    FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,	//mat3x4
    FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,	//mat4x2
    FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,	//mat4x3
    DOUBLE_MAT2 = GL_DOUBLE_MAT2,	//dmat2
    DOUBLE_MAT3 = GL_DOUBLE_MAT3,	//dmat3
    DOUBLE_MAT4 = GL_DOUBLE_MAT4,	//dmat4
    DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,	//dmat2x3
    DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,	//dmat2x4
    DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,	//dmat3x2
    DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,	//dmat3x4
    DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,	//dmat4x2
    DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3,	//dmat4x3
    SAMPLER_1D = GL_SAMPLER_1D,	//sampler1D
    SAMPLER_2D = GL_SAMPLER_2D,	//sampler2D
    SAMPLER_3D = GL_SAMPLER_3D,	//sampler3D
    SAMPLER_CUBE = GL_SAMPLER_CUBE,	//samplerCube
    SAMPLER_1D_SHADOW = GL_SAMPLER_1D_SHADOW,	//sampler1DShadow
    SAMPLER_2D_SHADOW = GL_SAMPLER_2D_SHADOW,	//sampler2DShadow
    SAMPLER_1D_ARRAY = GL_SAMPLER_1D_ARRAY,	//sampler1DArray
    SAMPLER_2D_ARRAY = GL_SAMPLER_2D_ARRAY,	//sampler2DArray
    SAMPLER_1D_ARRAY_SHADOW = GL_SAMPLER_1D_ARRAY_SHADOW,	//sampler1DArrayShadow
    SAMPLER_2D_ARRAY_SHADOW = GL_SAMPLER_2D_ARRAY_SHADOW,	//sampler2DArrayShadow
    SAMPLER_2D_MULTISAMPLE = GL_SAMPLER_2D_MULTISAMPLE, //sampler2DMS
    SAMPLER_2D_MULTISAMPLE_ARRAY = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,	//sampler2DMSArray
    SAMPLER_CUBE_SHADOW = GL_SAMPLER_CUBE_SHADOW,	//samplerCubeShadow
    SAMPLER_BUFFER = GL_SAMPLER_BUFFER,	//samplerBuffer
    SAMPLER_2D_RECT = GL_SAMPLER_2D_RECT,	//sampler2DRect
    SAMPLER_2D_RECT_SHADOW = GL_SAMPLER_2D_RECT_SHADOW,	//sampler2DRectShadow
    INT_SAMPLER_1D = GL_INT_SAMPLER_1D,	//isampler1D
    INT_SAMPLER_2D = GL_INT_SAMPLER_2D,	//isampler2D
    INT_SAMPLER_3D = GL_INT_SAMPLER_3D,	//isampler3D
    INT_SAMPLER_CUBE = GL_INT_SAMPLER_CUBE,	//isamplerCube
    INT_SAMPLER_1D_ARRAY = GL_INT_SAMPLER_1D_ARRAY,	//isampler1DArray
    INT_SAMPLER_2D_ARRAY = GL_INT_SAMPLER_2D_ARRAY,	//isampler2DArray
    INT_SAMPLER_2D_MULTISAMPLE = GL_INT_SAMPLER_2D_MULTISAMPLE,	//isampler2DMS
    INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,	//isampler2DMSArray
    INT_SAMPLER_BUFFER = GL_INT_SAMPLER_BUFFER,	//isamplerBuffer
    INT_SAMPLER_2D_RECT = GL_INT_SAMPLER_2D_RECT,	//isampler2DRect
    UNSIGNED_INT_SAMPLER_1D = GL_UNSIGNED_INT_SAMPLER_1D,	//usampler1D
    UNSIGNED_INT_SAMPLER_2D = GL_UNSIGNED_INT_SAMPLER_2D,	//usampler2D
    UNSIGNED_INT_SAMPLER_3D = GL_UNSIGNED_INT_SAMPLER_3D,	//usampler3D
    UNSIGNED_INT_SAMPLER_CUBE = GL_UNSIGNED_INT_SAMPLER_CUBE,	//usamplerCube
    UNSIGNED_INT_SAMPLER_1D_ARRAY = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,	//usampler2DArray
    UNSIGNED_INT_SAMPLER_2D_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,	//usampler2DArray
    UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,	//usampler2DMS
    UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,	//usampler2DMSArray
    UNSIGNED_INT_SAMPLER_BUFFER = GL_UNSIGNED_INT_SAMPLER_BUFFER,	//usamplerBuffer
    UNSIGNED_INT_SAMPLER_2D_RECT = GL_UNSIGNED_INT_SAMPLER_2D_RECT,	//usampler2DRect
    IMAGE_1D = GL_IMAGE_1D,	//image1D
    IMAGE_2D = GL_IMAGE_2D,	//image2D
    IMAGE_3D = GL_IMAGE_3D,	//image3D
    MAGE_2D_RECT = GL_IMAGE_2D_RECT,	//image2DRect
    MAGE_CUBE = GL_IMAGE_CUBE,	//imageCube
    MAGE_BUFFER = GL_IMAGE_BUFFER,	//imageBuffer
    MAGE_1D_ARRAY = GL_IMAGE_1D_ARRAY,	//image1DArray
    MAGE_2D_ARRAY = GL_IMAGE_2D_ARRAY,	//image2DArray
    IMAGE_2D_MULTISAMPLE = GL_IMAGE_2D_MULTISAMPLE,	//image2DMS
    IMAGE_2D_MULTISAMPLE_ARRAY = GL_IMAGE_2D_MULTISAMPLE_ARRAY,	//image2DMSArray
    INT_IMAGE_1D = GL_INT_IMAGE_1D,	//iimage1D
    INT_IMAGE_2D = GL_INT_IMAGE_2D,	//iimage2D
    INT_IMAGE_3D = GL_INT_IMAGE_3D,	//iimage3D
    INT_IMAGE_2D_RECT = GL_INT_IMAGE_2D_RECT,	//iimage2DRect
    INT_IMAGE_CUBE = GL_INT_IMAGE_CUBE,	//iimageCube
    INT_IMAGE_BUFFER = GL_INT_IMAGE_BUFFER,	//iimageBuffer
    INT_IMAGE_1D_ARRAY = GL_INT_IMAGE_1D_ARRAY,	//iimage1DArray
    INT_IMAGE_2D_ARRAY = GL_INT_IMAGE_2D_ARRAY,	//iimage2DArray
    INT_IMAGE_2D_MULTISAMPLE = GL_INT_IMAGE_2D_MULTISAMPLE,	//iimage2DMS
    INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,	//iimage2DMSArray
    UNSIGNED_INT_IMAGE_1D = GL_UNSIGNED_INT_IMAGE_1D,	//uimage1D
    UNSIGNED_INT_IMAGE_2D = GL_UNSIGNED_INT_IMAGE_2D,	//uimage2D
    UNSIGNED_INT_IMAGE_3D = GL_UNSIGNED_INT_IMAGE_3D,	//uimage3D
    UNSIGNED_INT_IMAGE_2D_RECT = GL_UNSIGNED_INT_IMAGE_2D_RECT,	//uimage2DRect
    UNSIGNED_INT_IMAGE_CUBE = GL_UNSIGNED_INT_IMAGE_CUBE,	//uimageCube
    UNSIGNED_INT_IMAGE_BUFFER = GL_UNSIGNED_INT_IMAGE_BUFFER,	//uimageBuffer
    UNSIGNED_INT_IMAGE_1D_ARRAY = GL_UNSIGNED_INT_IMAGE_1D_ARRAY,	//uimage1DArray
    UNSIGNED_INT_IMAGE_2D_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,	//uimage2DArray
    UNSIGNED_INT_IMAGE_2D_MULTISAMPLE = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,	//uimage2DMS
    UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,	//uimage2DMSArray
    UNSIGNED_INT_ATOMIC_COUNTER = GL_UNSIGNED_INT_ATOMIC_COUNTER	//atomic_uint
};


/*
 * glsl type
 *
 * */
class glsl_t {
public:
};


struct glsl_transparent_t_meta
{
    std::uint32_t components_count;
    std::uint32_t component_type_size;
    std::string component_type_name;
    std::uint32_t component_type_gl_enum;
    std::uint32_t type_size;
    std::string semantic_name;

    glsl_transparent_t_meta(
            std::uint32_t _components_count,
            std::uint32_t _component_type_size,
            std::uint32_t _component_type_gl_enum,
            std::uint32_t _type_size,
            std::string _semantic_name) :
            components_count(_components_count),
            component_type_size(_component_type_size),
            component_type_gl_enum(_component_type_gl_enum),
            type_size(_type_size),
            semantic_name(_semantic_name)
    {}
};

enum class glsl_tranparent_type
{
    FLOAT = GL_FLOAT,
    FLOAT_VEC2 = GL_FLOAT_VEC2,
    FLOAT_VEC3 = GL_FLOAT_VEC3,
    FLOAT_VEC4 = GL_FLOAT_VEC4,

    DOUBLE = GL_DOUBLE,
    DOUBLE_VEC2 = GL_DOUBLE_VEC2,
    DOUBLE_VEC3 = GL_DOUBLE_VEC3,
    DOUBLE_VEC4 = GL_DOUBLE_VEC4,

    INT = GL_INT,
    INT_VEC2 = GL_INT_VEC2,
    INT_VEC3 = GL_INT_VEC3,
    INT_VEC4 = GL_INT_VEC4,

    UNSIGNED_INT = GL_UNSIGNED_INT,
    UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,
    UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,
    UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,

    BOOL = GL_BOOL,
    BOOL_VEC2 = GL_BOOL_VEC2,
    BOOL_VEC3 = GL_BOOL_VEC3,
    BOOL_VEC4 = GL_BOOL_VEC4,

    FLOAT_MAT2 = GL_FLOAT_MAT2,
    FLOAT_MAT3 = GL_FLOAT_MAT3,
    FLOAT_MAT4 = GL_FLOAT_MAT4,
    FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,
    FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,
    FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,
    FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,
    FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,
    FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,

    DOUBLE_MAT2 = GL_DOUBLE_MAT2,
    DOUBLE_MAT3 = GL_DOUBLE_MAT3,
    DOUBLE_MAT4 = GL_DOUBLE_MAT4,
    DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,
    DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,
    DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,
    DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,
    DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,
    DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3,
};

enum class glsl_transparent_component_type 
{};


struct glsl_transparent_clazz
{
    std::int32_t components_num;
    glsl_tranparent_type type;
    glsl_transparent_component_type component_type;
    std::int32_t size;
    std::int32_t component_size;
};

/*
 * glsl transparent type
 *
 * */
class glsl_transparent_t : public glsl_t{
public:
    virtual std::uint8_t* data();
	[[nodiscard]] virtual const std::uint8_t* data() const;
	[[nodiscard]] virtual const std::int64_t size() const;
};


#define TOKEN_STR(__TOKEN__) #__TOKEN__

#define DEFINE_GLSL_TRANSPARENT_T(GLSL_T_NAME, GLSL_T_SEMANTIC_NAME)\
class glsl_##GLSL_T_NAME final : public glsl_transparent_t{\
public:\
	glsl_##GLSL_T_NAME() = default;\
	explicit glsl_##GLSL_T_NAME(const glm::GLSL_T_SEMANTIC_NAME& value){}\
	~glsl_##GLSL_T_NAME() = default;\
public:\
	glm::GLSL_T_SEMANTIC_NAME data;\
};\

// float scalar && vectors && matrices
DEFINE_GLSL_TRANSPARENT_T(float, vec1)
DEFINE_GLSL_TRANSPARENT_T(vec2, vec2)
DEFINE_GLSL_TRANSPARENT_T(vec3, vec3)
DEFINE_GLSL_TRANSPARENT_T(vec4, vec4)
DEFINE_GLSL_TRANSPARENT_T(mat2, mat2)
DEFINE_GLSL_TRANSPARENT_T(mat2x3, mat2x3)
DEFINE_GLSL_TRANSPARENT_T(mat2x4, mat2x4)
DEFINE_GLSL_TRANSPARENT_T(mat3, mat3)
DEFINE_GLSL_TRANSPARENT_T(mat3x2, mat3x2)
DEFINE_GLSL_TRANSPARENT_T(mat3x4, mat3x4)
DEFINE_GLSL_TRANSPARENT_T(mat4, mat4)
DEFINE_GLSL_TRANSPARENT_T(mat4x2, mat4x2)
DEFINE_GLSL_TRANSPARENT_T(mat4x3, mat4x3)
// double scalar && vectors && matrices
DEFINE_GLSL_TRANSPARENT_T(double, dvec1)
DEFINE_GLSL_TRANSPARENT_T(dvec2, dvec2)
DEFINE_GLSL_TRANSPARENT_T(dvec3, dvec3)
DEFINE_GLSL_TRANSPARENT_T(dvec4, dvec4)
DEFINE_GLSL_TRANSPARENT_T(dmat2, dmat2)
DEFINE_GLSL_TRANSPARENT_T(dmat2x3, dmat2x3)
DEFINE_GLSL_TRANSPARENT_T(dmat2x4, dmat2x4)
DEFINE_GLSL_TRANSPARENT_T(dmat3, dmat3)
DEFINE_GLSL_TRANSPARENT_T(dmat3x2, dmat3x2)
DEFINE_GLSL_TRANSPARENT_T(dmat3x4, dmat3x4)
DEFINE_GLSL_TRANSPARENT_T(dmat4, dmat4)
DEFINE_GLSL_TRANSPARENT_T(dmat4x2, dmat4x2)
DEFINE_GLSL_TRANSPARENT_T(dmat4x3, dmat4x3)
// int scalar && vectors
DEFINE_GLSL_TRANSPARENT_T(int, ivec1)
DEFINE_GLSL_TRANSPARENT_T(ivec2, ivec2)
DEFINE_GLSL_TRANSPARENT_T(ivec3, ivec3)
DEFINE_GLSL_TRANSPARENT_T(ivec4, ivec4)
// uint scalar && vectors
DEFINE_GLSL_TRANSPARENT_T(uint, uvec1)
DEFINE_GLSL_TRANSPARENT_T(uvec2, uvec2)
DEFINE_GLSL_TRANSPARENT_T(uvec3, uvec3)
DEFINE_GLSL_TRANSPARENT_T(uvec4, uvec4)

/*
 * glsl opaque type
 * sampler/image/atomic_counter
 * */
class glsl_opaque_t : public glsl_t{

};


/*
 * sampler/image
 * */
class glsl_texture_handler_t : glsl_opaque_t{
public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

enum class glsl_storage_qualifier
{
    _const,
    _in,
    _out,
    _uniform,
    _buffer,
    _shared
};

enum class glsl_auxiliary_storage_qualifier
{
    _centroid,
    _sampler,
    _patch,
};

/*
 *
 * */
class glsl_interface_block_t : public glsl_t{
public:
    glsl_interface_block_t() = default;
    glsl_interface_block_t(const glsl_interface_block_t&) = delete;

    ~glsl_interface_block_t() = default;

public:
    virtual std::uint8_t* data() = 0;
    [[nodiscard]] virtual const std::uint8_t* data() const = 0;
    [[nodiscard]] virtual std::int64_t size() const = 0;
};

enum class glsl_interface_block_matrix_layout
{
    ROW_MAJOR,
    COLUMN_MAJOR
};

#endif
