/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ScopedPointer<juce::Slider> driveSlider;
    juce::ScopedPointer<juce::Slider> gainSlider;
    juce::ScopedPointer<juce::Slider> volumeSlider;

    juce::ScopedPointer<juce::Label> gainLabel;
    juce::ScopedPointer<juce::Label> volumeLabel;
    juce::ScopedPointer<juce::Label> driveLabel;


    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment>driveAttachment;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment>gainAttachment;
    juce::ScopedPointer<juce::AudioProcessorValueTreeState::SliderAttachment>volumeAttachment;



    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
