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
    //distFunction.onChange = [this] { styleMenuChanged(); };

    addAndMakeVisible(driveSlider = new Slider("Drive"));
    driveSlider->Slider::setSliderStyle(Slider::LinearBarVertical);
    driveSlider->Slider::setTextBoxStyle(Slider::NoTextBox,false,100,100);
    
    addAndMakeVisible(driveLabel=new Label("driveLabel"));
    driveLabel->Label::setText("Drive", dontSendNotification);
    driveLabel->Label::attachToComponent(driveSlider, false);

    addAndMakeVisible(gainSlider = new Slider("Gain"));
    gainSlider->Slider::setSliderStyle(Slider::LinearBarVertical);
    gainSlider->Slider::setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(gainLabel = new Label("gainLabel"));
    gainLabel->Label::setText("Gain", dontSendNotification);
    gainLabel->Label::attachToComponent(gainSlider, false);
    
    addAndMakeVisible(volumeSlider = new Slider("Volume"));
    volumeSlider->Slider::setSliderStyle(Slider::LinearBarVertical);
    volumeSlider->Slider::setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    
    addAndMakeVisible(volumeLabel = new Label("volumeLabel"));
    volumeLabel->Label::setText("Volume", dontSendNotification);
    volumeLabel->Label::attachToComponent(volumeSlider, false);
    
    addAndMakeVisible(distFunction);//= new ComboBox("distFunction"));

    distFunction.addItem("OverDrive", 1);
    distFunction.addItem("Crunch", 2);
    distFunction.addItem("Dist", 3);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    distFunctionAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(p.getState(), "distFuncAtt",distFunction);
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
    int xhalf = ((getWidth() / 2)) - (125);
    int yhalf = (getHeight() / 2);
    int sliderWidth = 50;
    driveSlider->setBounds(xhalf,(yhalf-70), sliderWidth,yhalf+20);
    gainSlider->setBounds(xhalf+100, (yhalf-70), sliderWidth, yhalf+20);
    volumeSlider->setBounds(xhalf + 200, (yhalf-70), sliderWidth, yhalf+20);
    distFunction.setBounds(xhalf, (yhalf + 70),getWidth()-70, 20);
}
