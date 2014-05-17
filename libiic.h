/*-
 * Copyright (c) 2014 Rui Paulo <rpaulo@felyko.com>                        
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _LIBIIC_H_
#define _LIBIIC_H_

#include <sys/types.h>
#include <sys/iic.h>

__BEGIN_DECLS

#define	IIC_INVALID_HANDLE	-1
typedef int iic_handle_t;

iic_handle_t	iic_open(unsigned int);
iic_handle_t	iic_open_device(const char *);
void		iic_close(iic_handle_t);

int		iic_read_1(iic_handle_t, int, uint8_t *);
int		iic_read_2(iic_handle_t, int, uint16_t *);
int		iic_read_2_le(iic_handle_t, int, uint16_t *);
int		iic_read_2_be(iic_handle_t, int, uint16_t *);
int		iic_read_4(iic_handle_t, int, uint32_t *);
int		iic_read_4_le(iic_handle_t, int, uint32_t *);
int		iic_read_4_be(iic_handle_t, int, uint32_t *);
int		iic_read_8(iic_handle_t, int, uint64_t *);
int		iic_read_8_le(iic_handle_t, int, uint64_t *);
int		iic_read_8_be(iic_handle_t, int, uint64_t *);
int		iic_read_n(iic_handle_t, int, void *, size_t);
int		iic_read_n_le(iic_handle_t, int, void *, size_t);
int		iic_read_n_be(iic_handle_t, int, void *, size_t);

int		iic_write_1(iic_handle_t, int, uint8_t);
int		iic_write_2(iic_handle_t, int, uint16_t);
int		iic_write_4(iic_handle_t, int, uint32_t);
int		iic_write_8(iic_handle_t, int, uint64_t);
int		iic_write_n(iic_handle_t, int, void *, size_t);

int		iic_reset(iic_handle_t);

__END_DECLS

#endif /* _LIBIIC_H_ */
