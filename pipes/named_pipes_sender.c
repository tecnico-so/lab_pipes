#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FIFO_PATHNAME "fifo.pipe"

// Helper function to send messages
// Retries to send whatever was not sent in the beginning
void send_msg(int tx, char const *str) {
    size_t len = strlen(str);
    size_t written = 0;

    while (written < len) {
        ssize_t ret = write(tx, str + written, len - written);
        if (ret < 0) {
            fprintf(stderr, "[ERR]: write failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        written += ret;
    }
}

int main() {
    // Remove pipe if it does not exist
    if (unlink(FIFO_PATHNAME) != 0 && errno != ENOENT) {
        fprintf(stderr, "[ERR]: unlink(%s) failed: %s\n", FIFO_PATHNAME,
                strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Create pipe
    if (mkfifo(FIFO_PATHNAME, 0640) != 0) {
        fprintf(stderr, "[ERR]: mkfifo failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Open pipe for writing
    // This waits for someone to open it for reading
    int tx = open(FIFO_PATHNAME, O_WRONLY);
    if (tx == -1) {
        fprintf(stderr, "[ERR]: open failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // The parent likes classic rock:
    // https://www.youtube.com/watch?v=Kc71KZG87X4
    send_msg(tx, "In the burning heart\n");
    send_msg(tx, "Just about to burst\n");
    send_msg(tx, "There's a quest for answers\n");

    fprintf(stderr, "[INFO]: closing pipe\n");
    close(tx);
}
