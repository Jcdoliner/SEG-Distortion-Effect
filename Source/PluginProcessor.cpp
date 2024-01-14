/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/
#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    state = new juce::AudioProcessorValueTreeState(*this, nullptr);
    state->createAndAddParameter(statenames[0], paramNames[0], paramNames[0], juce::NormalisableRange<float>(0.f, 1.f, 0.01f), 0.f, nullptr, nullptr);
    state->createAndAddParameter(statenames[1], paramNames[1], paramNames[1], juce::NormalisableRange<float>(1.f, 150.f, 0.01f), 0.f, nullptr, nullptr);
    state->createAndAddParameter(statenames[2], paramNames[2], paramNames[2], juce::NormalisableRange<float>(0.01f, 1.f, 0.01f), 0.f, nullptr, nullptr);
    
    state->state = juce::ValueTree(statenames[0]);
    state->state = juce::ValueTree(statenames[1]);
    state->state = juce::ValueTree(statenames[2]);
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    float drive = *state->getRawParameterValue(statenames[0]);
    float gain = *state->getRawParameterValue(statenames[1]);
    float volume = *state->getRawParameterValue(statenames[2]);
    float distcontant = (gain / (200 * (gain/3)));
    float s;
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {

            s++;
            float cleanSig = *channelData;
            *channelData *= drive*gain;
            //*channelData *= drive;
            *channelData = ((volume) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2)));
            //*channelData = (volume*(((2.f /(juce::float_Pi)) * (tanf(*channelData)))+(cleanSig/2)));
            //*channelData = ((volume+distcontant) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2) - ((sinf((*channelData)/200)) / 2)));
            //*channelData = ((volume + distcontant) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2) - ((sinf(*channelData)) / 8)));
            //*channelData = ((volume/(s/gain)) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2) - ((sinf(*channelData)) / 8)));
            //*channelData = ((volume ) * ((cleanSig / 2) + ((sinf(*channelData * 50)) / 8)));
            //*channelData = ((volume +distcontant) * ((cleanSig / 2) + ((sinf(*channelData * 50)) / 8)));
            //*channelData = ((volume / 2) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2) - ((sinf(*channelData*(sinf(cleanSig)) * 50)) / 8)));
            
            channelData++;
        }
        
        // ..do something to the data...
    }
}
juce::AudioProcessorValueTreeState& NewProjectAudioProcessor::getState() {
     return *state;
}
//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    /*juce::MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);*/
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    juce::ValueTree tree = juce::ValueTree::readFromData(data,sizeInBytes);
    if (tree.isValid()) {
        state->state = tree;

    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
