#ifndef CAMERAH
#define CAMERAH

#include "core/cyclop.hpp"

namespace transform {
class Transform;
}

namespace camera {
class Camera {
 public:
};

transform::Transform rasterToNdc(const Float &resX, const Float &resY);
transform::Transform ndcToCam(const Float &aspect, const Float &fov);
transform::Transform rasterToCam(const Float &resX, const Float &resY,
                                 const Float &fov);

}  // namespace camera

#endif