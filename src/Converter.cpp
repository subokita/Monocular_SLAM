//
// Created by JimXing on 19/11/16.
//
#include "Converter.h"

namespace Converter {
    // SE3Quat and Mat
    g2o::SE3Quat cvMatToSE3Quat (const Mat mat) {
        // mat is either 4 by 4 or 3 by 4
        Eigen::Matrix<double,3,3> R;
        R << mat.at<double>(0,0), mat.at<double>(0,1), mat.at<double>(0,2),
                mat.at<double>(1,0), mat.at<double>(1,1), mat.at<double>(1,2),
                mat.at<double>(2,0), mat.at<double>(2,1), mat.at<double>(2,2);

        Eigen::Matrix<double,3,1> t(mat.at<double>(0,3), mat.at<double>(1,3), mat.at<double>(2,3));

        return g2o::SE3Quat(R,t);
    }

    Mat SE3QuatToCvMat(const g2o::SE3Quat &SE3) {
        // convert to 3 by 4 pose matrix
        Eigen::Matrix<double,4,4> eigen_mat = SE3.to_homogeneous_matrix();
        // normalize by eigen_mat(3,3)
        eigen_mat = eigen_mat/eigen_mat(3,3);
        cv::Mat cv_mat(3,4,CV_64F);
        for(int i=0;i<3;i++)
            for(int j=0; j<4; j++)
                cv_mat.at<double>(i,j)=eigen_mat(i,j);

        return cv_mat.clone();
    }


    // Eigen and Mat, 3 by 1
    Eigen::Matrix<double, 3, 1> cvMatToVector3d(const Mat mat) {
        Eigen::Matrix<double,3,1> v;
        v << mat.at<double>(0), mat.at<double>(1), mat.at<double>(2);
        return v;
    }

    Mat vector3DToCvMat(const Eigen::Matrix<double, 3, 1> &m) {
        cv::Mat cv_mat(3,1,CV_64F);
        for(int i=0;i<3;i++)
            for(int j=0; j<1; j++)
                cv_mat.at<double>(i,j)=m(i,j);

        return cv_mat.clone();
    }

    Eigen::Matrix<double,3,1> point3dToVector3d(const Point3d p)
    {
        Eigen::Matrix<double,3,1> v;
        v << p.x, p.y, p.z;
        return v;
    }
        
    Point3d vector3dToPoint3d(const Eigen::Matrix<double,3,1> p)
    {
        Point3d point;
        point.x = p(0,0);
        point.y = p(1,0);
        point.z = p(2,0);
        return point;
    }

    // Eigen and cv Mat, 4 by 4
    Eigen::Matrix<double, 4, 4> cvMatToEigenMatrix(const Mat mat) {
        Eigen::Matrix<double,4,4> v;
        for(int i=0;i<4;i++)
            for(int j=0; j<4; j++)
                v << mat.at<double>(i,j);

        return v;
    }

    Mat eigenMatrixToCvMat(const Eigen::Matrix<double,4,4> &m) {
        cv::Mat cv_mat(4,4,CV_64F);
        for(int i=0;i<4;i++)
            for(int j=0; j<4; j++)
                cv_mat.at<double>(i,j)=m(i,j);

        return cv_mat.clone();
    }
}

