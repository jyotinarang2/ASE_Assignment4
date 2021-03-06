/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#define MODWIDTH 0
#define MODFREQ 1

//==============================================================================
VibratoPluginAudioProcessorEditor::VibratoPluginAudioProcessorEditor (VibratoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
        // these define the parameters of our slider object
    modulationWidth.setSliderStyle (Slider::LinearBarVertical);
    modulationWidth.setRange(0, 1, 0.01);
    modulationWidth.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    modulationWidth.setPopupDisplayEnabled (true, false, this);
    modulationWidth.setTextValueSuffix (" Modulation Width");
    modulationWidth.setValue(0.01);
	
	modulationWidth.addListener(this);
	addAndMakeVisible(widthLabel);
	widthLabel.setText("Width(Sec)", dontSendNotification);
	widthLabel.attachToComponent(&modulationWidth, true);
    // this function adds the slider to the editor
    addAndMakeVisible (&modulationWidth);
    modulationFrequency.setSliderStyle (Slider::LinearBarVertical);
    modulationFrequency.setRange(0, 7, 0.01);
    modulationFrequency.setTextBoxStyle (Slider::NoTextBox, false, 90, 0);
    modulationFrequency.setPopupDisplayEnabled (true, false, this);
    modulationFrequency.setTextValueSuffix (" Modulation Frequency");
    modulationFrequency.setValue(5);
	modulationFrequency.addListener(this);
	addAndMakeVisible(freqLabel);
	freqLabel.setText("Freq(Hz)", dontSendNotification);
	freqLabel.attachToComponent(&modulationFrequency, true);
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
		processor.setParameter(MODWIDTH, widthValue);
	}
	else if (slider == &modulationFrequency) {
		float freqValue = modulationFrequency.getValue();
		processor.setParameter(MODFREQ, freqValue);
	}
	
}

void VibratoPluginAudioProcessorEditor::buttonClicked(Button* clickedButton) {
	
	if (clickedButton == &toggleButton) {
	    bool byPassState = toggleButton.getToggleState();
		processor.setParamByPass(byPassState);
	
	}
}
//==============================================================================
void VibratoPluginAudioProcessorEditor::paint(Graphics& g)

{

	// (Our component is opaque, so we must completely fill the background with a solid colour)

	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
	g.setColour(Colours::orange);
	g.setFont(20.0f);
	g.drawFittedText("Bypass vibrato", -100, 20, getWidth(), 30, Justification::centred, 1);
}



void VibratoPluginAudioProcessorEditor::resized()

{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..

	modulationWidth.setBounds(200, 30, 50, getHeight() - 60);
	modulationFrequency.setBounds(320, 30, 50, getHeight() - 60);
	toggleButton.setBounds(90, 55, 30, 30);

}