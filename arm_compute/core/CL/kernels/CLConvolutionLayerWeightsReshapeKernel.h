/*
 * Copyright (c) 2017 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __ARM_COMPUTE_CLCONVOLUTIONLAYERWEIGHTSRESHAPEKERNEL_H__
#define __ARM_COMPUTE_CLCONVOLUTIONLAYERWEIGHTSRESHAPEKERNEL_H__

#include "arm_compute/core/CL/ICLKernel.h"

namespace arm_compute
{
/** Interface for the weights reshape kernel used by convolution and fully connected layers.
 *
 * Rearranges each 3-dimensional kernel to a single row leading to a matrix with linearized kernels.
 * In combination with the @ref CLIm2ColKernel can transform a convolution into a matrix multiplication.
 *
 * For example assuming a 3D weight kernel of 3x3 dimensions and depth of 2 we have:
 * @f[
 * \left( \begin{array}{ccc}
 * a000 & a001 & a002 \\
 * a010 & a011 & a012 \\
 * a020 & a021 & a022 \\
 * \end{array} \right)
 * \left( \begin{array}{ccc}
 * a100 & a101 & a102 \\
 * a110 & a111 & a112 \\
 * a120 & a121 & a122 \\
 * \end{array} \right)
 * \rightarrow
 * \left( \begin{array}{ccccccccc}
 * a000 & a001 & a002 & a010 & a011 & a012 & a020 & a021 & a022 & a100 & a101 & a102 & a110 & a111 & a112 & a120 & a121 & a122 \\
 * \end{array} \right)
 * @f]
 */
class CLConvolutionLayerWeightsReshapeKernel : public ICLKernel
{
public:
    /** Default constructor */
    CLConvolutionLayerWeightsReshapeKernel();
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    CLConvolutionLayerWeightsReshapeKernel(const CLConvolutionLayerWeightsReshapeKernel &) = delete;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    CLConvolutionLayerWeightsReshapeKernel &operator=(const CLConvolutionLayerWeightsReshapeKernel &) = delete;
    /** Allow instances of this class to be moved */
    CLConvolutionLayerWeightsReshapeKernel(CLConvolutionLayerWeightsReshapeKernel &&) = default;
    /** Allow instances of this class to be moved */
    CLConvolutionLayerWeightsReshapeKernel &operator=(CLConvolutionLayerWeightsReshapeKernel &&) = default;
    /** Default destructor */
    ~CLConvolutionLayerWeightsReshapeKernel() = default;

    /** Set the input and output of the kernel.
     *
     * @param[in]  input  The input tensor to convert. Weights are 4D tensor with dimensions [kernel_x, kernel_y, IFM, OFM].  Data types supported: F16, F32
     * @param[in]  biases The shared biases tensor to append.  Bias is 1D tensor with dimensions [OFM]. Data types supported: Same as @p input
     * @param[out] output The output tensor. Should be a 2D Tensor. Data types supported: Same as @p input
     */
    void configure(const ICLTensor *input, const ICLTensor *biases, ICLTensor *output);

    // Inherited methods overridden:
    void run(const Window &window, cl::CommandQueue &queue) override;

private:
    const ICLTensor *_input;
    const ICLTensor *_biases;
    ICLTensor       *_output;
};
}
#endif /*__ARM_COMPUTE_CLCONVOLUTIONLAYERWEIGHTSRESHAPEKERNEL_H__ */
