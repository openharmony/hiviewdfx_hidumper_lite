/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "parse_dump_uint64.h"

#include <charconv>
#include <cstring>
#include <system_error>

extern "C" bool ParseDumpUint64(const char *text, uint64_t *out)
{
    if (text == nullptr || out == nullptr || *text == '\0') {
        return false;
    }
    const char *first = text;
    const char *last = text + std::strlen(text);
    if ((last - first) >= 2 && first[0] == '0' && (first[1] == 'x' || first[1] == 'X')) {
        first += 2;
    }
    if (first == last) {
        return false;
    }
    uint64_t value = 0;
    auto result = std::from_chars(first, last, value, 16);
    if (result.ec != std::errc() || result.ptr != last) {
        return false;
    }
    *out = value;
    return true;
}
