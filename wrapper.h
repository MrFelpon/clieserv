//
// Created by Gennaro Caccavale on 06/03/2020.
//

#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>


int Socket(int family, int type, int protocol){
    int n;
    if ((n = socket(family, type, protocol)) < 0){
        perror("socket creation failed...");
        exit(1);
    }

    return n;
}

void Bind(int sockfd, struct sockaddr_in *servaddr) {
    if (bind(sockfd, (struct sockaddr *) servaddr, sizeof(*servaddr)) < 0) {
        perror("socket bind failed...\n");
        exit(1);
    }
}

void Connect(int sockfd, struct sockaddr_in *servaddr) {
    if (connect(sockfd,(struct sockaddr *) servaddr, sizeof(*servaddr)) < 0) {
        perror("connection failed...");
        exit(1);
    }
}

void Listen(int sockfd, int backlog){
    // Now server is ready to listen and verification
    if (listen(sockfd, backlog) < 0) {
        printf("Listen failed...\n");
        exit(1);
    }
    else
        printf("Server listening..\n");
}

int Accept(int sockfd, struct sockaddr_in *client, socklen_t *addr_dim){
    int connfd = accept(sockfd, (struct sockaddr *)&client, addr_dim);
    if (connfd < 0) {
        perror("server acccept failed...\n");
        exit(1);
    }
    return connfd;
}

ssize_t FullWrite(int fd, const void *buf, size_t count) {
    size_t nleft = count;
    ssize_t nwritten = 0;
//    nleft = count;

    while (nleft > 0) {
        if ((nwritten = write(fd, buf, nleft)) < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                perror("hhh");
                exit(nwritten);
            }
        }
        nleft -= nwritten;
        buf += nwritten;
    }

    return nleft;
}

ssize_t FullRead(int fd, void *buf, size_t count){
    size_t nleft;
    size_t nread;
    nleft = count;

    while (nleft > 0){
        if ((nread = read(fd, buf, nleft))<0) {
            if (errno == EINTR) {
                continue;
            } else {
                exit(nread);
            }
        } else if (nread == 0){
            break;
        }
        nleft -= nread;
        buf += nread;
        }
    buf = 0;
    return nleft;
}

pid_t Fork(){
    int pid;

    if((pid=fork())<0){
        perror("fork");
        exit(1);
    }

    return pid;
}
//maybbe add setsockopt

#endif //WRAPPER_H
