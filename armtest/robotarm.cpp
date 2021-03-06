#include <Servo.h>
#include "robotarm.h"

Servo shoulder;
Servo elbow;
Servo gripper;

int shoulder_pos = SHOULDER_OFFSET;
int elbow_pos = ELBOW_OFFSET;
int gripper_pos = GRIPPER_OFFSET;

int init_arm() {
  shoulder.attach(SHOULDER_PIN);
  elbow.attach(ELBOW_PIN);
  gripper.attach(GRIPPER_PIN);

  shoulder.write(SHOULDER_OFFSET);
  elbow.write(ELBOW_OFFSET);
  gripper.write(GRIPPER_OFFSET);

  return 0;
}

void center_arm() {
  shoulder.write(SHOULDER_OFFSET);
  elbow.write(ELBOW_OFFSET);
  gripper.write(GRIPPER_OFFSET);
}

void arm_down(int angle) {
  if (elbow_pos + angle * ELBOW_SCALE <= ELBOW_MAX) {
    elbow_pos += angle * ELBOW_SCALE;
    elbow.write(elbow_pos);
  } else {
    elbow_pos = ELBOW_MAX;
    elbow.write(elbow_pos);
  }
  return;
}

void arm_up(int angle) {
  if (elbow_pos - angle * ELBOW_SCALE >= ELBOW_MIN) {
    elbow_pos -= angle * ELBOW_SCALE;
    elbow.write(elbow_pos);
  } else {
    elbow_pos = ELBOW_MIN;
    elbow.write(elbow_pos);
  }
  return;
}

void arm_right(int angle) {
  if (shoulder_pos - angle * SHOULDER_SCALE >= SHOULDER_MIN) {
    shoulder_pos -= angle * SHOULDER_SCALE;
    shoulder.write(shoulder_pos);
  } else {
    shoulder_pos = SHOULDER_MIN;
    shoulder.write(shoulder_pos);
  }
  return;
}

void arm_left(int angle) {
  if (shoulder_pos + angle * SHOULDER_SCALE <= SHOULDER_MAX) {
    shoulder_pos += angle * SHOULDER_SCALE;
    shoulder.write(shoulder_pos);
  } else {
    shoulder_pos = SHOULDER_MAX;
    shoulder.write(shoulder_pos);
  }
  return;
}

void open_gripper(int angle) {
  if (gripper_pos + angle * GRIPPER_SCALE <= GRIPPER_MAX) {
    gripper_pos += angle * GRIPPER_SCALE;
  } else {
    gripper_pos = GRIPPER_MAX;
  }
  gripper.write(gripper_pos);
  return;
}

void close_gripper(int angle) {
    if (gripper_pos - angle * GRIPPER_SCALE >= GRIPPER_MIN) {
    gripper_pos -= angle * GRIPPER_SCALE;
  } else {
    gripper_pos = GRIPPER_MIN;
  }
  gripper.write(gripper_pos);
  return;
}
