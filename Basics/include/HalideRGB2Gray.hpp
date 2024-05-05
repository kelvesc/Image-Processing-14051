#ifndef HALIDE_RGB2GRAY
#define HALIDE_RGB2GRAY

#include "Halide.h"

using namespace Halide;
using namespace Halide::ConciseCasts;

class HalideRGB2Gray : public Generator<HalideRGB2Gray> {
    public:

        Input<Buffer<uint8_t>> img_input{"img_input_rgb", 3};

        Output<Buffer<uint8_t>> img_output{"img_output_gray", 3};

        void generate() {
            Expr scale = 1 / 255.0f;
            input_f32(x, y, c) = f32(img_input(x, y, c)) * scale;

            Expr R = input_f32(x, y, 0);
            Expr G = input_f32(x, y, 1);
            Expr B = input_f32(x, y, 2);

            // Expr Gray = 0.299f * R + 0.587f * G + 0.114f * B;
            grayscale(x, y, c) = input_f32(x, y, .299f * R + 0.587f * G + 0.114f * B);

            img_output(x, y, c) = u8(grayscale);
            // img_output(x, y, c) = clamp(grayscale(x, y), 0, 1);
        }

        void schedule() {
            if (using_autoscheduler()) {
                img_input.set_estimates({{0, 512}, {0, 512}});
                img_output.set_estimates({{0, 512}, {0, 512}});
            } else {
                // inline computation
            }
        }

    private:
        Var x{"x"}, y{"y"}, c{"c"};
        Func input_f32{"input_f32"};
        Func grayscale{"grayscale"};
};

#endif