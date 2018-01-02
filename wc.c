#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_wc(const char *path);
static void in_wc();
static void die(const char *s);


int
main(int argc, char *argv[])
{
    int i;

    if(argc <2){
        in_wc();
    }

    for(i=1; i< argc; i++){
        do_wc(argv[i]);
    }
    exit(0);
}

#define BUFFER_SIZE 2048

static void
in_wc()
{
    unsigned char buf[BUFFER_SIZE];
    int n;
    for(;;){
        n = read(STDIN_FILENO, buf, sizeof buf);
        if(n == 0) break;
        if(write(STDOUT_FILENO, buf, n) < 0 ) die("mope");
    }
}


static void
do_wc(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;
    int count = 0;

    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);
    for(;;){
        n = read(fd, buf, sizeof buf);
        if(n < 0) die(path);
        if(n == 0) break;
        unsigned long i;
        for(i=0; i<sizeof buf ; i++){
            if(buf[i] == '\n'){
                count++;
            }
        }
    }
    printf("count = %d", count);
    if (close(fd) < 0) die(path);
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}