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
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <libiic.h>

iic_handle_t
iic_open(unsigned int unit)
{
	char device[16];

	snprintf(device, sizeof(device), "/dev/iic%d", unit);

	return iic_open_device(device);
}

iic_handle_t
iic_open_device(const char *device)
{
	int fd;
	
	fd = open(device, O_RDWR);
	if (fd < 0)
		return IIC_INVALID_HANDLE;

	return fd;
}

void
iic_close(iic_handle_t handle)
{
	close(handle);
}

int
iic_read_1(iic_handle_t handle, int slave, uint8_t *v)
{
	return iic_read_n(handle, slave, v, 1);
}

int
iic_read_2(iic_handle_t handle, int slave, uint16_t *v)
{
	return iic_read_n(handle, slave, v, 2);
}

int
iic_read_4(iic_handle_t handle, int slave, uint32_t *v)
{
	return iic_read_n(handle, slave, v, 4);
}

int
iic_read_8(iic_handle_t handle, int slave, uint64_t *v)
{
	return iic_read_n(handle, slave, v, 8);
}

int
iic_read_n(iic_handle_t handle, int slave, void *v, size_t n)
{
	struct iic_msg msg;
	struct iic_rdwr_data rdwr;

	bzero(&msg, sizeof(msg));
	bzero(&rdwr, sizeof(rdwr));

	msg.slave = slave;
	msg.flags = IIC_M_RD;
	msg.len = n;
	msg.buf = v;
	rdwr.nmsgs = 1;
	rdwr.msgs = &msg;

	return ioctl(handle, I2CRDWR, &rdwr);
}

int
iic_write_1(iic_handle_t handle, int slave, uint8_t v)
{
	return iic_write_n(handle, slave, &v, 1);
}

int
iic_write_2(iic_handle_t handle, int slave, uint16_t v)
{
	return iic_write_n(handle, slave, &v, 2);
}

int
iic_write_4(iic_handle_t handle, int slave, uint32_t v)
{
	return iic_write_n(handle, slave, &v, 4);
}

int
iic_write_8(iic_handle_t handle, int slave, uint64_t v)
{
	return iic_write_n(handle, slave, &v, 8);
}

int
iic_write_n(iic_handle_t handle, int slave, void *v, size_t n)
{
	struct iic_msg msg;
	struct iic_rdwr_data rdwr;

	bzero(&msg, sizeof(msg));
	bzero(&rdwr, sizeof(rdwr));

	msg.slave = slave;
	msg.flags = IIC_M_WR;
	msg.len = n;
	msg.buf = v;
	rdwr.nmsgs = 1;
	rdwr.msgs = &msg;

	return ioctl(handle, I2CRDWR, &rdwr);
}

int
iic_reset(iic_handle_t handle)
{
	struct iiccmd cmd;
	
	bzero(&cmd, sizeof(cmd));

	return (ioctl(handle, I2CRSTCARD, &cmd));
}
