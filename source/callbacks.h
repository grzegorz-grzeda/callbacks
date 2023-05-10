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
#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @defgroup callbacks Callbacks
 * @brief Simple and efficient C library for handling callbacks
 * @{
*/

/**
 * @brief Callback handler type
 * 
 * This is a callback pointer. 
 * @param[in] context pointer to some context passed during registration
 * @param[in] payload pointer to some payload associated with the event ID
*/
typedef void (*callback_handler_t)(void *context, void *payload);

/**
 * @brief Callback structure type
 * 
 * This is a declaration of the callbacks structure type. Use only by pointer.
*/
typedef struct callbacks callbacks_t;

/**
 * @brief Create the callbacks
*/
callbacks_t *create_callbacks(void);

/**
 * @brief Register an new callback handler
 *
 * @note This function is not thread safe! Consider registering all handlers in
 * the initialization part of your project.
 * 
 * @param[in] callbacks pointer to the callbacks object
 * @param[in] handler pointer to the actual callback handler
 * @param[in] context pointer to some context for the callback handler
 * @return true if registration was successfull
 * @return false if handler was invalid or no more memory to store it
*/
bool register_callback_handler(callbacks_t *callbacks, callback_handler_t handler, void *context);

/**
 * @brief Dispatch callbacks
 * 
 * It calls each handler registered.
 * @note This code is platform-agnostic. If this function was called from e.g. 
 * - ISR
 * - another thread
 * It is the handlers job to cross thread/interrupt barriers correctly (e.g. through queues, semaphores etc.). 
 * The handlers are being called in the `dispatch_callbacks` caller context.
 * 
 * @param[in] callbacks pointer to the callback object
 * @param[in] payload pointer to possible payload associated with the event ID
*/
void dispatch_callbacks(callbacks_t*callbacks, void *payload);

/**
 * @}
*/

#endif // CALLBACKS_H
