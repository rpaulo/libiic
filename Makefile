LIB=	iic
SHLIB_MAJOR=1
SRCS=	iic.c
INCS=	libiic.h

CFLAGS+=-I${.CURDIR}

WARNS?=	3

#MAN=	libiic.3
#MLINKS

.include <bsd.lib.mk>
