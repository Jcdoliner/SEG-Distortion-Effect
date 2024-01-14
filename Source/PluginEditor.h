/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#define sliderN 3
 

using namespace juce;

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;


    //std::string statecaps[sliderN] = { "drive","gain","volume" };
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
  
    const char* paramNames[sliderN] = { "Drive","Gain","Volume" };
    const char* labelNames[sliderN] = { "driveLabel","gainLabel","volumeLabel" };
    const char* statenames[sliderN] = { "drive","gain","volume" };

    ScopedPointer<Slider> driveSlider, gainSlider, volumeSlider;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment>volumeAttachment, gainAttachment, driveAttachment;
    ScopedPointer<Label> driveLabel, volumeLabel, gainLabel;


    //const char* paramNames[sliderN] = {"driveSlider","gainSlider","volumeSlider"};
    //const char* labelNames[sliderN] = { "driveLabel","gainLabel","volumeLabel" };
    ScopedPointer<Slider> sval[sliderN] = {driveSlider, gainSlider, volumeSlider };
    ScopedPointer<Label> slabel[sliderN]={driveLabel, gainLabel, volumeLabel};
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> apvts[3] = { driveAttachment,gainAttachment,volumeAttachment };


    
    



    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
