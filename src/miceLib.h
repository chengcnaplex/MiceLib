#ifndef __MICELib_H__
#define __MICELib_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <linux/input.h>

int setMiceDown(char* dev, int value);
int setMiceUp(char* dev, int value);
int setMiceMove(char* dev, int rel_x, int rel_y);
int setKeyboardDown(char* dev, int value);
int setKeyboardUp(char* dev, int value);
int setKeyboardAction(char* dev, int value);

#endif // __MICELib_H__
