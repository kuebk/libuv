/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "uv.h"
#include "task.h"
#include <unistd.h>

TEST_IMPL(affinity) {
  int pid = getpid();

  //are we running on 2 cores?
  char *core;
  int core_size;
  int result = uv_get_affinity(pid, &core, &core_size);

  ASSERT(result == 0);
  ASSERT(core_size == 2);
  ASSERT(core[0] == 0);
  ASSERT(core[1] == 1);

  free(core);

  //setting affinity to core 1
  char *core2 = (char *) malloc(sizeof(char) * 1);
  int core_size2 = 1;
  core2[0] = 1;
  int result2 = uv_set_affinity(pid, core2, core_size2);

  ASSERT(result2 == 0);

  free(core2);

  //veryfying
  char *core3;
  int core_size3;
  int result3 = uv_get_affinity(pid, &core3, &core_size3);

  ASSERT(result3 == 0);
  ASSERT(core_size3 == 1);
  ASSERT(core3[0] == 1);

  free(core3);

  return 0;
}
