#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE (128)

int child_main(int fd) {
    while (1) {
        char buffer[BUFFER_SIZE + 1];
        ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);

        if (bytes_read == 0) {
            /* if read() returns 0, it reached EOF */
            fprintf(stderr, "[INFO](child): parent closed the pipe\n");
            break;
        } else if (bytes_read == -1) {
            /* read() returning -1 signals an error occurred */
            perror("[ERR](child): read failed");
            return EXIT_FAILURE;
        }

        fprintf(stderr, "[INFO](child): parent sent %zdB\n", bytes_read);

        buffer[bytes_read] = '\0';
        fputs(buffer, stdout);
    }

    close(fd);
    return EXIT_SUCCESS;
}

/**
 * helper function to send messages
 */
void send_msg(int fd, char const *str) {
    size_t len = strlen(str);
    size_t bytes_written = 0;

    while (bytes_written < len) {
        ssize_t ret = write(fd, str + bytes_written, len - bytes_written);

        if (ret < 0) {
            perror("[ERR](parent): write failed");
            exit(EXIT_FAILURE);
        }

        bytes_written += ret;
    }

    fprintf(stderr, "[INFO](parent): message sent. waiting ack.\n");
}

int parent_main(int fd) {
    /**
     * the parent likes dad rock :)
     * https://www.youtube.com/watch?v=btPJPFnesV4
     */
    send_msg(fd, "It's the eye of the tiger\n");
    send_msg(fd, "It's the thrill of the fight\n");
    send_msg(fd, "Rising up to the challenge of our rival\n");

    fprintf(stderr, "[INFO](parent): closing pipe\n");
    close(fd);

    /* parent waits for the child */
    wait(NULL);
    return EXIT_SUCCESS;
}

int main() {
    int fildes[2];
    if (pipe(fildes) == -1) {
        perror("[ERR](main): pipe() failed");
        return EXIT_FAILURE;
    }

    if (fork() == 0) {
        /**
         * we need to close the ends we are not using, otherwise, the child will
         * be perpetually waiting for a message that will never come
         */
        close(fildes[1]);
        return child_main(fildes[0]);
    } else {
        close(fildes[0]);
        return parent_main(fildes[1]);
    }
}
