#ifndef KARAMAY_ENGINE_GRAPHICS_UNIT_GLSL_SAMPLER_T_H
#define KARAMAY_ENGINE_GRAPHICS_UNIT_GLSL_SAMPLER_T_H

#include "glsl_class.h"

class glsl_sampler_t : public glsl_opaque_t
{
protected:
    glsl_sampler_t() = delete;
    explicit glsl_sampler_t(std::string& value_name) :
        _value_name(std::move(value_name))
    {

    }
    ~glsl_sampler_t() = default;

    std::string _value_name;

public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
};


class glsl_sampler1D : public glsl_sampler_t {
public:
    glsl_sampler1D(std::string value_name) :
            glsl_sampler_t(value_name)
    {}

    struct glsl_sampler1DResource
    {
        std::shared_ptr<gl_texture_1d_base> texture_1d;
    } resource;

    void bind() override
    {
        if(!resource.texture_1d) return;
        glBindTextureUnit(GL_TEXTURE0 + 1, resource.texture_1d->get_handle());
    }

    void unbind() override
    {
        if(!resource.texture_1d) return;
        glBindTextureUnit(GL_TEXTURE0 + 1, 0);
    }

private:

};

class glsl_sampler1DArray : public glsl_sampler_t {
public:
    glsl_sampler1DArray() = delete;
    glsl_sampler1DArray(std::string value_name) :
        glsl_sampler_t(value_name)
    {

    }

    struct glsl_sampler1DArrayResource
    {
        std::shared_ptr<gl_texture_1d_array_base> texture_array;
    } resource;


    void bind() override
    {

    }

};

class glsl_sampler2D : public glsl_sampler_t
{
public:

    glsl_sampler2D() = default;

public:

    struct glsl_sampler2DResource
    {
        std::shared_ptr<gl_texture_2d_base> texture_2d;
    } resource;


    void bind()
    {
        glBindTextureUnit(GL_TEXTURE0, texture_2d->get_handle());
    }

    void unbind()
    {
        glBindTextureUnit(GL_TEXTURE0, 0);
    }


};

class glsl_sampler2DArray : public glsl_sampler_t
{
public: /** constructor / desctructor  */

    glsl_sampler2DArray() = delete;

    virtual ~glsl_sampler2DArray() = default;

public: /** implement functions */

    struct glsl_sampler2DArrayResource
    {
        std::shared_ptr<gl_texture_2d_array_base> texture_2d_array;
    } resource;

public:

    void bind()
    {
        glBindTextureUnit(GL_TEXTURE0, texture_2d_array->get_handle());
    }

    void unbind()
    {
        glBindTextureUnit(GL_TEXTURE0, 0);
    }

};

class glsl_sampler2DMS : public glsl_sampler_t
{
public:

    glsl_sampler2DMS(){}

public:

    struct glsl_sampler2DMSResource
    {
        std::shared_ptr<gl_texture_2d_multisample_base> texture_2d_multisample;
    } resource;


    void bind()
    {
        glBindTextureUnit(GL_TEXTURE0, texture_2d->get_handle());
    }

    void unbind()
    {
        glBindTextureUnit(GL_TEXTURE0, 0);
    }


};

class glsl_sampler2DMSArray : public glsl_sampler_t
{
public:

    glsl_sampler2DMSArray() = delete;

public:

    struct glsl_sampler2DMSArrayResource
    {
        std::shared_ptr<gl_texture_2d_multisample_array_base> texture_2d_multisample_array;
    } resource;

public:

    void bind()
    {
        glBindTextureUnit(GL_TEXTURE0, texture_2d_array->get_handle());
    }

    void unbind()
    {
        glBindTextureUnit(GL_TEXTURE0, 0);
    }

};

class glsl_samplerCube : public glsl_sampler_t {
public:
    glsl_samplerCube(){}

    struct glsl_samplerCubeResource
    {
        std::shared_ptr<gl_texture_cube_base> texture_cube;
    } resource;
};

class glsl_samplerCubeArray : public glsl_sampler_t {
public:

    struct glsl_samplerCubeArrayResource
    {
        std::shared_ptr<gl_texture_cube_array_base> texture_cube_array;
    } resource;
};

class glsl_sampler2DRect : public glsl_sampler_t
{
public:

    glsl_sampler2DRect() = default;

public:

    struct glsl_sampler2DRectResource
    {
        std::shared_ptr<gl_texture_rectangle_base> texture_rectangle;
    } resource;

};

class glsl_sampler3D : public glsl_sampler_t {

    struct glsl_sampler3DResource
    {
        std::shared_ptr<gl_texture_3d_base> texture_3d;
    } resource;
};

class glsl_samplerBuffer : public glsl_sampler_t
{
public:
    glsl_samplerBuffer();

public:

    struct glsl_samplerBufferResource
    {
        std::shared_ptr<gl_texture_buffer_base> texture_buffer;

    } resource;

};



class glsl_sampler1DShadow : public glsl_sampler_t {};

class glsl_sampler1DArrayShadow : public glsl_sampler_t {};

class glsl_sampler2DShadow : public glsl_sampler_t {};

class glsl_sampler2DArrayShadow : public glsl_sampler_t {};

class glsl_samplerCubeShadow : public glsl_sampler_t {};

class glsl_samplerCubeArrayShadow : public glsl_sampler_t {};

class glsl_sampler2DRectShadow : public glsl_sampler_t {};





//DEFINE_GLSL_SAMPLER_T(sampler1D)
//DEFINE_GLSL_SAMPLER_T(sampler1DArray)
//DEFINE_GLSL_SAMPLER_T(sampler2D)
//DEFINE_GLSL_SAMPLER_T(sampler2DArray)
//DEFINE_GLSL_SAMPLER_T(samplerCube)
//DEFINE_GLSL_SAMPLER_T(samplerCubeArray)
//DEFINE_GLSL_SAMPLER_T(sampler2DMS)
//DEFINE_GLSL_SAMPLER_T(sampler2DMSArray)
//DEFINE_GLSL_SAMPLER_T(sampler2DRect)
//DEFINE_GLSL_SAMPLER_T(sampler3D)
//DEFINE_GLSL_SAMPLER_T(samplerBuffer)

//DEFINE_GLSL_SAMPLER_T(sampler1DShadow)
//DEFINE_GLSL_SAMPLER_T(sampler2DShadow)
//DEFINE_GLSL_SAMPLER_T(sampler1DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(sampler2DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(samplerCubeShadow)
//DEFINE_GLSL_SAMPLER_T(samplerCubeArrayShadow)
//DEFINE_GLSL_SAMPLER_T(sampler2DRectShadow)


//DEFINE_GLSL_SAMPLER_T(isampler1D)
//DEFINE_GLSL_SAMPLER_T(isampler1DArray)
//DEFINE_GLSL_SAMPLER_T(isampler2D)
//DEFINE_GLSL_SAMPLER_T(isampler2DArray)
//DEFINE_GLSL_SAMPLER_T(isampler2DRect)
//DEFINE_GLSL_SAMPLER_T(isampler2DMS)
//DEFINE_GLSL_SAMPLER_T(isampler2DMSArray)
//DEFINE_GLSL_SAMPLER_T(isampler3D)
//DEFINE_GLSL_SAMPLER_T(isamplerCube)
//DEFINE_GLSL_SAMPLER_T(isamplerCubeArray)
//DEFINE_GLSL_SAMPLER_T(isamplerBuffer)
//DEFINE_GLSL_SAMPLER_T(isampler1DShadow)
//DEFINE_GLSL_SAMPLER_T(isampler2DShadow)
//DEFINE_GLSL_SAMPLER_T(isampler2DRectShadow)
//DEFINE_GLSL_SAMPLER_T(isampler1DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(isampler2DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(isamplerCubeShadow)
//DEFINE_GLSL_SAMPLER_T(isamplerCubeArrayShadow)

//DEFINE_GLSL_SAMPLER_T(usampler1D)
//DEFINE_GLSL_SAMPLER_T(usampler1DArray)
//DEFINE_GLSL_SAMPLER_T(usampler2D)
//DEFINE_GLSL_SAMPLER_T(usampler2DArray)
//DEFINE_GLSL_SAMPLER_T(usampler2DRect)
//DEFINE_GLSL_SAMPLER_T(usampler2DMS)
//DEFINE_GLSL_SAMPLER_T(usampler2DMSArray)
//DEFINE_GLSL_SAMPLER_T(usampler3D)
//DEFINE_GLSL_SAMPLER_T(usamplerCube)
//DEFINE_GLSL_SAMPLER_T(usamplerCubeArray)
//DEFINE_GLSL_SAMPLER_T(usamplerBuffer)
//DEFINE_GLSL_SAMPLER_T(usampler1DShadow)
//DEFINE_GLSL_SAMPLER_T(usampler2DShadow)
//DEFINE_GLSL_SAMPLER_T(usampler2DRectShadow)
//DEFINE_GLSL_SAMPLER_T(usampler1DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(usampler2DArrayShadow)
//DEFINE_GLSL_SAMPLER_T(usamplerCubeShadow)
//DEFINE_GLSL_SAMPLER_T(usamplerCubeArrayShadow)


#endif