/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
CompressorAudioProcessor::CompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter (outputGainDBParameter = new AudioParameterFloat ("output_gain_db", // parameter ID
                                                  "Output Gain",                                // parameter name
                                                  NormalisableRange<float> (-100.0f, 6.0f), // parameter range
                                                  0.0f));                                // default value
    addParameter (thresholdDBParameter = new AudioParameterFloat ("threshold_db",
                                                                   "Threshold",
                                                                   NormalisableRange<float> (-100.0f, 6.0f),
                                                                   0.0f));
}

CompressorAudioProcessor::~CompressorAudioProcessor()
{

}

//==============================================================================
const String CompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double CompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompressorAudioProcessor::setCurrentProgram (int index)
{
}

const String CompressorAudioProcessor::getProgramName (int index)
{
    return String();
}

void CompressorAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void CompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void CompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void CompressorAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // fixme: add sensing parameter for peak vs RMS. currently using peak
    // fixme: add attack/release

    // FIXME
    ratio = 4;
    // limiter ratio can be set to 60 i read somewhere
    
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        const float peak = buffer.getMagnitude(channel, 0, buffer.getNumSamples());
        const float peakDB = Decibels::gainToDecibels<float>(peak);
        
        // Peak Sensing
        // attack time is 0 (FIXME)
        // release time is the time it takes to play the buffer (FIXME)
        if (peakDB > *thresholdDBParameter) {
            const float cs = 1.0f - (1.0f / ratio);
            const float gainDB = cs * (*thresholdDBParameter - peakDB);
            const float gain = Decibels::decibelsToGain<float>(gainDB);
            
            float* channelData = buffer.getWritePointer (channel);
            
            for (int i = 0; i < buffer.getNumSamples(); i++) {
                const float value = channelData[i];
                channelData[i] = gain * value;
            }
        }
    }
    const float outputGain = Decibels::decibelsToGain<float>(*outputGainDBParameter);
    buffer.applyGain(outputGain);
}

//==============================================================================
bool CompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* CompressorAudioProcessor::createEditor()
{
    return new CompressorAudioProcessorEditor (*this);
}

//==============================================================================
void CompressorAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompressorAudioProcessor();
}
