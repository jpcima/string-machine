#include <fontstash.h>
#include <memory>

struct FONScontext_delete {
    void operator()(FONScontext *x) const noexcept { fonsDeleteInternal(x); }
};

typedef std::unique_ptr<FONScontext, FONScontext_delete> FONScontext_u;
