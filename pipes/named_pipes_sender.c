#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATHNAME "fifo.pipe"

/**
 * helper function to send messages
 * retries to send whatever was not sent in the beginning
 */
void send_msg(int fd, char const *str) {
    size_t len = strlen(str);
    size_t written = 0;

    while (written < len) {
        ssize_t ret = write(fd, str + written, len - written);
        if (ret < 0) {
            perror("[ERR]: write failed");
            exit(EXIT_FAILURE);
        }

        written += ret;
    }
}

int main() {
    /* remove pipe if it exists */
    if (unlink(FIFO_PATHNAME) != 0 && errno != ENOENT) {
        perror("[ERR]: unlink(%s) failed");
        exit(EXIT_FAILURE);
    }

    /* create pipe */
    if (mkfifo(FIFO_PATHNAME, 0640) != 0) {
        perror("[ERR]: mkfifo failed");
        exit(EXIT_FAILURE);
    }

    /**
     * open pipe for writing
     * this waits for someone to open it for reading
     */
    int tx = open(FIFO_PATHNAME, O_WRONLY);
    if (tx == -1) {
        perror("[ERR]: open failed");
        exit(EXIT_FAILURE);
    }

    /**
     * more dad rock :)
     * https://www.youtube.com/watch?v=lrpXArn3hII
     */
    send_msg(tx, "Tell me now, baby\n");
    send_msg(tx, "Is he good to you?\n");
    send_msg(tx, "Can he do to you the things that I do?\n");

    fprintf(stderr, "[INFO]: closing pipe\n");
    close(tx);
}
