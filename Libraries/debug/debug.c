#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#if defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
    #define GETCHAR_PROTOTYPE int fgetc(FILE * f)
    #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#elif defined   (  __GNUC__  )
    #define GETCHAR_PROTOTYPE int __io_getchar (void)
    #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#endif

PUTCHAR_PROTOTYPE
{
    return ch;
}

GETCHAR_PROTOTYPE
{
    return 0;
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
    (void)file;
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        *ptr++ = __io_getchar();
    }
    return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
    (void)file;
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}

__attribute__((weak)) int _isatty(int fd)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 1;

    errno = EBADF;
    return 0;
}

__attribute__((weak)) int _close(int fd)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 0;

    errno = EBADF;
    return -1;
}

__attribute__((weak)) int _lseek(int fd, int ptr, int dir)
{
    (void)fd;
    (void)ptr;
    (void)dir;

    errno = EBADF;
    return -1;
}

__attribute__((weak)) int _fstat(int fd, struct stat *st)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
    {
        st->st_mode = S_IFCHR;
        return 0;
    }

    errno = EBADF;
    return 0;
}

__attribute__((weak)) int _getpid(void)
{
  errno = ENOSYS;
  return -1;
}

__attribute__((weak)) int _kill(pid_t pid, int sig)
{
    (void)pid;
    (void)sig;
    errno = ENOSYS;
    return -1;
}