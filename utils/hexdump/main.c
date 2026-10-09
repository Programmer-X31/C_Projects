
#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define BYTES_PER_LINE 16

/*
 * Read up to capacity bytes.
 *
 * Returns:
 *   > 0 : number of bytes read
 *     0 : EOF before any bytes were read
 *    -1 : error
 *
 * If EOF occurs after some bytes have been read,
 * those bytes are returned normally.
 */
static ssize_t read_chunk(int fd, unsigned char *buffer,
                          size_t capacity)
{
    size_t total = 0;

    while (total < capacity) {
        ssize_t n = read(fd, buffer + total, capacity - total);

        if (n > 0) {
            total += (size_t)n;
        } else if (n == 0) {
            break;
        } else if (errno == EINTR) {
            continue;
        } else {
            return -1;
        }
    }

    return (ssize_t)total;
}

/* Print one line of hexadecimal and ASCII output. */
static void print_line(uint64_t offset,
                       const unsigned char *buffer,
                       size_t length)
{
    printf("%08" PRIx64 "  ", offset);

    for (size_t i = 0; i < BYTES_PER_LINE; i++) {
        if (i < length) {
            printf("%02x ", buffer[i]);
        } else {
            printf("   ");
        }

        if (i == 7) {
            putchar(' ');
        }
    }

    printf(" |");

    for (size_t i = 0; i < length; i++) {
        unsigned char c = buffer[i];

        if (c >= 0x20 && c <= 0x7e) {
            putchar(c);
        } else {
            putchar('.');
        }
    }

    printf("|\n");
}

int main(int argc, char *argv[])
{
    int fd = STDIN_FILENO;
    int close_fd = 0;
    uint64_t offset = 0;
    unsigned char buffer[BYTES_PER_LINE];

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [file|-]\n", argv[0]);
        return 1;
    }

    if (argc == 2 && argv[1][0] != '-') {
        fd = open(argv[1], O_RDONLY);

        if (fd == -1) {
            perror(argv[1]);
            return 1;
        }

        close_fd = 1;
    } else if (argc == 2 && argv[1][0] == '-' &&
               argv[1][1] != '\0') {
        fprintf(stderr, "Usage: %s [file|-]\n", argv[0]);
        return 1;
    }

    for (;;) {
        ssize_t n = read_chunk(fd, buffer, sizeof(buffer));

        if (n == -1) {
            perror("read");
            if (close_fd) {
                close(fd);
            }
            return 1;
        }

        if (n == 0) {
            break;
        }

        print_line(offset, buffer, (size_t)n);
        offset += (uint64_t)n;
    }

    if (close_fd && close(fd) == -1) {
        perror("close");
        return 1;
    }

    if (fflush(stdout) == EOF) {
        perror("stdout");
        return 1;
    }

    return 0;
}
