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



    setSize (700, 400);
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
    //12x12 Grid
    int xunit = (getWidth() / 12);
    int yunit = (getHeight() / 12);
    int xcenter = xunit * 6;
    int ycenter = xunit * 6;
    int sliderWidth =xunit*2;
    int sliderHeight = yunit * 9;

    volumeSlider->setBounds(2*xunit, yunit, sliderWidth, sliderHeight);
    gainSlider->setBounds(xcenter-(xunit), yunit, sliderWidth, sliderHeight);
    driveSlider->setBounds(xcenter+(2 * xunit), yunit, sliderWidth, sliderHeight);

    distFunction.setBounds(xunit, (10.5 * yunit),xunit*10,yunit);
}
