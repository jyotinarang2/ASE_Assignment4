/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define MODWIDTH 0;
#define MODFREQ 1;

//==============================================================================
VibratoPluginAudioProcessorEditor::VibratoPluginAudioProcessorEditor (VibratoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
        // these define the parameters of our slider object
    modulationWidth.setSliderStyle (Slider::LinearBarVertical);
    modulationWidth.setRange(0, 100, 1.0);
    modulationWidth.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    modulationWidth.setPopupDisplayEnabled (true, false, this);
    modulationWidth.setTextValueSuffix (" Modulation Width");
    //modulationWidth.setValue(processor.getParameter(0));
	modulationWidth.addListener(this);
    // this function adds the slider to the editor
    addAndMakeVisible (&modulationWidth);
    modulationFrequency.setSliderStyle (Slider::LinearBarVertical);
    modulationFrequency.setRange(0, 10, 1.0);
    modulationFrequency.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    modulationFrequency.setPopupDisplayEnabled (true, false, this);
    modulationFrequency.setTextValueSuffix (" Modulation Frequency");
    //modulationFrequency.setValue(processor.getParameter(1));
	modulationFrequency.addListener(this);
    // this function adds the slider to the editor
    addAndMakeVisible (&modulationFrequency);
	addAndMakeVisible(&toggleButton);
	toggleButton.addListener(this);
    
}

VibratoPluginAudioProcessorEditor::~VibratoPluginAudioProcessorEditor()
{
}

void VibratoPluginAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (slider == &modulationWidth) {
		float widthValue = modulationWidth.getValue();
		processor.modulationWidthChanged = true;
		processor.modulationWidth = widthValue/100;
		processor.setParameter(0, widthValue/100);
	}
	else if (slider == &modulationFrequency) {
		float freqValue = modulationFrequency.getValue();
		processor.modulationWidthChanged = true;
		processor.modulationFreq = freqValue;
		processor.setParameter(1, freqValue);
	}
	
}

void VibratoPluginAudioProcessorEditor::buttonClicked(Button* clickedButton) {
	
	if (clickedButton == &toggleButton) {
	    bool byPassState = toggleButton.getToggleState();
	    if(byPassState == true){
	        processor.setParameter(0, 0.0f);
	        processor.setParameter(1, 0.0f);
	        modulationWidth.setValue(0);
	        modulationFrequency.setValue(0);
	    }    
		processor.pluginByPass = byPassState;
	
	}
}
//==============================================================================
void VibratoPluginAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Plugin Sliders", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void VibratoPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    modulationWidth.setBounds (40, 30, 20, getHeight() - 60);
    modulationFrequency.setBounds(120,30, 20, getHeight() - 60);
    toggleButton.setBounds(200, 150, 200, 30);
}
