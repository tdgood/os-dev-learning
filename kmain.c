#include "framebuffer.h"

int sum_of_three(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

int kmain() {
    fb_write("This\nis\na\ntest\nnow\nto\nsee\nwhat\nhappens\nwhen\nwe\ngo\npast\nthe\n25\nheight\nlimit\nthis\nmight\ntake\nmore\nwords\nthan\ni\nthought\noh\nwow\nwere\nstill\ngoing\nhopefully\nthis\nis\nenough.", 166);

    return 0;
}
