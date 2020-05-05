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

#ifndef GE_OP_OUTFEED_OPS_H
#define GE_OP_OUTFEED_OPS_H

#include "graph/operator.h"
#include "graph/operator_reg.h"

namespace ge {

/**
*@brief Enqueue a Tensor on the computation outfeed.

*@par Inputs:
*Inputs include: \n
*x: A Tensor. Must be one of the following types: float16, float32, \n
float64, int8, int16, uint16, uint8, int32, int64, uint32, uint64, \n
bool, double, string.

*@par Attributes:
*channel_name: name of operator channel, default "".

*@attention Constraints:\n
*-The implementation for OutfeedEnqueueOp on Ascend uses AICPU, with bad performance.\n

*/
REG_OP(OutfeedEnqueueOp)
  .DYNAMIC_INPUT(x, TensorType({DT_FLOAT, DT_FLOAT16, DT_INT8,
      DT_INT16, DT_UINT16, DT_UINT8, DT_INT32, DT_INT64, DT_UINT32,
      DT_UINT64, DT_BOOL, DT_DOUBLE, DT_STRING}))
  .ATTR(channel_name, String, "")
  .OP_END_FACTORY_REG(OutfeedEnqueueOp)

}  // namespace ge

#endif  // GE_OP_OUTFEED_OPS_H

