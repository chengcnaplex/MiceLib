#include "miceLib.h"

char *defaultMice = "/dev/input/mice";
char *defaultKB = "/dev/intput/event1";

int sendREL_XYData(int fd, int rel_x, int rel_y) {
    struct input_event event;

    gettimeofday(&event.time, 0);

    event.type = EV_REL;
    event.value = rel_x;
    event.code = REL_X;
    write(fd, &event, sizeof(event));

    event.type = EV_REL;
    event.value = rel_y;
    event.code = REL_Y;
    write(fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(fd, &event, sizeof(event));
}

int sendKey(int fd, int value, int status) {
    struct input_event event;

    gettimeofday(&event.time, 0);
    event.type = EV_KEY;
    event.value = status;
    event.code = value;
    write(fd, &event, sizeof(event));
    
    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(fd, &event, sizeof(event));
}

int openDev(char* dev) {
    int fd = open(dev, O_RDWR);
    if(fd <= 0) {
        printf("Can not %s input file.\n", dev);
        exit(-1);
    }
    return fd;
}

int sendMiceMove(char* dev, int rel_x, int rel_y) {

    int fd = open(dev, O_RDWR);

    sendREL_XYData(fd, rel_x, rel_y);

    close(fd);
}


int sendKBDown(char* dev, int value) {
    struct input_event event;
    
    int fd = openDev(dev);
    
    sendKey(fd, value, 1);

    close(fd);
}

int sendKBUp(char* dev, int value) {
    struct input_event event;
    
    int fd = openDev(dev);
    
    sendKey(fd, value, 0);

    close(fd);
}

int sendKBAction(char* dev, int value) {
    struct input_event event;
    
    int fd = openDev(dev);
    
    sendKey(fd, value, 1);
    sendKey(fd, value, 0);

    close(fd);
}

int sendMiceDown(char* dev, int value){
    sendKBDown(dev, value);
}

int sendMiceUp(char* dev, int value) {
    sendKBUp(dev, value);
}

int sendMiceAction(char* dev, int value) {
    sendKBAction(dev, value);
}

int main(int argc, char *argv) {

    int i = 0;
    
    for (i = 0; i < 50; i++) {
        sendMiceMove("/dev/input/event3", 10, 10);
        sendKBAction("/dev/input/event1", KEY_A);
        sleep(1);
    }
}
