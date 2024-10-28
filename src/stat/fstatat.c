// SPDX-License-Identifier: BSD-3-Clause

#include <sys/stat.h>
#include <internal/types.h>
#include <unistd.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

#define makedev(x, y) ( \
        (((x)&0xfffff000ULL) << 32) | \
    (((x)&0x00000fffULL) << 8) | \
        (((y)&0xffffff00ULL) << 12) | \
    (((y)&0x000000ffULL)) \
    )

/* Structure describing file characteristics as defined in linux/stat.h */
struct statx {
	uint32_t stx_mask;
	uint32_t stx_blksize;
	uint64_t stx_attributes;
	uint32_t stx_nlink;
	uint32_t stx_uid;
	uint32_t stx_gid;
	uint16_t stx_mode;
	uint16_t pad1;
	uint64_t stx_ino;
	uint64_t stx_size;
	uint64_t stx_blocks;
	uint64_t stx_attributes_mask;
	struct {
		int64_t tv_sec;
		uint32_t tv_nsec;
		int32_t pad;
	} stx_atime, stx_btime, stx_ctime, stx_mtime;
	uint32_t stx_rdev_major;
	uint32_t stx_rdev_minor;
	uint32_t stx_dev_major;
	uint32_t stx_dev_minor;
	uint64_t spare[14];
};

// I have no idea if this works
int fstatat_statx(int fd, const char *restrict path, struct stat *restrict st,
				  int flag) {
	struct statx buffer;
	long err = syscall(__NR_statx, fd, path, flag, &buffer);
	if (err != 0) {
		errno = -err;
		return -1;
	}

	st->st_atime = buffer.stx_atime.tv_sec;
	st->st_atime_nsec = buffer.stx_atime.tv_nsec;
	st->st_blksize = buffer.stx_blksize;
	st->st_blocks = buffer.stx_blocks;
	st->st_ctime = buffer.stx_ctime.tv_sec;
	st->st_ctime_nsec = buffer.stx_ctime.tv_nsec;
	st->st_gid = buffer.stx_gid;
	st->st_ino = buffer.stx_ino;
	st->st_mode = buffer.stx_mode;
	st->st_mtime = buffer.stx_mtime.tv_sec;
	st->st_mtime_nsec = buffer.stx_mtime.tv_nsec;
	st->st_nlink = buffer.stx_nlink;
	st->st_size = buffer.stx_size;
	st->st_uid = buffer.stx_uid;
	st->st_dev = makedev(buffer.stx_dev_major, buffer.stx_dev_minor);
	st->st_rdev = makedev(buffer.stx_rdev_major, buffer.stx_rdev_minor);

	return 0;
}

int
fstatat(int fd, const char *restrict path, struct stat *restrict st, int flag) {
	return fstatat_statx(fd, path, st, flag);
}
