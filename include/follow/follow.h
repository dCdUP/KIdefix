//
// Created by KIdefix on 11.08.24.
//

#ifndef FOLLOW_H
#define FOLLOW_H

int follow(const std::string& Interface);

void Handler(const void *message);

float convertDisttoCm(float dist);

float convertMovetoInterval(float moveX);

#endif //FOLLOW_H
