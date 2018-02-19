#ifndef NATIVES
#define NATIVES

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <string>

//My grid and snake libraries

#include "Snake.hpp"
#include "Grid.hpp"

// Do we want to showcase direct JNI/NDK interaction?
// Undefine this to get real cross-platform code.
// These headers are only needed for direct NDK/JDK interaction
#include <jni.h>
#include <android/native_activity.h>

// Since we want to get the native activity from SFML, we'll have to use an
// extra header here:
#include <SFML/System/NativeActivity.hpp>

int vibrate(sf::Time duration);

#endif