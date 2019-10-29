/*
 * Copyright (c) 2019, NVIDIA CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <tests/utilities/column_wrapper.hpp>
#include <gtest/gtest.h>

namespace cudf {
namespace test {
namespace transformation {

template <typename TypeOut, typename TypeIn, typename TypeOpe>
void ASSERT_UNARY(cudf::test::fixed_width_column_wrapper<TypeOut>& out,
                  cudf::test::fixed_width_column_wrapper<TypeIn>& in,
                  TypeOpe&& ope) {
    auto in_h = in.to_host();
    auto in_data = in_h.first;
    auto out_h = out.to_host();
    auto out_data = out_h.first;

    ASSERT_TRUE(out_data.size() == in_data.size());
    
    auto data_comparator = [ope](const TypeIn& in, const TypeOut& out){
      EXPECT_EQ(out, static_cast<TypeOut>(ope(in)));
      return true;
    };
    std::equal(in_data.begin(), in_data.end(), out_data.begin(), data_comparator);
    
    auto in_valid = in_h.second;
    auto out_valid = out_h.second;
    
    ASSERT_TRUE(out_valid.size() == in_valid.size());
    auto valid_comparator = [](const bool& in, const bool& out){
      EXPECT_EQ(out, in);
      return true;
    };
    std::equal(in_valid.begin(), in_valid.end(), out_valid.begin(), valid_comparator);
}

}
}
}
