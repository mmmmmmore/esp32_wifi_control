#ifndef MOTOR_HANDLER_H
#define MOTOR_HANDLER_H

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int forward;
    int backward;
    int left;
    int right;
    int crotator;
    int acrotator;
} motor_command_t;

void motor_handler_update(const motor_command_t *cmd);

#ifdef __cplusplus
}
#endif




#endif   //
