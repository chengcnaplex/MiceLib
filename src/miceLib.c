#include "miceLib.h"

int CAPDecodeFlag = 0;

int keyDecode(char ch) {
    CAPDecodeFlag = 0;
    switch ( ch ) {
        case 27 : CAPDecodeFlag = 0; return KEY_ESC		;
        case '!' : CAPDecodeFlag = 1; case '1' : return KEY_1			;
        case '@' : CAPDecodeFlag = 1; case '2' : return KEY_2			;
        case '#' : CAPDecodeFlag = 1; case '3' : return KEY_3			;
        case '$' : CAPDecodeFlag = 1; case '4' : return KEY_4			;
        case '%' : CAPDecodeFlag = 1; case '5' : return KEY_5			;
        case '^' : CAPDecodeFlag = 1; case '6' : return KEY_6			;
        case '&' : CAPDecodeFlag = 1; case '7' : return KEY_7			;
        case '*' : CAPDecodeFlag = 1; case '8' : return KEY_8			;
        case '(' : CAPDecodeFlag = 1; case '9' : return KEY_9			;
        case ')' : CAPDecodeFlag = 1; case '0' : return KEY_0			;
        case '_' : CAPDecodeFlag = 1; case '-' : return KEY_MINUS		;
        case '+' : CAPDecodeFlag = 1; case '=' : return KEY_EQUAL		;
        case '\b' : return KEY_BACKSPACE;
        case '\t' : return KEY_TAB		;
        case 'Q' : CAPDecodeFlag = 1; case 'q' : return KEY_Q			;
        case 'W' : CAPDecodeFlag = 1; case 'w' : return KEY_W			;
        case 'E' : CAPDecodeFlag = 1; case 'e' : return KEY_E			;
        case 'R' : CAPDecodeFlag = 1; case 'r' : return KEY_R			;
        case 'T' : CAPDecodeFlag = 1; case 't' : return KEY_T			;
        case 'Y' : CAPDecodeFlag = 1; case 'y' : return KEY_Y			;
        case 'U' : CAPDecodeFlag = 1; case 'u' : return KEY_U			;
        case 'I' : CAPDecodeFlag = 1; case 'i' : return KEY_I			;
        case 'O' : CAPDecodeFlag = 1; case 'o' : return KEY_O			;
        case 'P' : CAPDecodeFlag = 1; case 'p' : return KEY_P			;
        case '{' : CAPDecodeFlag = 1; case '[' : return KEY_LEFTBRACE	;
        case '}' : CAPDecodeFlag = 1; case ']' : return KEY_RIGHTBRACE;
        case '\n': return KEY_ENTER	;
        case 'A' : CAPDecodeFlag = 1; case 'a' : return KEY_A			;
        case 'S' : CAPDecodeFlag = 1; case 's' : return KEY_S			;
        case 'D' : CAPDecodeFlag = 1; case 'd' : return KEY_D			;
        case 'F' : CAPDecodeFlag = 1; case 'f' : return KEY_F			;
        case 'G' : CAPDecodeFlag = 1; case 'g' : return KEY_G			;
        case 'H' : CAPDecodeFlag = 1; case 'h' : return KEY_H			;
        case 'J' : CAPDecodeFlag = 1; case 'j' : return KEY_J			;
        case 'K' : CAPDecodeFlag = 1; case 'k' : return KEY_K			;
        case 'L' : CAPDecodeFlag = 1; case 'l' : return KEY_L			;
        case ':' : CAPDecodeFlag = 1; case ';' : return KEY_SEMICOLON	;
        case '"' : CAPDecodeFlag = 1; case '\'': return KEY_APOSTROPHE;
        case '~' : CAPDecodeFlag = 1; case '`' : return KEY_GRAVE		;
        case '|' : CAPDecodeFlag = 1; case '\\': return KEY_BACKSLASH;
        case 'Z' : CAPDecodeFlag = 1; case 'z' : return KEY_Z			;
        case 'X' : CAPDecodeFlag = 1; case 'x' : return KEY_X			;
        case 'C' : CAPDecodeFlag = 1; case 'c' : return KEY_C			;
        case 'V' : CAPDecodeFlag = 1; case 'v' : return KEY_V			;
        case 'B' : CAPDecodeFlag = 1; case 'b' : return KEY_B			;
        case 'N' : CAPDecodeFlag = 1; case 'n' : return KEY_N			;
        case 'M' : CAPDecodeFlag = 1; case 'm' : return KEY_M			;
        case '<' : CAPDecodeFlag = 1; case ',' : return KEY_COMMA		;
        case '>' : CAPDecodeFlag = 1; case '.' : return KEY_DOT		;
        case '?' : CAPDecodeFlag = 1; case '/' : return KEY_SLASH		;
        case ' ' : return KEY_SPACE		;
        default  : return KEY_SPACE		;
    };
};


int shiftDecode(void) {
    return KEY_LEFTSHIFT;
}

int ControlDecode(void) {
    return KEY_LEFTCTRL	;
}

int miceLeftDecode(void) {
    return BTN_LEFT;
}

int miceRightDecode(void) {
    return BTN_RIGHT;
}

int miceMiddleDecode(void) {
    return BTN_MIDDLE;
}

int sendREL_WheelData(int fd, int rel) {
    struct input_event event;

    gettimeofday(&event.time, 0);

    event.type = EV_REL;
    event.value = rel;
    event.code = REL_WHEEL;
    write(fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.value = 0;
    event.code = SYN_REPORT;
    write(fd, &event, sizeof(event));
}

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
    int fd = openDev(dev);
    
    sendKey(fd, value, 1);

    close(fd);
}

int sendKBUp(char* dev, int value) {
    int fd = openDev(dev);
    
    sendKey(fd, value, 0);

    close(fd);
}

int sendChar(char* dev, int value) {
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
    sendChar(dev, value);
}

int sendCapChar(char* dev, char ch) {
    sendKBDown(dev, shiftDecode());
    sendChar(dev, ch);
    sendKBUp(dev, shiftDecode());
}

int sendString(char* dev, char* string) {

    if (string == NULL){
        return 0;
    }

    int i = 0;
    while ( string[0] != 0 ) {

        int decode = keyDecode(string[0]);
        if (CAPDecodeFlag == 0) {
            if (string[0] == '\n') {
                sendChar(dev, KEY_ENTER);
                sendChar(dev, KEY_ENTER);
            } else 
                sendChar(dev, decode);

        } else {
            sendCapChar(dev, decode);
        }

        string++;
    }
}

int miceLeftSClick(char* dev) {
    sendMiceAction(dev, miceLeftDecode());
}

int miceLeftDClick(char* dev) {
    sendMiceDown(dev, miceLeftDecode());
    sendMiceDown(dev, miceLeftDecode());
    sendMiceUp(dev, miceLeftDecode());
}

int miceRightClick(char* dev) {
    sendMiceAction(dev, miceRightDecode());
}

int miceMiddleClick(char* dev) {
    sendMiceAction(dev, miceMiddleDecode());
}

int miceWheel(char* dev, int rel) {
    int fd = openDev(dev);
    sendREL_WheelData(fd, rel);
    close(fd);
}


int main(int argc, char *argv) {

    sendMiceMove("/dev/input/event3", 10, 10);
    sendString("/dev/input/event1", "ls\n");
    sendString("/dev/input/event1", "`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>?\n");
    //miceWheel("/dev/input/event3", 1);
}
