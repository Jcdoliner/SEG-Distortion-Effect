/*
  ==============================================================================

    distFunctions.h
    Created: 15 Jan 2024 5:55:04pm
    Author:  Cheka

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

const float TWOVERPI = (2.f / (juce::float_Pi));
float distortionFunction(int idx, float channelData, float volume, float cleanSig,float maxVal);
float windowFunction(int N,int sample);