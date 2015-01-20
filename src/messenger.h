#pragma once
#include "ofMain.h"

class Messenger {
public:
    static ofEvent<string> sendMessage;
};