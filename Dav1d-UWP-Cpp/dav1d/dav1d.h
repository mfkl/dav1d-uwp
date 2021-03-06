/*
 * Copyright © 2018, VideoLAN and dav1d authors
 * Copyright © 2018, Two Orioles, LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __DAV1D_H__
#define __DAV1D_H__

#include "common.h"
#include "picture.h"
#include "data.h"

extern "C"
{
typedef struct Dav1dContext Dav1dContext;
typedef struct Dav1dRef Dav1dRef;

typedef struct Dav1dSettings {
    int n_frame_threads;
    int n_tile_threads;
    Dav1dPicAllocator allocator;
} Dav1dSettings;

/**
 * Get library version.
 */
DAV1D_API const char *dav1d_version(void);

/**
 * Initialize settings to default values.
 *
 * @param s Input settings context.
 */
DAV1D_API void dav1d_default_settings(Dav1dSettings *s);

/**
 * Allocate and open a decoder instance.
 *
 * @param c_out The decoder instance to open. To be used in iterative calls to
 *              dav1d_decode(). *c_out will be set to the allocated context.
 * @param     s Input settings context.
 *
 * @note The context must be freed using dav1d_close() when decoding is
 *       finished.
 *
 * @return 0 on success, or < 0 (a negative errno code) on error.
 */
DAV1D_API int dav1d_open(Dav1dContext **c_out, const Dav1dSettings *s);

/**
 * Decode one frame.
 *
 * @param   c Input decoder instance.
 * @param  in Input bitstream data. On success, the caller retains ownership of
 *            the input reference if the data was not fully consumed.
 * @param out Output frame. The caller assumes ownership of the returned
 *            reference.
 *
 * @return
 *         0: Success, and a frame is returned.
 *   -EAGAIN: Not enough data to output a frame. The fuction should be called
 *            again with new input.
 *   other negative errno codes: Error during decoding or because of invalid
 *                               passed-in arguments.
 *
 * @note To flush the decoder (i.e. all input is finished), feed it NULL input
 *       data until it returns -EAGAIN.
 */
DAV1D_API int dav1d_decode(Dav1dContext *c, Dav1dData *in, Dav1dPicture *out);

/**
 * Close a decoder instance and free all associated memory.
 *
 * @param c_out The decoder instance to close. *c_out will be set to NULL.
 */
DAV1D_API void dav1d_close(Dav1dContext **c_out);

/**
 * Flush all delayed frames in decoder, to be used when seeking.
 *
 * @param c Input decoder instance.
 */
DAV1D_API void dav1d_flush(Dav1dContext *c);
}
#endif /* __DAV1D_H__ */
