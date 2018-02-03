#ifndef CPSRDEC_H
#define CPSRDEC_H

#define PMODE_USR  (0)
#define PMODE_FIQ  (1)
#define PMODE_IRQ  (2)
#define PMODE_SVC  (3)
#define PMODE_ABT  (7)
#define PMODE_UND  (11)
#define PMODE_SYS  (15)
#define PMODE_MASK (15)

#define EMODE_ARM     (0)
#define EMODE_THUMB   (0x20)
#define EMODE_JAZELLE (0x1000000)
#define EMODE_MASK    (0x1000020)


#define IFLAGS_FIQ  (0x40)
#define IFLAGS_IRQ  (0x80)
#define IFLAGS_IMP  (0x100)

#define CFLAGS_V    (0x10000000)
#define CFLAGS_C    (0x20000000)
#define CFLAGS_Z    (0x40000000)
#define CFLAGS_N    (0x80000000)

#define OFLAGS_END  (0x200)
#define OFLAGS_Q    (0x8000000)

#endif
