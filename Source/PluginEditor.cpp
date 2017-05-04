/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
CompressorAudioProcessorEditor::CompressorAudioProcessorEditor (CompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize (600, 200);
    
    addAndMakeVisible(outputGainLabel);
    outputGainLabel.setText(p.outputGainDBParameter->name, dontSendNotification);
    outputGainLabel.attachToComponent(&outputGainSlider, true);
    outputGainSlider.setValue(*(p.outputGainDBParameter));
    addAndMakeVisible(&outputGainSlider);

    addAndMakeVisible(thresholdLabel);
    thresholdLabel.setText(p.thresholdDBParameter->name, dontSendNotification);
    thresholdLabel.attachToComponent(&thresholdSlider, true);
    thresholdSlider.setValue(*(p.thresholdDBParameter));
    addAndMakeVisible(&thresholdSlider);
    
    outputGainSlider.addListener(this);
    thresholdSlider.addListener(this);
    
    // Use a timer to update editor state periodically. There are other clients besides this editor that
    // may be changing the state of the processor, the timer synchronizes this editor with that state.
    startTimer(100);
}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
}

//==============================================================================
void CompressorAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    //g.drawFittedText ("Compressor", getLocalBounds(), Justification::centred, 1);
}

void CompressorAudioProcessorEditor::resized()
{
    const int sliderX = 110;
    const int sliderWidth = getWidth() - 150;
    const int sliderHeight = 20;
    
    thresholdSlider.setBounds(sliderX, 30, sliderWidth, sliderHeight);
    outputGainSlider.setBounds (sliderX, 70, sliderWidth, sliderHeight);
}

void CompressorAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    if (slider == &outputGainSlider) {
        *(processor.outputGainDBParameter) = outputGainSlider.getValue();
    } else if (slider == &thresholdSlider) {
        *(processor.thresholdDBParameter) = thresholdSlider.getValue();
    } else {
        assert(0);
    }
}

void CompressorAudioProcessorEditor::sliderDragStarted (Slider* slider)
{
    if (slider == &outputGainSlider) {
        processor.outputGainDBParameter->beginChangeGesture();
    } else if (slider == &thresholdSlider) {
        processor.thresholdDBParameter->beginChangeGesture();
    } else {
        assert(0);
    }
}

void CompressorAudioProcessorEditor::sliderDragEnded (Slider* slider)
{
    if (slider == &outputGainSlider) {
        processor.outputGainDBParameter->endChangeGesture();
    } else if (slider == &thresholdSlider) {
        processor.thresholdDBParameter->endChangeGesture();
    } else {
        assert(0);
    }
}

void CompressorAudioProcessorEditor::timerCallback()
{
    // update the slider based on the value of the parameter in the processor
    outputGainSlider.setValue(*(processor.outputGainDBParameter));
    thresholdSlider.setValue(*(processor.thresholdDBParameter));
}

CompressorDBSlider::CompressorDBSlider()
: Slider() {
    setSliderStyle (Slider::LinearHorizontal);
    setRange(defaultMinusInfinitydB, 6);
    setTextValueSuffix(" dB");
    setTextBoxStyle (Slider::TextBoxRight, false, 70, 20);
    setPopupDisplayEnabled (true, this);
}

CompressorDBSlider::~CompressorDBSlider()
{
    
}

String CompressorDBSlider::getTextFromValue(double value)
{
    if (value <= defaultMinusInfinitydB) {
        return String("-INF") + getTextValueSuffix();
    } else {
        return String(value, 1) + getTextValueSuffix();
    }
}


