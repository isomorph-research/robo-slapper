#ifndef ROBOARM_H
#define ROBOARM_H

const int SHOULDER_PIN = 8;
const int ELBOW_PIN = 9;
const int GRIPPER_PIN = 10;

const int SHOULDER_OFFSET = 0;
const int ELBOW_OFFSET = 0;
const int GRIPPER_OFFSET = 0;

const int SHOULDER_SCALE = 1;
const int ELBOW_SCALE = 1;
const int GRIPPER_SCALE = 1;

const int SHOULDER_MAX = 180;
const int ELBOW_MAX = 180;
const int GRIPPER_MAX = 120;

const int SHOULDER_MIN = 0;
const int ELBOW_MIN = 0;
const int GRIPPER_MIN = 60;

int init_arm();

void arm_up(int angle);
void arm_down(int angle);
void arm_left(int angle);
void arm_right(int angle);
void open_gripper();
void close_gripper();

#endif