#ifndef HELLOQT_EIGEN_H
#define HELLOQT_EIGEN_H

#include <Eigen/Dense>

using namespace Eigen;


using VectorRGB = Matrix<unsigned char, 3, 1>;
using MatrixXf =  Matrix<float, Eigen::Dynamic, Eigen::Dynamic>;
using MatrixXuc =  Matrix<uchar, Eigen::Dynamic, Eigen::Dynamic>;

#endif //!HELLOQT_INCLUDES_H
