#ifndef HALIDE_BRIGHTNESS
#define HALIDE_BRIGHTNESS

#include "Halide.h"

using namespace Halide;
using namespace Halide::ConciseCasts;

class HalideBrightness : public Generator<HalideBrightness> {
    public:

        Input<Buffer<uint8_t>> img_input{"img_input", 3};

        Output<Buffer<uint8_t>> img_output{"img_output", 3};

        void generate() {
            Expr scale = 1 / 255.0f;
            input_f32(x, y) = f32(img_input(x, y)) * scale;

            // Expr R = input_f32(x, y, 0);
            // Expr G = input_f32(x, y, 1);
            // Expr B = input_f32(x, y, 2);

            // Expr Gray = 0.299f * R + 0.587f * G + 0.114f * B;
            // brightness(x, y) = input_f32(x, y, .299f * R + 0.587f * G + 0.114f * B);

            img_output(x, y, c) = u8_sat(brightness(x, y))
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
        Func brightness{"brightness"};
};

#endif