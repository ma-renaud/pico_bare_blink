#ifndef ISR_VECTORS_H
#define ISR_VECTORS_H


#pragma once
#include <functional>
#include "RP2040.h"
void registerHandler(IRQn_Type irqn, std::function<void()> &&f);


#endif //ISR_VECTORS_H
