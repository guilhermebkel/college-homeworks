#ifndef POKER_FACE_VALIDATION_H
#define POKER_FACE_VALIDATION_H

#include "poker-face.h"
#include "arrangement-list.h"

bool handHasClassificationType (Hand hand, ClassifiedHandType classifiedHandType);
bool isInvalidPlay (Round round, ArrangementList<Balance> *balances);

#endif