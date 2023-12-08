/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
using namespace juce;
class LabeledSlider : public GroupComponent
{
public:
    LabeledSlider (const String& name)
    {
        setText (name);
        setTextLabelPosition (Justification::centredTop);
        addAndMakeVisible (slider);
    }
    
    void resized() override
    {
        slider.setBounds (getLocalBounds().reduced (10));
    }
    
    Slider slider { Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };
};
//==============================================================================
/**
*/
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
class LilmotorjawnAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LilmotorjawnAudioProcessorEditor (LilmotorjawnAudioProcessor&,juce::AudioProcessorValueTreeState& vts);
    ~LilmotorjawnAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::AudioProcessorValueTreeState& valueTreeState;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LilmotorjawnAudioProcessor& audioProcessor;
    std::unique_ptr<SliderAttachment> openAttachment;
    LabeledSlider openAmountSlider {"Open/Close Amount"};
    
    std::unique_ptr<SliderAttachment> speedAttachment;
    LabeledSlider speedSlider {"Speed"};
    
    std::unique_ptr<SliderAttachment> accelAttachment;
    LabeledSlider accelSlider {"acceleration"};
    
     
    juce::TextButton openButton{"open"};
    juce::TextButton closeButton{"close"};
    double startTime;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LilmotorjawnAudioProcessorEditor)
};
