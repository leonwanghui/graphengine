/**
 * Copyright 2019-2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GE_OP_NN_CALCULATION_OPS_H
#define GE_OP_NN_CALCULATION_OPS_H

#include "graph/operator_reg.h"

namespace ge {
/**
* @brief Computes the gradients of depthwise convolution with respect to
* the filter.

* @par Inputs:
* Three inputs include: \n
* @li input: 4D origin shape of input tensor [N, C, H, W] or [N, H, W, C],
* support float16, float32, double
* @li filter_size: A 4D tensor of type int32, with shape [H, W, C, K]
* @li out_backprop: 4D tensor with shape [N, C, H, W] or [N, H, W, C].
* Must be one of the following types: float16, float32, double.

* @par Attributes:
* @li strides: A required list or tuple. The stride of the sliding window
* for height and width of input "x" of the convolution.
* Must be with shape [1, 1, stride_height, stride_width] or
* [1, stride_height, stride_width, 1].
* @li dilations: An optional list or tuple. The dilation factor for each
* dimension of input "x".
* If set to k > 1, there will be k-1 skipped cells between each filter element
* on that dimension. Must be with shape [1, 1, dilation_height, dilation_width]
* or [1, dilation_height, dilation_width, 1].
* @li pads: A required list or tuple. Padding added to each dimension of the
* input.
* @li data_format: An optional string. Input data format, either "NHWC" or
* "NCHW".

* @par Outputs:
* filter_grad: Gradient of the deep convolution relative to the filter with
* shape [H, W, C, K]. Must be one of the following types: float16, float32,
* double.

* @attention Constraints:\n
* The feature map is 4D with shape [N, C, Hi, Wi] or [N, Hi, Wi, C], but
* the data is 5D with shape [N, C1, Hi, Wi, C0], where C0 is 16.\n
* The filter is 4D with shape [Hf, Wf, C, K], but the data is 6D with shape
* [C1, Hf, Wf, K, Co, C0],
* where K is fixed at 1, and Co and C0 are 16.\n
* Output backprop is 4D with shape [N, C, Ho, Wo] or [N, Ho, Wo, C], but the
* data is 5D with shape [N, C1, Ho, Wo, C0],
* where C is the same as that of the feature map and C0 is 16.\n
* Limited by Tiling and L1 / L0 buffer memory: 512 * ceil(Wo, 16) + (480 *
* stride_h + 32 * filter_h) * ceil(Wi, 16) <= l1_size and Hf*Wf <= l0b_size/512.

* @par Third-party framework compatibility
* @li Compatible with the TensorFlow operator DepthwiseConv2DBackpropFilter.
* @li Compatible with the Caffe operator DepthwiseConv2DBackpropFilter.
*/
REG_OP(DepthwiseConv2DBackpropFilter)
    .INPUT(input, TensorType({float16}))
    .INPUT(filter_size, TensorType({DT_INT32, DT_INT64}))
    .INPUT(out_backprop, TensorType({float16}))
    .OUTPUT(filter_grad, TensorType({float32}))
    .REQUIRED_ATTR(strides, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(DepthwiseConv2DBackpropFilter)

/**
* @brief Computes the gradients of depthwise convolution with respect to
* the filter.

* @par Inputs:
* Two inputs include: \n
* @li input: 4D tensor with shape [N, C, H, W] or [N, H, W, C], of type float16
* @li out_backprop: 4D tensor with shape [N, C, H, W] or [N, H, W, C],
* of type float16

* @par Attributes:
* @li filter_size: A required list or tuple. Shape of filter.
* @li strides: A required list or tuple. The stride of the sliding window for
* height and width of input "x" of the convolution.
* Must be with shape [1, 1, stride_height, stride_width] or [1, stride_height,
* stride_width, 1].
* @li dilations: An optional list or tuple. The dilation factor for each
* dimension of input "x".
* If set to k > 1, there will be k-1 skipped cells between each filter element
* on that dimension. Must be with shape [1, 1, dilation_height, dilation_width]
* or [1, dilation_height, dilation_width, 1].
* @li pads: A required list or tuple. Padding added to each dimension of the
* input.
* @li data_format: An optional string. Input data format, either "NHWC" or
* "NCHW".

* @par Outputs:
* filter_grad: Gradient of the deep convolution relative to the filter with
* shape [H, W, C, K]. Must be of type float32.

* @attention Constraints:\n
* The feature map is 4D with shape [N, C, Hi, Wi] or [N, Hi, Wi, C], but
* the data is 5D with shape [N, C1, Hi, Wi, C0], where C0 is 16.\n
* The filter is 4D with shape [Hf, Wf, C, K], but the data is 6D with shape
* [C1, Hf, Wf, K, Co, C0],
* where K is fixed at 1, and Co and C0 are 16.\n
* Output backprop is 4D with shape [N, C, Ho, Wo] or [N, Ho, Wo, C], but the
* data is 5D with shape [N, C1, Ho, Wo, C0],
* where C is the same as that of the feature map and C0 is 16.\n
* Limited by Tiling and L1 / L0 buffer memory: 512 * ceil(Wo, 16) + (480 *
* stride_h + 32 * filter_h) * ceil(Wi, 16) <= l1_size and Hf*Wf <= l0b_size/512.

* @par Third-party framework compatibility
* @li Compatible with the TensorFlow operator DepthwiseConv2DBackpropFilter.
* @li Compatible with the Caffe operator DepthwiseConv2DBackpropFilter.
*/
REG_OP(DepthwiseConv2DBackpropFilterD)
    .INPUT(input, TensorType({float16}))
    .INPUT(out_backprop, TensorType({float16}))
    .OUTPUT(filter_grad, TensorType({float32}))
    .REQUIRED_ATTR(filter_size, ListInt)
    .REQUIRED_ATTR(strides, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(DepthwiseConv2DBackpropFilterD)

/**
* @brief Computes the gradients of depthwise convolution with respect to the
* input.

* @par Inputs:
* Three inputs include: \n
* @li input_size: 4D shape of input tensor [N, C, H, W] or [N, H, W, C],
* support int32, int64
* @li filter: 4D filter tensor with shape of [H, W, C, K], support float16.
* @li out_backprop: 4D tensor with shape [N, C, H, W] or [N, H, W, C].
* Must be one of the following types: float16.

* @par Attributes:
* @li strides: A required list or tuple of int32. The stride of the sliding window for
* height and width of input "x" of the convolution.
* Must be with shape [1, 1, stride_height, stride_width] or [1, stride_height,
* stride_width, 1].
* @li dilations: An optional list or tuple of int32. The dilation factor for each
* dimension of input "x". Defaults to "[1, 1, 1, 1]".
* If set to k > 1, there will be k-1 skipped cells between each filter element
* on that dimension. Must be with shape [1, 1, dilation_height, dilation_width]
* or [1, dilation_height, dilation_width, 1].
* @li pads: A required list or tuple of int32. Padding added to each dimension of the
* input.
* @li data_format: An optional string. Input data format, either "NHWC" or
* "NCHW". Defaults to "NHWC".

* @par Outputs:
* input_grad: Gradient of the deep convolution relative to the input with shape
* [N, C, H, W] or [N, H, W, C] Must be one of the following types: float16.

* @attention Constraints:\n
* The feature map is 4D with shape [N, C, Hi, Wi] or [N, Hi, Wi, C], but
* the data is 5D with shape [N, C1, Hi, Wi, C0], where C0 is 16.\n
* The filter is 4D with shape [Hf, Wf, C, K], but the data is 6D with shape
* [C1, Hf, Wf, K, Co, C0],
* where K is fixed at 1, and Co and C0 are 16.\n
* Output backprop is 4D with shape [N, C, Ho, Wo] or [N, Ho, Wo, C], but the
* data is 5D with shape [N, C1, Ho, Wo, C0],
* where C is the same as that of the feature map and C0 is 16.\n
* Limited by Tiling: max_h_in_l1 >= C0, where max_h_in_l1 = (l1_size - Hf *
* Wf * C0 * C0 * 2) / (2 * Wo *C0).\n

* @par Third-party framework compatibility
* @li Compatible with the TensorFlow operator DepthwiseConv2DBackpropInput.
* @li Compatible with the Caffe operator DepthwiseConv2DBackpropInput.
*/
REG_OP(DepthwiseConv2DBackpropInput)
    .INPUT(input_size, TensorType({DT_INT32, DT_INT64}))
    .INPUT(filter, TensorType({DT_FLOAT16}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16}))
    .OUTPUT(input_grad, TensorType({DT_FLOAT16}))
    .REQUIRED_ATTR(strides, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(DepthwiseConv2DBackpropInput)

/**
* @brief Computes the gradients of depthwise convolution with respect to the
* input.

* @par Inputs:
* Two inputs include: \n
* @li filter: A 4D tensor of type float16, with shape [H, W, C, K]
* @li out_backprop: 4D tensor with shape [N, C, H, W] or [N, H, W, C], of
* type float16

* @par Attributes:
* @li input_size: A required list or tuple. The origin shape of input.
* @li strides: A required list or tuple. The stride of the sliding window for
* height and width of input "x" of the convolution.
* Must be with shape [1, 1, stride_height, stride_width] or [1, stride_height,
* stride_width, 1].
* @li dilations: An optional list or tuple. The dilation factor for each
* dimension of input "x".
* If set to k > 1, there will be k-1 skipped cells between each filter element
* on that dimension. Must be with shape [1, 1, dilation_height, dilation_width]
* or [1, dilation_height, dilation_width, 1].
* @li pads: A required list or tuple. Padding added to each dimension of the
* input.
* @li data_format: An optional string. Input data format, either "NHWC" or
* "NCHW".

* @par Outputs:
* input_grad: Gradient of the deep convolution relative to the input with
* shape [N, C, H, W] or [N, H, W, C]. Must be of type float16.

* @attention Constraints:\n
* The feature map is 4D with shape [N, C, Hi, Wi] or [N, Hi, Wi, C], but
* the data is 5D with shape [N, C1, Hi, Wi, C0], where C0 is 16.\n
* The filter is 4D with shape [Hf, Wf, C, K], but the data is 6D with shape
* [C1, Hf, Wf, K, Co, C0],
* where K is fixed at 1, and Co and C0 are 16.\n
* Output backprop is 4D with shape [N, C, Ho, Wo] or [N, Ho, Wo, C], but the
* data is 5D with shape [N, C1, Ho, Wo, C0],
* where C is the same as that of the feature map and C0 is 16.\n
* Limited by Tiling: max_h_in_l1 >= C0, where max_h_in_l1 = (l1_size - Hf *
* Wf * C0 * C0 * 2) / (2 * Wo *C0).\n

* @par Third-party framework compatibility
* @li Compatible with the TensorFlow operator DepthwiseConv2DBackpropInput.
* @li Compatible with the Caffe operator DepthwiseConv2DBackpropInput.
*/
REG_OP(DepthwiseConv2DBackpropInputD)
    .INPUT(filter, TensorType({DT_FLOAT16}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16}))
    .OUTPUT(input_grad, TensorType({DT_FLOAT16}))
    .REQUIRED_ATTR(input_size, ListInt)
    .REQUIRED_ATTR(strides, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(DepthwiseConv2DBackpropInputD)

/**
*@brief Computes a 2D deep convolution given a 4D input tensor and a filter
* tensor.

*@par Inputs:
*Two required inputs and two optional inputs, including: \n
* @li x: A 4D tensor of type float16 or int8, with shape [N, C, H, W] or [N, H, W, C]
* @li filter: A 4D tensor of type float16 or int8, with shape [H, W, C, K]
* @li bias: An optional tensor of type float16 or int32
* @li offset_w: An optional float16 or int8, used for quantized inference

* @par Attributes:
* @li strides: A required list or tuple. The stride of the sliding window for
* height and width of input "x" of the convolution.
* Must be with shape [1, 1, stride_height, stride_width] or [1, stride_height,
* stride_width, 1].
* @li dilations: An optional list or tuple. The dilation factor for each
* dimension of input "x".
* If set to k > 1, there will be k-1 skipped cells between each filter element
* on that dimension. Must be with shape [1, 1, dilation_height, dilation_width]
* or [1, dilation_height, dilation_width, 1]. Defaults to "[1, 1, 1, 1]".
* @li pads: A required list or tuple of int32. Padding added to each dimension of the
* input.
* @li data_format: An optional string. Input data format, either "NHWC" or
* "NCHW". Defaults to "NHWC".
* @li offset_x: An optional int. Input offset, used for quantized inference.
* Defaults to 0.

* @par Outputs:
* y: 4D tensor of type float16 or int32, with shape [N, C, H, W] or [N, H, W, C]

* @attention Constraints:\n
* The feature map is 4D with shape [N, C, Hi, Wi] or [N, Hi, Wi, C], but
* the data is 5D with shape [N, C1, Hi, Wi, C0], where C0 is 16.\n
* The filter is 4D with shape [Hf, Wf, C, K], but the data is 6D with shape
* [C1, Hf, Wf, K, Co, C0],
* where K is fixed at 1, and Co and C0 are 16.\n
* Limited by the size of L1 buffer memory: \n
* (l1_size - filter_h*filter_w*BLOCK_SIZE*BLOCK_SIZE*data_size) // (Wi *
* BLOCK_SIZE * data_size) >= (BLOCK_SIZE * strides_h + filter_h - strides_h).\n

* @par Quantization supported or not
* Yes

* @par Third-party framework compatibility
* @li Compatible with the TensorFlow operator DepthwiseConv2D.
* @li Compatible with the Caffe operator DepthwiseConv2D.
*/
REG_OP(DepthwiseConv2D)
    .INPUT(x, TensorType({DT_FLOAT16, DT_INT8}))
    .INPUT(filter, TensorType({DT_FLOAT16, DT_INT8}))
    .OPTIONAL_INPUT(bias, TensorType({DT_FLOAT16, DT_INT32}))
    .OPTIONAL_INPUT(offset_w, TensorType({DT_FLOAT16, DT_INT8}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_INT32}))
    .REQUIRED_ATTR(strides, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(data_format, String, "NHWC")
    .ATTR(offset_x, Int, 0)
    .OP_END_FACTORY_REG(DepthwiseConv2D)

/**
*@brief Performs the the backward operation for "BiasAdd" on the "bias" tensor.
*        It accumulates all the values from out_backprop into the feature
*        dimension. For NHWC data format, the feature dimension is the last.
*        For NCHW data format, the feature dimension is the third-to-last.

*@par Inputs:
*x: A Tensor of type NumberType.

*@par Attributes:
*data_format: Data format. Defaults to "NHWC".

*@par Outputs:
*y: A Tensor.Has the same type as "x".

*@par Third-party framework compatibility
* Compatible with the TensorFlow operator BiasAddGrad.
*/
REG_OP(BiasAddGrad)
    .INPUT(x, TensorType::NumberType())
    .OUTPUT(y, TensorType::NumberType())
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(BiasAddGrad)

/**
*@brief Computes the gradients of convolution with respect to the input.
*@par Inputs:
 * Three inputs:
 * @li input_size: A Tensor of type int32. An integer vector representing the shape of input,
 * where input is a 4-D tensor [batch, height, width, channels] or [batch, channels, height, width].
 * @li filter: A Tensor. Must be one of the following types: float16, float32, float64.
 * 4-D with shape [filter_height, filter_width, in_channels, out_channels]
 * or [out_channels, filter_height, filter_width, in_channels] or [out_channels, in_channel, filter_height, filter_width].
 * @li out_backprop: A Tensor. Must have the same type as filter. 4-D with shape [batch, out_height, out_width, out_channels]
 * or [batch, out_channels, out_height, out_width]. Gradients with respect to the output of the convolution.
*@par Attributes:
 * Five attributes:
 * @li strides: A tuple/list of 2 integers. The stride of the sliding window for H/W dimension.
 * @li pads: A tuple/list of 4 integers, [top, bottom, left, right] pads on feature map
 * @li dilations: A tuple/list of 4 integers, The dilation factor for each dimension of input, now only support [1,1,1,1]
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NHWC", "NCHW". Defaults to "NHWC". Specify the data format of the input and output data.
*@par Outputs:
 * y: A Tensor. Has the same type as filter,and has same format as input_size
*@par Third-party framework compatibility
 * Compatible with Tensorflow's conv2d_backprop_input
*/
REG_OP(Conv2DBackpropInput)
    .INPUT(input_size, TensorType({DT_INT32}))
    .INPUT(filter, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(Conv2DBackpropInput)

/**
*@brief Computes the gradients of convolution with respect to the input.
*@par Inputs:
 * Two inputs:
 * @li filter: A Tensor. Types is float16.
 * 4-D with shape [filter_height, filter_width, in_channels, out_channels] or [out_channels, filter_height, filter_width, in_channels]
 * or [out_channels, in_channel, filter_height, filter_width].
 * @li out_backprop: A Tensor. Must have the same type as filter. 4-D with shape [batch, out_height, out_width, out_channels]
 * or [batch, out_channels, out_height, out_width]. Gradients with respect to the output of the convolution.
*@par Attributes:
 * Six attributes:
 * @li input_size A Tensor of type int32. An integer vector representing the shape of input,
 * where input is a 4-D tensor [batch, height, width, channels] or [batch, channels, height, width].
 * @li strides: A tuple/list of 2 integers. The stride of the sliding window for H/W dimension.
 * @li pads: A tuple/list of 4 integers, [top, bottom, left, right] pads on feature map
 * @li dilations: A tuple/list of 4 integers, The dilation factor for each dimension of input, now only support [1,1,1,1]
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NHWC", "NCHW". Defaults to "NHWC". Specify the data format of the input and output data.
*@par Outputs:
 * y: A Tensor. Has the same type as filter,4-D tensor [batch, height, width, channels] or [batch, channels, height, width].
*@par Third-party framework compatibility
 * Compatible with Tensorflow's conv2d_backprop_input
*/
REG_OP(Conv2DBackpropInputD)
    .INPUT(filter, TensorType({DT_FLOAT16, DT_INT8}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16, DT_INT8}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_INT32}))
    .REQUIRED_ATTR(input_size, ListInt)
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(Conv2DBackpropInputD)

/**
*@brief Computes the Deconvolution with respect to the input.
*@par Inputs:
 * Three inputs:
 * @li x: A Tensor. Must have the same type as "filter". 4D with shape
 * [batch, out_channels, out_height, out_width]. Gradients with respect
 * to the output of the convolution.
 * @li filter: A Tensor of type float16, float32, double or int8.
 * 4D with shape [out_channels, in_channel, filter_height, filter_width].\n
 * Two optional inputs:
 * @li bias: An optional tensor of type float16, float32, int32 or int64.
 * @li offset_w: An optional 1D tensor for quantized deconvolution. Type is int8. Reserved.\n
*@par Attributes:
 * Six attributes:
 * @li strides: A tuple or list of 2 integers. The stride of the sliding window
 * for H/W dimension. Defaults to [1, 1, 1, 1].
 * @li pads: A tuple or list of 4 integers. The [top, bottom, left, right]
 * padding on the feature map. Defaults to [0, 0, 0, 0].
 * @li dilations: A tuple or list of 4 integers. The dilation factor for each
 * dimension of input. Must be [1, 1, 1, 1].
 * @li groups: Number of blocked connections from input channels to
 output channels. Defaults to "1".
 * @li data_format: An optional string from: "NCHW". Defaults to "NCHW". \n
  Specify the data format of the input and output data.
 * @li offset_x: An optional integer for quantized deconvolution. Defaults to "0".
*@par Outputs:
 * y: A Tensor. Has the same type as "filter". 4D tensor with shape
 * [batch, channels, height, width].
*/
REG_OP(Deconvolution)
    .INPUT(x, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE, DT_INT8}))
    .INPUT(filter, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE, DT_INT8}))
    .OPTIONAL_INPUT(bias, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE, DT_INT32}))
    .OPTIONAL_INPUT(offset_w, TensorType({DT_INT8}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE, DT_INT32}))
    .ATTR(strides, ListInt, {1, 1})
    .ATTR(pads, ListInt, {0, 0, 0, 0})
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NCHW")
    .ATTR(offset_x, Int, 0)
    .OP_END_FACTORY_REG(Deconvolution)
/**
*@brief Computes the gradients of convolution with respect to the filter
*@par Inputs:
 * Three inputs:
 * @li x: A Tensor. Must be one of the following types: float16, float32, float64.
 * 4-D with shape [batch, in_height, in_width, in_channels] or [batch, in_channels, in_height, in_width].
 * @li filter_size: A Tensor of type int32. An integer vector representing the tensor shape of filter,
 * where filter is a 4-D tensor [filter_height, filter_width, in_channels, out_channels]
 * or [out_channels, filter_height, filter_width, in_channels] or [out_channels, in_channel, filter_height, filter_width].
 * @li out_backprop: A Tensor. Must have the same type as x. 4-D with shape [batch, out_height, out_width, out_channels]
 * or [batch, out_channels, out_height, out_width]. Gradients with respect to the output of the convolution.
*@par Attributes:
 * Five attributes:
 * @li strides: A tuple/list of 2 integers. The stride of the sliding window for H/W dimension.
 * @li pads: A tuple/list of 4 integers, [top, bottom, left, right] pads on feature map.
 * @li dilations: A tuple/list of 4 integers, The dilation factor for each dimension of input, now only support [1,1,1,1].
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NHWC", "NCHW". Defaults to "NHWC". Specify the data format of the input and output data.
*@par Outputs:
 * y: A Tensor. Has the same type as x
*@par Third-party framework compatibility
 * Compatible with Tensorflow's conv2d_backprop_filter
*/
REG_OP(Conv2DBackpropFilter)
    .INPUT(x, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .INPUT(filter_size, TensorType({DT_INT32}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(Conv2DBackpropFilter)

/**
*@brief Computes the gradients of convolution with respect to the filter.
*@par Inputs:
 * Two inputs:
 * @li x: A Tensor. Type is float16.
 * 4-D with shape [batch, in_height, in_width, in_channels] or [batch, in_channels, in_height, in_width].
 * @li out_backprop: A Tensor. Must have the same type as x. 4-D with shape [batch, out_height, out_width, out_channels]
 * or [batch, out_channels, out_height, out_width]. Gradients with respect to the output of the convolution.
*@par Attributes:
 * Six attributes:
 * @li filter_size: A Tensor of type integers. An integer vector representing the tensor shape of filter,
 * where filter is a 4-D tensor [filter_height, filter_width, in_channels, out_channels]
 * or [out_channels, filter_height, filter_width, in_channels] or [out_channels, in_channel, filter_height, filter_width].
 * @li strides: A tuple/list of 2 integers. The stride of the sliding window for H/W dimension.
 * @li pads: A tuple/list of 4 integers, [top, bottom, left, right] pads on feature map
 * @li dilations: A tuple/list of 4 integers, The dilation factor for each dimension of input, now only support [1,1,1,1].
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NHWC", "NCHW". Defaults to "NHWC". Specify the data format of the input and output data.
*@par Outputs:
 * y: A Tensor. Has the same type as x
*@par Third-party framework compatibility
 * Compatible with Tensorflow's conv2d_backprop_filter
*/
REG_OP(Conv2DBackpropFilterD)
    .INPUT(x, TensorType({DT_FLOAT16}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16}))
    .OUTPUT(y, TensorType({DT_FLOAT}))
    .REQUIRED_ATTR(filter_size, ListInt)
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NHWC")
    .OP_END_FACTORY_REG(Conv2DBackpropFilterD)

/**
*@brief Computes a 2D convolution given 4D "x" and "filter" tensors.
*@par Inputs:
* @li x: A 4D tensor of input images.
* @li filter: A 4D tensor of filters.
* @li bias: An optional 1D tensor.
* @li offset_w: An optional 1D tensor for quantized convolution. Reserved.
* 
* The input and output tensor attributes are listed as follows:
* @verbatim
    |Tensor    | x       | filter  | bias    | offset_w | y
    -----------|---------|---------|---------|----------|--------
    |Data Type | float16 | float16 | float16 | _        | float16
    |          |---------|---------|---------|----------|--------
    |          | float32 | float32 | float32 | _        | float32
    |          |---------|---------|---------|----------|--------
    |          | int8    | int8    | int32   | int8     | int32
    -----------|---------|---------|---------|----------|--------
    |Format    | NCHW    | NCHW    | ND      | ND       | NCHW
    |          | NHWC    | NHWC    |         |          | NHWC
    |          |         | HWCN    |         |          |
@endverbatim
* It should be noted that the data types must correspond to each other, but the
* format does not need to.

*@par Attributes:
* @li strides: A list of 4 integers. Specifying the strides of the
* convolution along the height and width. The dimension order is determined
* by the data format of "x". By default the N and C dimensions are set to 1.
* @li pads: A list of 4 integers. Specifying the top, bottom, left and right
* padding.
* @li dilations: A list of 4 integers. Specifying the dilation rate to use
* for dilated convolution. Has the same dimension order and value as "strides".
* @li groups: Number of blocked connections from input channels to output
* channels. Input channels and output channels must both be divisible by
* "groups".Type is int32.
* @li offset_x: An optional integer for quantized convolution. Type is int32. Defaults to "0".
* @li data_format: An optional string from: "NHWC", "NCHW". Specifying the
* data format of the input and output images. Type is string. Defaults to "NHWC". Reserved.

*@par Outputs:
* @li y: A 4D Tensor of output images.

*@attention
* @li The parameter scope is listed as follows:
* @verbatim
    |Name             | Field        | Scope
    ------------------|--------------|----------
    |Input Image Size | H dimension  | [1, 4096]
    |                 | W dimension  | [1, 4096]
    ------------------|--------------|----------
    |Filter Size      | H dimension  | [1, 255]
    |                 | W dimension  | [1, 255]
    ------------------|--------------|----------
    |Stride Size      | H dimension  | [1, 63]
    |                 | W dimension  | [1, 63]
    ------------------|--------------|----------
    |Padding Size     | top side     | [0, 255]
    |                 | bottom side  | [0, 255]
    |                 | left side    | [0, 255]
    |                 | right side   | [0, 255]
    ------------------|--------------|----------
    |Dilation Size    | H dimension  | [1, 255]
                      | W dimension  | [1, 255]
@endverbatim

* @li There are restrictions for certain scenarios:
* @verbatim
     Output           | Restrictions
    ------------------|----------------------------------------------
     W dimension == 1 | HxW(input) == HxW(filter)
     H dimension == 1 |
    ------------------|----------------------------------------------
     W dimension == 1 | Not supported
     H dimension != 1 |
@endverbatim
* As shown above, "HxW(input)" indicates the image size after padding and
* "HxW(filter)" indicates the filter size after dilation.

*@par Quantization supported or not
* Yes

*@par Third-party framework compatibility
*@li Compatible with the TensorFlow operator "conv2d".
*@li Compatible with the Caffe operator 2D "Convolution".
*/
REG_OP(Conv2D)
    .INPUT(x, TensorType({DT_FLOAT16, DT_FLOAT, DT_INT8}))
    .INPUT(filter, TensorType({DT_FLOAT16, DT_FLOAT, DT_INT8}))
    .OPTIONAL_INPUT(bias, TensorType({DT_FLOAT16, DT_FLOAT, DT_INT32}))
    .OPTIONAL_INPUT(offset_w, TensorType({DT_INT8}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_INT32}))
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NHWC")
    .ATTR(offset_x, Int, 0)
    .OP_END_FACTORY_REG(Conv2D)

REG_OP(Conv2DCompress)
    .INPUT(x, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE, DT_INT8}))
    .INPUT(filter_compress, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE, DT_INT8}))
    .INPUT(compress_index, TensorType({DT_INT8}))
    .OPTIONAL_INPUT(bias, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE, DT_INT32}))
    .OPTIONAL_INPUT(offset_w, TensorType({DT_INT8}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE, DT_INT32}))
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NHWC")
    .ATTR(offset_x, Int, 0)
    .OP_END_FACTORY_REG(Conv2DCompress)

/**
*@brief Computes a 3D convolution given 5D "x" and "filter" tensors.
 *@par Inputs:
 * @li x: A 5D tensor. Must be one of the following types: float16, float32, float64. The format is NCDHW or NDHWC.
 * @li filter: A 5D tensor of the same type as "x". The format is NCDHW, NDHWC or DHWCN.

*@par Optional input:
 * @li bias: An optional 1D tensor of the same type as "x".
 * @li offset_w: An optional 1D tensor for quantized deconvolution. Reserved.

*@par Required Attributes:
* @li strides: A list of 5 ints. Specifies the stride of the sliding window for each dimension of "x". The N and C dimensions must be 1. Has the same format as "x".
* @li pads: A list of 6 ints. Supports only padding along the D, H and W dimensions in sequence of head, tail, top, bottom, left and right.

*@par Attributes:
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NDHWC", "NCDHW". Defaults to "NDHWC". Specify the data format of the input and output data.
 * @li dilations: A list of 5 ints. Specifies the dilation factor for each dimension of "x". The N and C dimensions must be 1. Has the same format as "x".
 * @li offset_x: An optional int. Input offset, used for quantized inference. Defaults to 0.

*@par Outputs:
 *y: A Tensor. Has the same type as "x".

*@attention Constraints:
 *The image size after padding is greater than the filter size.

*@par Third-party framework compatibility
 * @li Compatible with the TensorFlow operator conv3d.
 * @li Compatible with the Caffe operator Convolution.
*/
REG_OP(Conv3D)
    .INPUT(x, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .INPUT(filter, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .OPTIONAL_INPUT(bias, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .OPTIONAL_INPUT(offset_w, TensorType({DT_INT8}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NDHWC")
    .ATTR(offset_x, Int, 0)
    .OP_END_FACTORY_REG(Conv3D)

/**
*@brief Computes the gradients of convolution 3d with respect to the input.
*@par Inputs:
 * Three inputs:
 * @li input_size: A Tensor of type int32, int64. An integer vector representing the shape of input,
 * where input is a 5-D tensor [batch, depth, height, width, channels] or [batch, channels, depth, height, width].
 * @li filter: A Tensor. Must be one of the following types: float16, float32, float64.
 * @li out_backprop: A Tensor. Must have the same type as filter. 5-D with shape [batch, depth, out_height, out_width, out_channels]
 * or [batch, out_channels, depth, out_height, out_width]. Gradients with respect to the output of the convolution.

*@par Required Attributes:
 * @li strides: A list of 5 ints. Specifies the stride of the sliding window for each dimension of "x". The N and C dimensions must be 1. Has the same format as "x".
 * @li pads: A list of 6 ints. Supports only padding along the D, H and W dimensions in sequence of head, tail, top, bottom, left and right.

*@par Attributes:
 * Three attributes:
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NDHWC", "NCHWD". Defaults to "NDHWC". Specify the data format of the input and output data.
 * @li dilations: A tuple/list of 6 integers, The dilation factor for each dimension of input, now only support [1,1,1,1,1]

*@par Outputs:
 * y: A Tensor. Has the same type as filter,and has same format as input_size

*@par Third-party framework compatibility
 * Compatible with Tensorflow's conv3d_backprop_input
*/
REG_OP(Conv3DBackpropInput)
    .INPUT(input_size, TensorType({DT_INT32, DT_INT64}))
    .INPUT(filter, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NDHWC")
    .OP_END_FACTORY_REG(Conv3DBackpropInput)

/**
*@brief Computes the gradients of convolution 3d with respect to the input.
*@par Inputs:
 * Two inputs:
 * @li filter: A Tensor. Types is float16.
 * @li out_backprop: A Tensor. Must have the same type as filter.

*@par Required Attributes:
 *@li strides: A list of 5 ints. Specifies the stride of the sliding window for
  each dimension of "x". The N and C dimensions must be 1. Has the same format as "x".
 *@li pads: A list of 6 ints. Supports only padding along the D, H and W
 dimensions in sequence of head, tail, top, bottom, left and right.
 *@li input_size: A Tensor of type int32, int64. An integer vector representing the shape of input,
 * where input is a 5-D tensor [batch, depth, height, width, channels] or [batch, channels, depth, height, width].

*@par Attributes:
 * Three attributes:
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NDHWC", "NCHWD". Defaults to "NDHWC". Specify the data format of the input and output data.
 * @li dilations: A tuple/list of 5 integers, The dilation factor for each dimension of input, now only support [1,1,1,1,1]
*@par Outputs:
 * y: A Tensor. Has the same type as filter
*@par Third-party framework compatibility
 * Compatible with Tensorflow's conv3d_backprop_input
*/


REG_OP(Conv3DBackpropInputD)
    .INPUT(filter, TensorType({DT_FLOAT16}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16}))
    .OUTPUT(y, TensorType({DT_FLOAT16}))
    .REQUIRED_ATTR(input_size, ListInt)
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NDHWC")
    .OP_END_FACTORY_REG(Conv3DBackpropInputD)

REG_OP(LSTM)
    .INPUT(x, TensorType({DT_FLOAT16}))
    .INPUT(cont, TensorType({DT_FLOAT32,DT_FLOAT16}))
    .INPUT(w_x, TensorType({DT_FLOAT16}))
    .INPUT(bias, TensorType({DT_FLOAT16,DT_FLOAT32,DT_INT16,DT_INT32}))
    .INPUT(w_h, TensorType({DT_FLOAT16}))
    .OPTIONAL_INPUT(x_static, TensorType({DT_FLOAT16}))
    .OPTIONAL_INPUT(h_0, TensorType({DT_FLOAT16,DT_FLOAT32}))
    .OPTIONAL_INPUT(c_0, TensorType({DT_FLOAT16,DT_FLOAT32}))
    .OPTIONAL_INPUT(w_x_static, TensorType({DT_FLOAT16}))
    .OUTPUT(h, TensorType({DT_FLOAT16, DT_FLOAT}))
    .OUTPUT(h_t, TensorType({DT_FLOAT16, DT_FLOAT}))
    .OUTPUT(c_t, TensorType({DT_FLOAT16, DT_FLOAT}))
    .ATTR(num_output, Int, 0)
    .ATTR(expose_hidden, Bool, false)
    .OP_END_FACTORY_REG(LSTM)

/**
*@brief Computes the gradients of convolution3D with respect to the filter
*@par Inputs:
 * Three inputs:
 * @li x: A Tensor. Must be one of the following types: float16
 * 5-D with shape [batch, in_depth, in_height, in_width, in_channels] or [batch, in_depth, in_channels, in_height, in_width].
 * @li filter_size: A Tensor of type int32. An integer vector representing the tensor shape of filter,
 * where filter is a 5-D tensor [filter_depth, filter_height, filter_width, in_channels, out_channels]
 * or [out_channels, filter_depth, filter_height, filter_width, in_channels] or [out_channels, filter_depth, in_channel, filter_height, filter_width].
 * @li out_backprop: A Tensor. Must have the same type as x. 5-D with shape [batch, out_depth, out_height, out_width, out_channels]
 * or [batch, out_depth, out_channels, out_height, out_width]. Gradients with respect to the output of the convolution.
*@par Attributes:
 * Three attributes:
 * @li strides: A tuple/list of 3 integers. The stride of the sliding window for D/H/W dimension.
 * @li pads: A tuple/list of 6 integers, [front, back, top, bottom, left, right] pads on feature map.
 * @li dilations: A tuple/list of 5 integers, The dilation factor for each dimension of input, now only support [1,1,1,1,1].
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NDHWC", "NDCHW". Defaults to "NDHWC". Specify the data format of the input and output data.
*@par Outputs:
 * y: A Tensor. Has the same type as x
*@par Third-party framework compatibility
 * Compatible with Tensorflow's conv3d_backprop_filter
*/
REG_OP(Conv3DBackpropFilter)
    .INPUT(x, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .INPUT(filter_size, TensorType({DT_INT32}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NDHWC")
    .OP_END_FACTORY_REG(Conv3DBackpropFilter)

/**
*@brief Computes the gradients of convolution with respect to the filter.
*@par Inputs:
 * Two inputs:
 * @li x: A Tensor. Type is float16.
 * 5-D with shape [batch, in_depth, in_height, in_width, in_channels] or [batch, in_depth, in_channels, in_height, in_width].
 * @li out_backprop: A Tensor. Must have the same type as x. 5-D with shape [batch, out_depth, out_height, out_width, out_channels]
 * or [batch, out_depth, out_channels, out_height, out_width]. Gradients with respect to the output of the convolution.
*@par Attributes:
 * Four attributes:
 * @li filter_size: A Tensor of type integers. An integer vector representing the tensor shape of filter,
 * where filter is a 5-D tensor [filter_depth, filter_height, filter_width, in_channels, out_channels]
 * or [out_channels, filter_depth, filter_height, filter_width, in_channels] or [out_channels, filter_depth, in_channel, filter_height, filter_width].
 * @li strides: A tuple/list of 3 integers. The stride of the sliding window for D/H/W dimension.
 * @li pads: A tuple/list of 6 integers, [front, back, top, bottom, left, right] pads on feature map
 * @li dilations: A tuple/list of 5 integers, The dilation factor for each dimension of input, now only support [1,1,1,1,1].
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NDHWC", "NDCHW". Defaults to "NDHWC". Specify the data format of the input and output data.
*@par Outputs:
 * y: A Tensor. Has the same type as x
*@par Third-party framework compatibility
 * Compatible with Tensorflow's conv3d_backprop_filter
*/


REG_OP(Conv3DBackpropFilterD)
    .INPUT(x, TensorType({DT_FLOAT16}))
    .INPUT(out_backprop, TensorType({DT_FLOAT16}))
    .OUTPUT(y, TensorType({DT_FLOAT}))
    .REQUIRED_ATTR(filter_size, ListInt)
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NDHWC")
    .OP_END_FACTORY_REG(Conv3DBackpropFilterD)

/**
*@brief Computes the transpose of convolution 3d with respect to the input.
*@par Inputs:
 * Five inputs:
 * @li input_size: A Tensor of type int32. An integer vector representing the shape of input
 * @li x: A Tensor.
 * @li filter: A Tensor. Types is float16.
 * @li bias: An optional 1D tensor of the same type as "x".
 * @li offset_w: An optional 1D tensor for quantized deconvolution. Reserved.

*@par Required Attributes:
 * @li strides: A tuple/list of 3 integers. The stride of the sliding window for D/H/W dimension.
 * @li pads: A tuple/list of 6 integers
*@par Attributes:
 * Five attributes:
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li dilations: A tuple/list of 5 integers, The dilation factor for each dimension of input, now only support [1,1,1,1,1]
 * @li data_format: An optional string from: "NDHWC", "NCHWD". Defaults to "NDHWC". Specify the data format of the input and output data.
 * @li output_padding: The size will be added in the output shape.
 * @li offset_x: Input offset_x value
*@par Outputs:
 * y: A Tensor. Has the same type as filter
*/
REG_OP(Conv3DTranspose)
    .INPUT(input_size, TensorType({DT_INT32, DT_INT64}))
    .INPUT(x, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .INPUT(filter, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .OPTIONAL_INPUT(bias, TensorType({DT_FLOAT16}))
    .OPTIONAL_INPUT(offset_w, TensorType({DT_INT8}))
    .OUTPUT(y, TensorType({DT_FLOAT16, DT_FLOAT, DT_DOUBLE}))
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NDHWC")
    .ATTR(output_padding, ListInt, {0, 0, 0, 0, 0})
    .ATTR(offset_x, Int, 0)
    .OP_END_FACTORY_REG(Conv3DTranspose)

/**
*@brief Computes the transpose of convolution 3d with respect to the input.
*@par Inputs:
 * Four inputs:
 * @li x: A Tensor.
 * @li filter: A Tensor. Types is float16.
 * @li bias: An optional 1D tensor of the same type as "x".
 * @li offset_w: An optional 1D tensor for quantized deconvolution. Reserved.

*@par Required Attributes:
 * @li input_size: A Tensor of type int32. An integer vector representing the shape of input
 * @li strides: A tuple/list of 3 integers. The stride of the sliding window for D/H/W dimension.
 * @li pads: A tuple/list of 6 integers
*@par Attributes:
 * Five attributes:
 * @li dilations: A tuple/list of 5 integers, The dilation factor for each dimension of input, now only support [1,1,1,1,1]
 * @li groups: Number of blocked connections from input channels to output channels.
 * @li data_format: An optional string from: "NDHWC", "NCHWD". Defaults to "NDHWC". Specify the data format of the input and output data.
 * @li output_padding: The size will be added in the output shape.
 * @li offset_x: Input offset_x value
*@par Outputs:
 * y: A Tensor. Has the same type as filter
*/


REG_OP(Conv3DTransposeD)
    .INPUT(x, TensorType({DT_FLOAT16}))
    .INPUT(filter, TensorType({DT_FLOAT16}))
    .OPTIONAL_INPUT(bias, TensorType({DT_FLOAT16}))
    .OPTIONAL_INPUT(offset_w, TensorType({DT_INT8}))
    .OUTPUT(y, TensorType({DT_FLOAT16}))
    .REQUIRED_ATTR(input_size, ListInt)
    .REQUIRED_ATTR(strides, ListInt)
    .REQUIRED_ATTR(pads, ListInt)
    .ATTR(dilations, ListInt, {1, 1, 1, 1, 1})
    .ATTR(groups, Int, 1)
    .ATTR(data_format, String, "NDHWC")
    .ATTR(output_padding, ListInt, {0, 0, 0, 0, 0})
    .ATTR(offset_x, Int, 0)
    .OP_END_FACTORY_REG(Conv3DTransposeD)

}  // namespace ge
#endif  // GE_OP_NN_CALCULATION_OPS_H
