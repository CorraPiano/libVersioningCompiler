/* Copyright 2017 Politecnico di Milano.
 * Developed by : Stefano Cherubin
 *                PhD student, Politecnico di Milano
 *                <first_name>.<family_name>@polimi.it
 *
 * This file is part of libVersioningCompiler
 *
 * libVersioningCompiler is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * libVersioningCompiler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libVersioningCompiler. If not, see <http://www.gnu.org/licenses/>
 */
#include "versioningCompiler/Utils.hpp"

#include <iostream>
#include <stdlib.h>
#include <cmath>

#ifndef FORCED_PATH_TO_TEST
#define FORCED_PATH_TO_TEST "../libVersioningCompiler/test_code"
#endif
#define PATH_TO_C_TEST_CODE FORCED_PATH_TO_TEST "/test_code.c"

#ifndef TEST_FUNCTION
#define TEST_FUNCTION "test_function"
#endif

// someone should provide the signature of the function now versioning
// in the form of function pointer type.
typedef float (*signature_t)(int);

using namespace vc; // libVersioningCompiler namespace

void checkResult(int result, int expected){
  if (std::fabs(result - expected) < 1e-5) {
    std::cout << "PASSED" << std::endl;
  }else{
    std::cout << "FAILED" << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  std::cout << "\n=== libVC_testUtils ===\n\n";
  std::cout << ">>> Test Configuration\n" 
            << "This test validates the basic utility interface of libVersioningCompiler.\n"
            << "- Initialize default system compiler and create version v using utility functions.\n"
            << "- Validate test_function(x) that computes x*x and stores the result in a global variable.\n";
  vc_utils_init();
  opt_list_t options;
  options.push_back(Option("O", "-O", "2"));
  options.push_back(Option("O", "-D", "TEST_FUNCTION"));
  version_ptr_t v = createVersion(PATH_TO_C_TEST_CODE, TEST_FUNCTION, options);
  signature_t fn_ptr = (signature_t)compileAndGetSymbol(v);
  std::cout << "\n>>> Test Case\n";
  if (fn_ptr){ 
    std::cout << "Test 01: Version v  --> test_function(3)\t";
    checkResult(fn_ptr(3),9);
  } else
    std::cerr << "Error: function pointer unavailable" << std::endl;
  return 0;
}
