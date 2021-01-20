#ifndef __KEY_H
#define __KEY_H

#include <stdio.h>
#include <stdint.h>
#include <Math.h>
#include <webots/keyboard.h>

#define Speed 20.0f

void get_Keyboard_Control(float *VX, float *VY, float *YAW, float *PITCH);


#endif /*__KEY_H*/