/**
 * Copyright (c) 2023, Virus.V <virusv@live.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of SmartOCD nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * Copyright 2023 Virus.V <virusv@live.com>
 */

#ifndef SRC_COMPONENT_COMPONENT_H_
#define SRC_COMPONENT_COMPONENT_H_

#include "smartocd.h"

#include "Library/lua/src/lauxlib.h"
#include "Library/lua/src/lua.h"
#include "Library/lua/src/lualib.h"
#include "Library/misc/list.h"
//
typedef int (*ComponentInitFunc)(lua_State *L, void *opaque);

struct componentEntry {
  const char *name;
  ComponentInitFunc init;
  void *opaque;
  unsigned int priority;
  struct list_head entry;
};

enum componentPriority {
  COM_ADAPTER = 0x0 << 16,
};

void component_regist(struct componentEntry *c);
void component_init(lua_State *L);

/*
 * 注册组件
 * name：组件名
 * init：组件初始化函数
 * opaque：函数参数
 * com：组件类型
 * pri：组件初始化优先级
 */
#define COMPONENT_INIT(name, init, opaque, com, pri)                                                       \
  static struct componentEntry _component_item_##name = {                                                  \
      #name, init, opaque, (com) + (pri), {&_component_item_##name.entry, &_component_item_##name.entry}}; \
  void __attribute__((used, constructor)) _component_item_##name##_register(void) {                        \
    component_regist(&_component_item_##name);                                                             \
  }

#endif
