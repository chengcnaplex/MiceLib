#ifndef __MICELIB_H__
#define __MICELIB_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <linux/input.h>

/**
 * mice wheel, rel value can be The positive and negative.
 */
int miceWheel(char* dev, int rel);
/**
 * mice move with relative.
 */
int miceMove(char* dev, int rel_x, int rel_y);
/**
 * mice left single click.
 */
int miceLeftSClick(char* dev);
/**
 * mice left double click.
 */
int miceLeftDClick(char* dev);
/**
 * mice right single click.
 */
int miceRightClick(char* dev);
/**
 * mice middle single click.
 */
int miceMiddleClick(char* dev);
/**
 * keyboard char or string.
 */
int KBString(char* dev, char* string);

#endif // __MICELIB_H__
