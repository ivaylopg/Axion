#include "messenger.h"

ofEvent<string> Messenger::sendMessage = ofEvent<string>();
ofEvent<float> Messenger::setVolume = ofEvent<float>();