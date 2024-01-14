/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace juce;
//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
 {
   /*
    for (int i = 0; i < 3;i++) {
        
        addAndMakeVisible(sval[i] = new Slider(paramNames[i]));
        sval[i]->Slider::setSliderStyle(Slider::LinearBarVertical);
        sval[i]->Slider::setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
       
        addAndMakeVisible(slabel[i] = new Label(labelNames[i]));
        slabel[i]->Label::setText(paramNames[i], dontSendNotification);
        slabel[i]->Label::attachToComponent(sval[i], true);

        //apvts[i] = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), statenames[i], *sval[i]);

    }
    */

    addAndMakeVisible(driveSlider = new Slider("Drive"));
    driveSlider->Slider::setSliderStyle(Slider::LinearBarVertical);
    driveSlider->Slider::setTextBoxStyle(Slider::NoTextBox,false,100,100);
    
    addAndMakeVisible(driveLabel=new Label("driveLabel"));
    driveLabel->Label::setText("Drive", dontSendNotification);
    driveLabel->Label::attachToComponent(driveSlider, true);

    addAndMakeVisible(gainSlider = new Slider("Gain"));
    gainSlider->Slider::setSliderStyle(Slider::LinearBarVertical);
    gainSlider->Slider::setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(gainLabel = new Label("gainLabel"));
    gainLabel->Label::setText("Gain", dontSendNotification);
    gainLabel->Label::attachToComponent(gainSlider, true);
    
    addAndMakeVisible(volumeSlider = new Slider("Volume"));
    volumeSlider->Slider::setSliderStyle(Slider::LinearBarVertical);
    volumeSlider->Slider::setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(volumeLabel = new Label("volumeLabel"));
    volumeLabel->Label::setText("Volume", dontSendNotification);
    volumeLabel->Label::attachToComponent(volumeSlider, true);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(),"drive", *driveSlider);
    gainAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "gain", *gainSlider);
    volumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "volume", *volumeSlider);


    setSize (300, 200);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
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
