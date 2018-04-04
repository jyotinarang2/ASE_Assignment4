/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define MOD_WIDTH  1
//==============================================================================
VibratoPluginAudioProcessor::VibratoPluginAudioProcessor()
{
	CVibrato::createInstance(cVibrato);
}

VibratoPluginAudioProcessor::~VibratoPluginAudioProcessor()
{
	CVibrato::destroyInstance(cVibrato);
}

//==============================================================================
const String VibratoPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VibratoPluginAudioProcessor::acceptsMidi() const
{
  
    return false;
   
}

bool VibratoPluginAudioProcessor::producesMidi() const
{
   
    return false;
   
}

bool VibratoPluginAudioProcessor::isMidiEffect() const
{
 
    return false;
  
}

double VibratoPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VibratoPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int VibratoPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VibratoPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String VibratoPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void VibratoPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}


//==============================================================================
void VibratoPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
	//error_t = CVibrato::createInstance(cVibrato);
	//if (error_t == kUnknownError) {
		//std::cout << "Vibrato instance could not be created";
	//	return;
	//}
	error_t = cVibrato->initInstance(MOD_WIDTH, sampleRate, getTotalNumInputChannels());
	cVibrato->setParam(CVibrato::kParamModWidthInS, 0.01f);
	cVibrato->setParam(CVibrato::kParamModFreqInHz, 5);
}
float VibratoPluginAudioProcessor::getParameter(int param_index) {
	if (param_index == 0) {
		return cVibrato->getParam(CVibrato::VibratoParam_t::kParamModWidthInS);
		
	}
	else if (param_index == 1) {
		return cVibrato->getParam(CVibrato::VibratoParam_t::kParamModFreqInHz);
	}
	else {
		jassert("Invalid index");
	}
}
void VibratoPluginAudioProcessor::setParameter(int param_index, float param_value) {
	if (param_index == 0 && cVibrato) {
		cVibrato->setParam(CVibrato::VibratoParam_t::kParamModWidthInS, (param_value/100));
	}
	else if (param_index == 1 && cVibrato) {
		cVibrato->setParam(CVibrato::VibratoParam_t::kParamModFreqInHz, param_value);
	}
	else {
		jassert("Invalid index");
	}
}
void VibratoPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VibratoPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void VibratoPluginAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	if (pluginByPass) {
		setParameter(0, 0.0f);
		setParameter(1, 0.0f);
    }
	else {
		ScopedNoDenormals noDenormals;
		auto totalNumInputChannels = getTotalNumInputChannels();
		auto totalNumOutputChannels = getTotalNumOutputChannels();

		// In case we have more outputs than inputs, this code clears any output
		// channels that didn't contain input data, (because these aren't
		// guaranteed to be empty - they may contain garbage).
		// This is here to avoid people getting screaming feedback
		// when they first compile a plugin, but obviously you don't need to keep
		// this code if your algorithm always overwrites all the output channels.
		for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
			buffer.clear(i, 0, buffer.getNumSamples());
		/*if (modulationWidthChanged) {
			cVibrato->setParam(CVibrato::VibratoParam_t::kParamModWidthInS, modulationWidth);
			modulationWidthChanged = false;
		}
		if (modualtionFreqChanged) {
			cVibrato->setParam(CVibrato::VibratoParam_t::kParamModFreqInHz, modulationFreq);
			modualtionFreqChanged = false;
		}*/
		// This is the place where you'd normally do the guts of your plugin's
		// audio processing...
		// Make sure to reset the state if your inner loop is processing
		// the samples and the outer loop is handling the channels.
		// Alternatively, you can process the samples with the channels
		// interleaved by keeping the same state.
		//for (int channel = 0; channel < totalNumInputChannels; ++channel)
		//{
		 //   auto* channelData = buffer.getWritePointer (channel);

			// ..do something to the data...
		//}
		float **writePointer = buffer.getArrayOfWritePointers();
		cVibrato->process(writePointer, writePointer, buffer.getNumSamples());
	}
}
//void VibratoPlugin::

//==============================================================================
bool VibratoPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* VibratoPluginAudioProcessor::createEditor()
{
    return new VibratoPluginAudioProcessorEditor (*this);
}

//==============================================================================
void VibratoPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void VibratoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VibratoPluginAudioProcessor();
}
