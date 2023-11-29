/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(driveSlider = new juce::Slider("Drive"));
    driveSlider->Slider::setSliderStyle(juce::Slider::LinearBarVertical);
    driveSlider->Slider::setTextBoxStyle(juce::Slider::NoTextBox,false,100,100);
    
    addAndMakeVisible(driveLabel=new juce::Label("driveLabel"));
    driveLabel->Label::setText("Drive", juce::dontSendNotification);
    driveLabel->Label::attachToComponent(driveSlider, true);

    addAndMakeVisible(gainSlider = new juce::Slider("Gain"));
    gainSlider->Slider::setSliderStyle(juce::Slider::LinearBarVertical);
    gainSlider->Slider::setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(gainLabel = new juce::Label("gainLabel"));
    gainLabel->Label::setText("Gain", juce::dontSendNotification);
    gainLabel->Label::attachToComponent(gainSlider, true);
    
    addAndMakeVisible(volumeSlider = new juce::Slider("Volume"));
    volumeSlider->Slider::setSliderStyle(juce::Slider::LinearBarVertical);
    volumeSlider->Slider::setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(volumeLabel = new juce::Label("volumeLabel"));
    volumeLabel->Label::setText("Volume", juce::dontSendNotification);
    volumeLabel->Label::attachToComponent(volumeSlider, true);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    driveAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(),"drive", *driveSlider);
    gainAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "gain", *gainSlider);
    volumeAttachment = new juce::AudioProcessorValueTreeState::SliderAttachment(p.getState(), "volume", *volumeSlider);


    setSize (300, 200);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    int sliderpos = ((getWidth() / 2)) - (100);
    driveSlider->setBounds(sliderpos,((getHeight()/2)-(100/2)),10,100);
    gainSlider->setBounds(sliderpos+100, ((getHeight() / 2) - (100 / 2)), 10, 100);
    volumeSlider->setBounds(sliderpos + 200, ((getHeight() / 2) - (100 / 2)), 10, 100);
}
