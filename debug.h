/* debug.h -- debug utilities
 *
 * Copyright (C) 2011--2012 Olaf Bergmann <bergmann@tzi.org>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "config.h"
#include "global.h"
#include <stdlib.h>

struct __session_t;

/** Pre-defined log levels akin to what is used in \b syslog. */
typedef enum { LOG_EMERG=0, LOG_ALERT, LOG_CRIT, LOG_WARN, 
       LOG_NOTICE, LOG_INFO, LOG_DEBUG
} log_t;

#ifndef NDEBUG
/** Returns the current log level. */
log_t dtls_get_log_level();

/** Sets the log level to the specified value. */
void dtls_set_log_level(log_t level);

/** 
 * Writes the given text to \c stdout. The text is output only when \p
 * level is below or equal to the log level that set by
 * set_log_level(). */
void dsrv_log(log_t level, char *format, ...);

/** dumps packets in usual hexdump format */
void hexdump(const unsigned char *packet, int length);

/** dump as narrow string of hex digits */
void dump(unsigned char *buf, size_t len);

void dtls_dsrv_hexdump_log(log_t level, const char *name, const unsigned char *buf, size_t length, int extend);

void dtls_dsrv_log_addr(log_t level, const char *name, const session_t *addr);

#else /* NDEBUG */

static inline log_t dtls_get_log_level()
{
  return LOG_EMERG;
}

static inline void dtls_set_log_level(log_t level)
{}

static inline void dsrv_log(log_t level, char *format, ...)
{}

static inline void hexdump(const unsigned char *packet, int length)
{}

static inline void dump(unsigned char *buf, size_t len)
{}

static inline void
dtls_dsrv_hexdump_log(log_t level, const char *name, const unsigned char *buf, size_t length, int extend)
{}

static inline void
dtls_dsrv_log_addr(log_t level, const char *name, const struct __session_t *addr)
{}

#endif /* NDEBUG */

/* A set of convenience macros for common log levels. */
#define info(...) dsrv_log(LOG_INFO, __VA_ARGS__)
#define warn(...) dsrv_log(LOG_WARN, __VA_ARGS__)
#define debug(...) dsrv_log(LOG_DEBUG, __VA_ARGS__)

#endif /* _DEBUG_H_ */
