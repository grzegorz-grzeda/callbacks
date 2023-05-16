/**
 * MIT License
 * Copyright (c) 2023 Grzegorz Grzęda
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
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
#include "callbacks.h"
#include "simple-list.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct callbacks_entry {
    callback_handler_t handler;
    void *context;
} callbacks_entry_t;

typedef struct callbacks {
    simple_list_t *list;
} callbacks_t;

callbacks_t *create_callbacks(void)
{
    callbacks_t *callbacks = calloc(1, sizeof(callbacks_t));
    if (callbacks) {
        callbacks->list = create_simple_list();
    }
    return callbacks;
}

bool register_callback_handler(callbacks_t *callbacks, callback_handler_t handler, void *context)
{
    if (!callbacks || !handler) {
        return false;
    }
    callbacks_entry_t *entry = calloc(1, sizeof(callbacks_entry_t));
    if (!entry) {
        return false;
    }
    entry->handler = handler;
    entry->context = context;
    append_to_simple_list(callbacks->list, entry);
    return true;
}

void dispatch_callbacks(callbacks_t *callbacks, void *payload)
{
    if (!callbacks) {
        return;
    }
    for (simple_list_iterator_t *it = simple_list_begin(callbacks->list); it; it = simple_list_next(it)) {
        callbacks_entry_t *entry = get_from_simple_list_iterator(it);
        entry->handler(entry->context, payload);
    }
}
