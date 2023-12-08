/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LilmotorjawnAudioProcessor::LilmotorjawnAudioProcessor()

     : AudioProcessor(), parameters (*this, nullptr, juce::Identifier ("lilmotorjawn"),
                                     {
         std::make_unique<juce::AudioParameterFloat> (ParameterID { "open_amount", 1 },            // parameterID
                                                                                      "Open amount",            // parameter name
                                                                                      0.0f,              // minimum value
                                                                                      1.0f,              // maximum value
                                                                                      1.0f),             // default value
         std::make_unique<juce::AudioParameterFloat> (ParameterID { "speed", 1 },      // parameterID
                                                                                     "Speed",     // parameter name
                                                     0.0f,              // minimum value
                                                     1.0f,              // maximum value
                                                     1.0f) ,             // default value
         std::make_unique<juce::AudioParameterFloat> (ParameterID { "accel", 1 },      // parameterID
                                                                                     "Acceleration",     // parameter name
                                                     0.0f,              // minimum value
                                                     1.0f,              // maximum value
                                                     1.0f)
                                     })
                    
{
}

LilmotorjawnAudioProcessor::~LilmotorjawnAudioProcessor()
{
}

//==============================================================================
const juce::String LilmotorjawnAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LilmotorjawnAudioProcessor::acceptsMidi() const
{
    return true;
}

bool LilmotorjawnAudioProcessor::producesMidi() const
{

    return true;

}

bool LilmotorjawnAudioProcessor::isMidiEffect() const
{

    return true;
 
}

double LilmotorjawnAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LilmotorjawnAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LilmotorjawnAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LilmotorjawnAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LilmotorjawnAudioProcessor::getProgramName (int index)
{
    return {};
}

void LilmotorjawnAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LilmotorjawnAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void LilmotorjawnAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LilmotorjawnAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    juce::ignoreUnused (layouts);
    return true;
 
}
#endif

void LilmotorjawnAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    // A pure MIDI plugin shouldn't be provided any audio data
    //jassert (buffer.getNumChannels() == 0);
    
    midiMessages.addEvents(midiBuffer, midiBuffer.getFirstEventTime(), midiBuffer.getLastEventTime(), 0);
    for(auto msg: midiMessages)
    {
        DBG(msg.getMessage().getDescription());
    }
    midiBuffer.clear();
   // however we use the buffer to get timing information
//   auto numSamples = buffer.getNumSamples();
//   for (const auto metadata : midi)
//    {
//        const auto msg = metadata.getMessage();
//        if      (msg.isNoteOn())  notes.add (msg.getNoteNumber());
//        else if (msg.isNoteOff()) notes.removeValue (msg.getNoteNumber());
//    }
//
//            midi.clear();
    
    //send midi message
   // midi.addEvent
}

//==============================================================================
bool LilmotorjawnAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LilmotorjawnAudioProcessor::createEditor()
{
    return new LilmotorjawnAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void LilmotorjawnAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void LilmotorjawnAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
     
            if (xmlState.get() != nullptr)
                if (xmlState->hasTagName (parameters.state.getType()))
                    parameters.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LilmotorjawnAudioProcessor();
}
