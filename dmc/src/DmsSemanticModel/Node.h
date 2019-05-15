#pragma once

#include "../DmsObject.h"

class Node {
private:
DmsObject *object;

public:
Node();
Node(DmsObject* scenario);
~Node();

void run();
void run(DmsObject* encounter);

};
