/* Generated by wayland-scanner 1.18.0 */

/*
 * Copyright © 2008-2011 Kristian Høgsberg
 * Copyright © 2010-2011 Intel Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this
 * software and its documentation for any purpose is hereby granted
 * without fee, provided that\n the above copyright notice appear in
 * all copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the name of
 * the copyright holders not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied
 * warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
 * THIS SOFTWARE.
 */

#include <stdlib.h>
#include <stdint.h>
#include "wayland-util.h"

#ifndef __has_attribute
# define __has_attribute(x) 0  /* Compatibility with non-clang compilers. */
#endif

#if (__has_attribute(visibility) || defined(__GNUC__) && __GNUC__ >= 4)
#define WL_PRIVATE __attribute__ ((visibility("hidden")))
#else
#define WL_PRIVATE
#endif

extern const struct wl_interface wl_buffer_interface;

static const struct wl_interface *drm_types[] = {
	NULL,
	&wl_buffer_interface,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&wl_buffer_interface,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&wl_buffer_interface,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

static const struct wl_message wl_drm_requests[] = {
	{ "authenticate", "u", drm_types + 0 },
	{ "create_buffer", "nuiiuu", drm_types + 1 },
	{ "create_planar_buffer", "nuiiuiiiiii", drm_types + 7 },
	{ "create_prime_buffer", "2nhiiuiiiiii", drm_types + 18 },
};

static const struct wl_message wl_drm_events[] = {
	{ "device", "s", drm_types + 0 },
	{ "format", "u", drm_types + 0 },
	{ "authenticated", "", drm_types + 0 },
	{ "capabilities", "u", drm_types + 0 },
};

WL_PRIVATE const struct wl_interface wl_drm_interface = {
	"wl_drm", 2,
	4, wl_drm_requests,
	4, wl_drm_events,
};

