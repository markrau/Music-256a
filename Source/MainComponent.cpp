// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
//
// Author: Mark Rau - mrau@ccrma.stanford.edu   (based on code by Romain Michon - rmichonATccrmaDOTstanfordDOTedu)
// Description: Addative synthesizer with 5 oscillators. Each oscillator has
// a frequency and gain control. The oscillator can also be played with an external 
// input on channel 0. There is a master gain control for all oscillators (but not the external input). 
// The "snap harmonic" button forces oscillators 2-5 to be the closest frequency to their slider value 
// which is a harmonic of slider 1.






// Author: Romain Michon (rmichonATccrmaDOTstanfordDOTedu)
// Description: Simple JUCE sine wave synthesizer

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sine.h"

class MainContentComponent :
    public AudioAppComponent,
    private Slider::Listener,
    private ToggleButton::Listener
{
public:
    MainContentComponent() : MasterGain (0.5), onOff (0), samplingRate(0.0), instOnOff (0), snap (0)
    {
        // configuring frequency 1 slider and adding it to the main window
        addAndMakeVisible (frequencySlider[0]);
        frequencySlider[0].setRange (50.0, 5000.0);
        frequencySlider[0].setSkewFactorFromMidPoint (500.0);
        frequencySlider[0].setValue(200); // will also set the default frequency of the sine osc
        frequencySlider[0].addListener (this);
        
        // configuring frequency 1 label box and adding it to the main window
        addAndMakeVisible(frequencyLabel1);
        frequencyLabel1.setText ("Frequency 1", dontSendNotification);
        frequencyLabel1.attachToComponent (&frequencySlider[0], true);

		// configuring frequency 2 slider and adding it to the main window
		addAndMakeVisible(frequencySlider[1]);
		frequencySlider[1].setRange(50.0, 5000.0);
		frequencySlider[1].setSkewFactorFromMidPoint(500.0);
		frequencySlider[1].setValue(400); // will also set the default frequency of the sine osc
		frequencySlider[1].addListener(this);

		// configuring frequency 2 label box and adding it to the main window
		addAndMakeVisible(frequencyLabel2);
		frequencyLabel2.setText("Frequency2", dontSendNotification);
		frequencyLabel2.attachToComponent(&frequencySlider[1], true);

		// configuring frequency 3 slider and adding it to the main window
		addAndMakeVisible(frequencySlider[2]);
		frequencySlider[2].setRange(50.0, 5000.0);
		frequencySlider[2].setSkewFactorFromMidPoint(500.0);
		frequencySlider[2].setValue(800); // will also set the default frequency of the sine osc
		frequencySlider[2].addListener(this);

		// configuring frequency 3 label box and adding it to the main window
		addAndMakeVisible(frequencyLabel3);
		frequencyLabel3.setText("Frequency 3", dontSendNotification);
		frequencyLabel3.attachToComponent(&frequencySlider[2], true);

		// configuring frequency 4 slider and adding it to the main window
		addAndMakeVisible(frequencySlider[3]);
		frequencySlider[3].setRange(50.0, 5000.0);
		frequencySlider[3].setSkewFactorFromMidPoint(500.0);
		frequencySlider[3].setValue(1000); // will also set the default frequency of the sine osc
		frequencySlider[3].addListener(this);

		// configuring frequency 4 label box and adding it to the main window
		addAndMakeVisible(frequencyLabel4);
		frequencyLabel4.setText("Frequency 4", dontSendNotification);
		frequencyLabel4.attachToComponent(&frequencySlider[3], true);

		// configuring frequency 5 slider and adding it to the main window
		addAndMakeVisible(frequencySlider[4]);
		frequencySlider[4].setRange(50.0, 5000.0);
		frequencySlider[4].setSkewFactorFromMidPoint(500.0);
		frequencySlider[4].setValue(1200); // will also set the default frequency of the sine osc
		frequencySlider[4].addListener(this);

		// configuring frequency 5 label box and adding it to the main window
		addAndMakeVisible(frequencyLabel5);
		frequencyLabel5.setText("Frequency 5", dontSendNotification);
		frequencyLabel5.attachToComponent(&frequencySlider[4], true);
        
        
        // configuring gain slider 1 and adding it to the main window
        addAndMakeVisible (gainSlider[0]);
        gainSlider[0].setRange (0.0, 0.2);
        gainSlider[0].setValue(0.5); // will alsi set the default gain of the sine osc
        gainSlider[0].addListener (this);
        
        // configuring gain label 1 and adding it to the main window
        addAndMakeVisible(gainLabel1);
        gainLabel1.setText ("Gain", dontSendNotification);
        gainLabel1.attachToComponent (&gainSlider[0], true);

		// configuring gain slider 2 and adding it to the main window
		addAndMakeVisible(gainSlider[1]);
		gainSlider[1].setRange(0.0, 0.2);
		gainSlider[1].setValue(0.5); // will alsi set the default gain of the sine osc
		gainSlider[1].addListener(this);

		// configuring gain label 2 and adding it to the main window
		addAndMakeVisible(gainLabel2);
		gainLabel2.setText("Gain", dontSendNotification);
		gainLabel2.attachToComponent(&gainSlider[1], true);

		// configuring gain slider 3 and adding it to the main window
		addAndMakeVisible(gainSlider[2]);
		gainSlider[2].setRange(0.0, 0.2);
		gainSlider[2].setValue(0.5); // will alsi set the default gain of the sine osc
		gainSlider[2].addListener(this);

		// configuring gain label 3 and adding it to the main window
		addAndMakeVisible(gainLabel3);
		gainLabel3.setText("Gain", dontSendNotification);
		gainLabel3.attachToComponent(&gainSlider[2], true);

		// configuring gain slider 4 and adding it to the main window
		addAndMakeVisible(gainSlider[3]);
		gainSlider[3].setRange(0.0, 0.2);
		gainSlider[3].setValue(0.5); // will alsi set the default gain of the sine osc
		gainSlider[3].addListener(this);

		// configuring gain label 4 and adding it to the main window
		addAndMakeVisible(gainLabel4);
		gainLabel4.setText("Gain", dontSendNotification);
		gainLabel4.attachToComponent(&gainSlider[3], true);

		// configuring gain slider 5 and adding it to the main window
		addAndMakeVisible(gainSlider[4]);
		gainSlider[4].setRange(0.0, 0.2);
		gainSlider[4].setValue(0.5); // will alsi set the default gain of the sine osc
		gainSlider[4].addListener(this);

		// configuring gain label 5 and adding it to the main window
		addAndMakeVisible(gainLabel5);
		gainLabel5.setText("Gain", dontSendNotification);
		gainLabel5.attachToComponent(&gainSlider[4], true);


		// configuring gain slider for overall volume and adding it to the main window
		addAndMakeVisible(gainSliderMaster);
		gainSliderMaster.setRange(0.0, 1.0);
		gainSliderMaster.setValue(0.5); // will alsi set the default gain of the sine osc
		gainSliderMaster.addListener(this);

		// configuring gain label for master volume and adding it to the main window
		addAndMakeVisible(gainLabelMaster);
		gainLabelMaster.setText("Master Volume", dontSendNotification);
		gainLabelMaster.attachToComponent(&gainSliderMaster, true);


		// configuring external instrument on/off button and adding it to the main window
		addAndMakeVisible(instButton);
		instButton.addListener(this);

		// configuring external instrument on/off label and adding it to the main window
		addAndMakeVisible(instLabel);
		instLabel.setText("External Input", dontSendNotification);
		instLabel.attachToComponent(&instButton, true);


		// configuring Snap to harmonic button and adding it to the main window
		addAndMakeVisible(snapButton);
		snapButton.addListener(this);

		// configuring snap to harmonis label and adding it to the main window
		addAndMakeVisible(snapLabel);
		snapLabel.setText("Snap Harmonic", dontSendNotification);
		snapLabel.attachToComponent(&snapButton, true);
        
        
        // configuring on/off button and adding it to the main window
        addAndMakeVisible(onOffButton);
        onOffButton.addListener(this);
        
        
        // configuring on/off label and adding it to the main window
        addAndMakeVisible(onOffLabel);
        onOffLabel.setText ("On/Off", dontSendNotification);
        onOffLabel.attachToComponent (&onOffButton, true);
        
        setSize (600, 100);
        nChans = 1;
		nInputs = 1;
        setAudioChannels (nInputs, nChans); // one input, one output
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void resized() override
    {
        // placing the UI elements in the main window
        // getWidth has to be used in case the window is resized by the user
        const int sliderLeft = 80;
		gainSliderMaster.setBounds(sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
        frequencySlider[0].setBounds (sliderLeft, 70, getWidth() - sliderLeft - 20, 20);
		gainSlider[0].setBounds(sliderLeft, 100, getWidth() - sliderLeft - 20, 20);
		frequencySlider[1].setBounds(sliderLeft, 130, getWidth() - sliderLeft - 20, 20);
		gainSlider[1].setBounds(sliderLeft, 160, getWidth() - sliderLeft - 20, 20);
		frequencySlider[2].setBounds(sliderLeft, 190, getWidth() - sliderLeft - 20, 20);
		gainSlider[2].setBounds(sliderLeft, 220, getWidth() - sliderLeft - 20, 20);
		frequencySlider[3].setBounds(sliderLeft, 250, getWidth() - sliderLeft - 20, 20);
		gainSlider[3].setBounds(sliderLeft, 280, getWidth() - sliderLeft - 20, 20);
		frequencySlider[4].setBounds(sliderLeft, 310, getWidth() - sliderLeft - 20, 20);
        gainSlider[4].setBounds (sliderLeft, 340, getWidth() - sliderLeft - 20, 20);
        onOffButton.setBounds (sliderLeft, 370, getWidth() - sliderLeft - 20, 20);
		instButton.setBounds(sliderLeft, 420, getWidth() - sliderLeft - 20, 20);
		snapButton.setBounds(sliderLeft, 470, getWidth() - sliderLeft - 20, 20);
    }
    
    void sliderValueChanged (Slider* slider) override
	// Check to see if the sliders are changed
    {
        if (samplingRate > 0.0){
			for (int i = 0; i < 5; i++) {
				if (slider == &frequencySlider[i] && snap ==0) {
					sine[i].setFrequency(frequencySlider[i].getValue());
				}
				else if (slider == &frequencySlider[i] && snap == 1) { // if the snap button is pressed, keep all oscillators as harmonics of the first oscillator
					for (int i = 1; i < 5; i++) { 
						sine[i].setFrequency(frequencySlider[i].getValue() - fmod(frequencySlider[i].getValue(), frequencySlider[0].getValue()));
					}
				}
				if (slider == &gainSlider[i]) {
					gain[i] = gainSlider[i].getValue();
				}
			}
            if (slider == &gainSliderMaster){
                MasterGain = gainSliderMaster.getValue();
            }
        }
    }
    
    void buttonClicked (Button* button) override
    {
        // turns audio on or off
        if(button == &onOffButton && onOffButton.getToggleState()){
            onOff = 1;
        }
        else if (button ==&onOffButton){
            onOff = 0;
        }
		if (button == &instButton && instButton.getToggleState()) {
			instOnOff = 1;
		}
		else if (button == &instButton){
			instOnOff = 0;
		}
		if (button == &snapButton && snapButton.getToggleState()) { // if the snap button is pressed, initially snap all the oscillators to be harmonics of the first oscillator
			snap = 1;
			for (int i = 1; i < 5; i++) {
				sine[i].setFrequency(frequencySlider[i].getValue() - fmod(frequencySlider[i].getValue(), frequencySlider[0].getValue()));
			}
		}
		else if (button == &snapButton) {
			snap = 0;
		}
    }
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        samplingRate = sampleRate;
		for (int i = 0; i < 5; i++) {
			sine[i].setSamplingRate(sampleRate);
		}
    }
    
    void releaseResources() override
    {
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
		//get audio input buffer
		const float* inBuffer = bufferToFill.buffer->getReadPointer(0,bufferToFill.startSample);

        // getting the audio output buffer to be filled
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);

        
        // computing one block
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
			if (onOff == 1) {
				if (instOnOff == 1) {  //if the input is on, allow it's sound and the synth to pass through
					buffer[sample] = inBuffer[sample] + (sine[0].tick() * gain[0] + sine[1].tick() * gain[1] + sine[2].tick() * gain[2] + sine[3].tick() * gain[3] + sine[4].tick() * gain[4])*MasterGain;
				}
				else {  // if the instrument is off, only allow the synth to be output
					buffer[sample] = (sine[0].tick() * gain[0] + sine[1].tick() * gain[1] + sine[2].tick() * gain[2] + sine[3].tick() * gain[3] + sine[4].tick() * gain[4])*MasterGain;
				}
			}
            else buffer[sample] = 0.0;
        }
    }
    
    
private:
    // UI Elements
	Slider gainSliderMaster;
    Slider frequencySlider[5];
    Slider gainSlider[5];
    ToggleButton onOffButton;
	ToggleButton instButton;
	ToggleButton snapButton;
    
    Label gainLabelMaster, frequencyLabel1, frequencyLabel2, frequencyLabel3, frequencyLabel4, frequencyLabel5, gainLabel1, gainLabel2, gainLabel3, gainLabel4, gainLabel5, onOffLabel, instLabel, snapLabel;
    
    Sine sine[5]; // Array of 5 sine wave oscillators
	float gain[5]; // Array of 5 sine wave gains
    
    // Global Variables
    float MasterGain; // gain which controls all oscillators
    int onOff, samplingRate, nChans, nInputs, instOnOff, snap;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
