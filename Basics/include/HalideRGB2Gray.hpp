#ifndef HALIDE_RGB2GRAY
#define HALIDE_RGB2GRAY

#include "Halide.h"

using namespace Halide;
using namespace Halide::ConciseCasts;

class HalideRGB2Gray : public Generator<HalideRGB2Gray> {
    public:

        Input<Buffer<uint8_t>> img_input{"img_input_rgb", 3};

        Output<Buffer<uint8_t>> img_output{"img_output_gray", 1};

        void generate() {
            Expr scale = 1 / 255.0f;
            input_f32(x, y, c) = f32(img_input(x, y, c)) * scale;

            Expr R = input_f32(x, y, 0);
            Expr G = input_f32(x, y, 1);
            Expr B = input_f32(x, y, 2);

            Expr Gray = 0.299f * R + 0.587f * G + 0.114f * B;

            img_output(x, y, c) = cast<uint8_t>(Gray);
        }

        void schedule() {
            if (using_autoscheduler()) {
                img_input.set_estimates({{0, 1920}, {0, 1920}, {0, 3}});
                img_output.set_estimates({{0, 1920}, {0, 1920}, {0, 3}});
            } else {
                // inline computation
            }
        }

    private:
        Var x{"x"}, y{"y"}, c{"c"};
        Func input_f32{"input_f32"};
};

#endif