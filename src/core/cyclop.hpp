#ifndef CYCLOPH
#define CYCLOPH

#include <Eigen/Dense>
#include <iostream>

template <typename... Args>
void LOG(Args &&... args) {
  (std::cout << ... << args) << std::endl << std::endl;
}

#ifndef NDEBUG
#define ASSERT(condition, message)                                       \
  do {                                                                   \
    if (!(condition)) {                                                  \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__   \
                << " line " << __LINE__ << ": " << message << std::endl; \
      std::terminate();                                                  \
    }                                                                    \
  } while (false)
#else

#define ASSERT(condition, message) \
  do {                             \
  } while (false)
#endif

#ifdef CYCLOP_FLOAT_AS_DOUBLE
typedef double Float;
#else
typedef float Float;
#endif

static constexpr Float MaxFloat = std::numeric_limits<Float>::max();
static constexpr Float Infinity = std::numeric_limits<Float>::infinity();

typedef Eigen::Matrix<Float, 2, 1> Vector2f;
typedef Eigen::Matrix<Float, 3, 1> Vector3f;
typedef Eigen::Matrix<Float, 4, 1> Vector4f;
typedef Eigen::Matrix<int, 2, 1> Vector2i;
typedef Eigen::Matrix<int, 3, 1> Vector3i;

typedef Eigen::Matrix<Float, 4, 4> Matrix4f;

enum Geomtype { VECTOR, POINT, NORMAL };


bool solveQuadratic(const double &a, const double &b, const double &c,
                    Float *t0, Float *t1);


#endif
