/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LilmotorjawnAudioProcessorEditor::LilmotorjawnAudioProcessorEditor (LilmotorjawnAudioProcessor& p,juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), valueTreeState(vts), audioProcessor (p), startTime (juce::Time::getMillisecondCounterHiRes() * 0.001)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    

    addAndMakeVisible (openAmountSlider);
    openAttachment.reset (new SliderAttachment (valueTreeState, "open_amount", openAmountSlider.slider));
    
    addAndMakeVisible (speedSlider);
    openAttachment.reset (new SliderAttachment (valueTreeState, "speed", speedSlider.slider));
    
    addAndMakeVisible (accelSlider);
    openAttachment.reset (new SliderAttachment (valueTreeState,"accel", accelSlider.slider));
    
    openAmountSlider.slider.onValueChange = [this] {
        auto message = juce::MidiMessage::controllerEvent (1, 0, (int)( openAmountSlider.slider.getValue() * 127));
        message.setTimeStamp (juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);
        audioProcessor.addMessageToBuffer (message);
    };
    
    speedSlider.slider.onValueChange = [this] {
        auto message = juce::MidiMessage::controllerEvent (1, 1, (int)( speedSlider.slider.getValue() * 127));
        message.setTimeStamp (juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);
        audioProcessor.addMessageToBuffer (message);
    };
    
    accelSlider.slider.onValueChange = [this] {
        auto message = juce::MidiMessage::controllerEvent (1, 2, (int)( accelSlider.slider.getValue() * 127));
        message.setTimeStamp (juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);
        audioProcessor.addMessageToBuffer (message);
    };
    
    addAndMakeVisible(openButton);
    openButton.onClick = [this]
    {
        auto message = juce::MidiMessage::noteOn (1, 61, (juce::uint8) 100);
        message.setTimeStamp (juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);
        audioProcessor.addMessageToBuffer (message);

        auto messageOff = juce::MidiMessage::noteOff (message.getChannel(), message.getNoteNumber());
        messageOff.setTimeStamp (message.getTimeStamp() + 0.1);
        audioProcessor.addMessageToBuffer (messageOff);
    };
    addAndMakeVisible(closeButton);
    closeButton.onClick = [this]
    {
        auto message = juce::MidiMessage::noteOn (1, 60, (juce::uint8) 100);
        message.setTimeStamp (juce::Time::getMillisecondCounterHiRes() * 0.001 - startTime);
        audioProcessor.addMessageToBuffer (message);

        auto messageOff = juce::MidiMessage::noteOff (message.getChannel(), message.getNoteNumber());
        messageOff.setTimeStamp (message.getTimeStamp() + 0.1);
        audioProcessor.addMessageToBuffer (messageOff);
    };
    
    //setSize (paramSliderWidth + paramLabelWidth, juce::jmax (100, paramControlHeight * 2));
    setSize (800, 300);
}

LilmotorjawnAudioProcessorEditor::~LilmotorjawnAudioProcessorEditor()
{
    openAttachment.reset(nullptr);
    speedAttachment.reset(nullptr);
    accelAttachment.reset(nullptr);
}

//==============================================================================
void LilmotorjawnAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void LilmotorjawnAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds().reduced(4.0f);
    auto buttonArea = area.removeFromRight(200);
    juce::FlexBox buttons;
    buttons.flexWrap = FlexBox::Wrap::noWrap;
    buttons.flexDirection = FlexBox::Direction::column;
    buttons.justifyContent = FlexBox::JustifyContent::spaceAround;
    buttons.items.add(FlexItem(openButton).withFlex(2).withMargin(2.0f));
    buttons.items.add(FlexItem(closeButton).withFlex(2).withMargin(2.0f));
    buttons.performLayout(buttonArea.toFloat());
    juce::FlexBox fb;
    fb.flexWrap = FlexBox::Wrap::noWrap;
    fb.flexDirection = FlexBox::Direction::row;
    fb.justifyContent = FlexBox::JustifyContent::spaceAround;
    //fb.items.add(buttons);
    fb.items.add(FlexItem(openAmountSlider).withFlex(2).withMargin(2.0f));
    fb.items.add(FlexItem(speedSlider).withFlex(2).withMargin(2.0f));
    fb.items.add(FlexItem(accelSlider).withFlex(2).withMargin(2.0f));
   
    fb.performLayout(area.toFloat());
}
