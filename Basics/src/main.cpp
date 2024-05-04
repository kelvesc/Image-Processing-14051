#include <iostream>
#include "HalideBuffer.h"
#include "halide_image_io.h"
#include "rgb2gray.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

using namespace Halide::Runtime;
using namespace Halide::Tools;

int main(int argc, char**argv) {
    if (argc < 3) {
        cout << "Usage: bin/main <path/to/input> <path/to/output>" << endl;
        return -1;
    }

    const string path_in = argv[1];
    const string path_out = argv[2];

    Buffer<uint8_t> img_input = load_image(path_in);
    Buffer<uint8_t> img_output = Buffer<uint8_t>::make_with_shape_of(img_input);

    // rgb2gray = create<HalideRGB2Gray>();
    // rgb2gray->apply(img_output_gray);
    // img_output = u8(rgb2gray(img_input));


    rgb2gray(img_input, img_output);

    save_image(img_output, path_out);

    return 0;
}