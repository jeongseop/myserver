#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024

int main(int argc, char *argv[]) {
    int ret;
    int fd, cfd;
    struct sockaddr_in ssin, csin;
    socklen_t socklen = sizeof(struct sockaddr);

    if (argc != 2) {
        printf("usage: %s [port]\n", argv[0]);
        exit(1);
    }
    memset(&ssin, 0, socklen);
    ssin.sin_family      = AF_INET;
    ssin.sin_port    = htons(atoi(argv[1]));
    ssin.sin_addr.s_addr = htonl(INADDR_ANY);

    /* socket, bind, listen */
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) { perror("socket"); exit(1); }
    ret = bind(fd, (struct sockaddr *)&ssin, socklen);
    if (ret == -1) { perror("bind"); exit(1); }
    ret = listen(fd, 5);
    if (ret == -1) { perror("listen"); exit(1); }

    int epfd;
    struct epoll_event ev;
    struct epoll_event evlist[MAX];

    /* epoll_create1 */
    epfd = epfd = epoll_create1(0);
    if (epfd == -1) { perror("epoll_create1"); exit(1); }
    /* epoll_ctl */
    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO; // for quit
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);
    if (ret == -1) { perror("epoll_ctl"); exit(1); }
    ev.data.fd = fd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    if (ret == -1) { perror("epoll_ctl"); exit(1); }

    int i, nfds;
    char buf[BUFSIZ];
    int buflen;

    for (;;) {
        /* epoll */
        nfds = epoll_wait(epfd, evlist, MAX, -1);
        if (ret == -1) { perror("epoll_wait"); exit(1); }

        for (i = 0; i < nfds; i++) {
            if (evlist[i].data.fd == STDIN_FILENO) {
                fgets(buf, BUFSIZ-1, stdin);
                if (!strcmp(buf, "quit\n") || !strcmp(buf, "exit\n")) {
                    close(fd);
                    exit(0);
                }
            }
            else if (evlist[i].data.fd == fd) {
                /* accept */
                cfd = accept(fd, (struct sockaddr *)&csin, &socklen);
                if (cfd == -1) { perror("accpet"); exit(1); }
                printf("\x1b[0;32m[*] aceept\x1b[0m\n");
                /* epoll_ctl */
                ev.events = EPOLLIN;
                ev.data.fd = cfd;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
                if (ret == -1) { perror("epoll_ctl"); exit(1); }
            }
            else {
                cfd = evlist[i].data.fd;
                /* read */
                buflen = read(cfd, buf, BUFSIZ-1);
                if (buflen == 0) {
                    /* close */
                    close(cfd);
                    if (cfd == -1) { perror("close"); exit(1); }
                    printf("\x1b[0;31m[*] close\x1b[0m\n");
                    /* epoll_ctl */
                    epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, &evlist[i]);
                    if (ret == -1) { perror("epoll_ctl"); exit(1); }
                }
                else {
                    /* write */
                    buf[buflen] = '\0';
                    write(cfd, buf, buflen);
                    printf("%s", buf);
                }
            }
        }
    }    

    return 0;
}
