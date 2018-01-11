#ifndef LWSS_TEXTURE_HH
#define LWSS_TEXTURE_HH

#include <lwss/image.hh>

#include <GL/glew.h>

namespace lwss {
    class Texture final {
    public:
        enum class WrapMode {
            ClampToBorder = GL_CLAMP_TO_BORDER,
            ClampToEdge = GL_CLAMP_TO_EDGE,
            MirroredRepeat = GL_MIRRORED_REPEAT,
            MirroredClampToEdge = GL_MIRROR_CLAMP_TO_EDGE,
            Repeat = GL_REPEAT
        };

        enum class MinFilter {
            Nearest = GL_NEAREST,
            Linear = GL_LINEAR,
            NearestMipmap = GL_NEAREST_MIPMAP_NEAREST,
            LinearMipmap = GL_LINEAR_MIPMAP_NEAREST,
            SmoothMipmap = GL_LINEAR_MIPMAP_LINEAR
        };

        enum class MagFilter {
            Nearest = GL_NEAREST,
            Linear = GL_LINEAR
        };

        struct Parameters final {
            WrapMode wrap_s { WrapMode::Repeat };
            WrapMode wrap_t { WrapMode::Repeat };
            float border_color[4] { 0.0, 0.0, 0.0, 1.0 };
            MinFilter min_filter { MinFilter::SmoothMipmap };
            MagFilter mag_filter { MagFilter::Linear };
        };

        Texture(const Image& image, const Parameters& parameters, GLuint texture_unit = 0);
        Texture(const Image& image, GLuint texture_unit = 0) : Texture { image, Parameters {  },
                                                                         texture_unit } {  }
        ~Texture() noexcept;

        void bind() const;
        GLenum active_unit() const;
        void active_unit(GLuint unit);

    private:
        GLuint unit;
        GLuint handle;
    };
}

#endif
