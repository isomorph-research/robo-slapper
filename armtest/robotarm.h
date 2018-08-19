#ifndef ROBOARM_H
#define ROBOARM_H

typedef enum
{
    LEFT,
    DOWN,
    UP,
    RIGHT,
    OPEN,
    CLOSE,
    INVALID
} Direction;

typedef struct
{
    Direction direction;
    int degrees;
} movement;

const int SHOULDER_PIN = 9;
const int ELBOW_PIN = 10;
const int GRIPPER_PIN = 11;

const int SHOULDER_OFFSET = 90;
const int ELBOW_OFFSET = 75;
const int GRIPPER_OFFSET = 90;

const int SHOULDER_SCALE = 2;
const int ELBOW_SCALE = 1;
const int GRIPPER_SCALE = 10;

const int SHOULDER_MAX = 180;
const int ELBOW_MAX = 180;
const int GRIPPER_MAX = 100;

const int SHOULDER_MIN = 0;
const int ELBOW_MIN = 0;
const int GRIPPER_MIN = 30;

int init_arm();
void center_arm();

void arm_up(int angle);
void arm_down(int angle);
void arm_left(int angle);
void arm_right(int angle);
void open_gripper(int angle);
void close_gripper(int angle);
void queue_open_gripper();
void queue_close_gripper();

#endif
