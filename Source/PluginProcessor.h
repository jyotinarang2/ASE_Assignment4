/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Vibrato.h"
#include "ErrorDef.h"

//==============================================================================
/**
*/
class VibratoPluginAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    VibratoPluginAudioProcessor();
    ~VibratoPluginAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    //==============================================================================
    float getParameter(int param_index) override;
    void setParameter(int param_index, float param_value) override;
	//===========================================================
	bool getParamByPass() {
		return pluginByPass;
	}
	void setParamByPass(bool byPassValue) {
		pluginByPass = byPassValue;
	}
	
	

	bool modulationWidthChanged = false;
	bool modualtionFreqChanged = false;
	float modulationWidth = 0.0f;
	float modulationFreq = 0.0f;

private:
    CVibrato *cVibrato = 0;
	bool pluginByPass = false;
	Error_t error_t;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoPluginAudioProcessor)
};
