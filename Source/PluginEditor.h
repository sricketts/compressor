/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


class CompressorDBSlider : public Slider {
public:
    CompressorDBSlider ();
    ~CompressorDBSlider();
    
    enum
    {
        defaultMinusInfinitydB = -100
    };
    
    String getTextFromValue (double value) override;
};

//==============================================================================
/**
*/
class CompressorAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener, private Timer
{
public:
    CompressorAudioProcessorEditor (CompressorAudioProcessor&);
    ~CompressorAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CompressorAudioProcessor& processor;

    CompressorDBSlider outputGainSlider;
    CompressorDBSlider thresholdSlider;
    
    Label outputGainLabel;
    Label thresholdLabel;
    
    void sliderValueChanged (Slider* slider) override;
    void sliderDragStarted (Slider* slider) override;
    void sliderDragEnded (Slider* slider) override;
    
    void timerCallback() override;
    
    void initSlider (Slider& slider);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
