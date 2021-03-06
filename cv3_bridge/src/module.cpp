/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2012, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#include "module.hpp"

PyObject *mod_opencv;

bp::object
cvtColor2Wrap(bp::object obj_in, const std::string & encoding_in, const std::string & encoding_out) {
  // Convert the Python input to an image
  cv::Mat mat_in;
  convert_to_CvMat2(obj_in.ptr(), mat_in);

  // Call cv3_bridge for color conversion
  cv3_bridge::CvImagePtr cv_image(new cv3_bridge::CvImage(std_msgs::Header(), encoding_in, mat_in));

  cv::Mat mat = cv3_bridge::cvtColor(cv_image, encoding_out)->image;

  return bp::object(boost::python::handle<>(pyopencv_from(mat)));
}

BOOST_PYTHON_MODULE(cv3_bridge_boost)
{
  do_numpy_import();
  mod_opencv = PyImport_ImportModule("cv2");

  // Wrap the function to get encodings as OpenCV types
  boost::python::def("getCvType", cv3_bridge::getCvType);
  boost::python::def("cvtColor2", cvtColor2Wrap);
}
