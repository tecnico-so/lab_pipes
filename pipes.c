#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE (128)

int child_main(int rx) {
    while (true) {
        char buffer[BUFFER_SIZE];
        ssize_t ret = read(rx, buffer, BUFFER_SIZE - 1);

        if (ret == 0) {
            // ret == 0 signals EOF
            fprintf(stderr, "[INFO]: parent closed the pipe\n");
            break;
        } else if (ret == -1) {
            // ret == -1 signals error
            fprintf(stderr, "[ERR]: read failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        fprintf(stderr, "[INFO]: parent sent %zd B\n", ret);
        buffer[ret] = 0;
        fputs(buffer, stdout);
    }

    close(rx);
    return 0;
}

// helper function to send messages
// retries to send whatever was not sent in the begginning
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

int parent_main(int tx) {
    // The parent is likes classic rock:
    // https://www.youtube.com/watch?v=lrpXArn3hII
    send_msg(tx, "Hey little girl\n");
    send_msg(tx, "Is your daddy home?\n");
    send_msg(tx, "Did he go and leave you all alone?\n");

    fprintf(stderr, "[INFO]: closing pipe\n");
    close(tx);

    // parent waits for the child
    wait(NULL);
    return 0;
}

int main() {
    int filedes[2];
    if (pipe(filedes) != 0) {
        fprintf(stderr, "[ERR]: pipe() failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (fork() == 0) {
        // we need to close the ends we are not using
        // otherwise, the child will be perpetually waiting for a message that
        // will never come
        close(filedes[1]);
        return child_main(filedes[0]);
    } else {
        close(filedes[0]);
        return parent_main(filedes[1]);
    }
}
