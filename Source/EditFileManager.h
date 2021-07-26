
#pragma once

#include <JuceHeader.h>
#include "common/Utilities.h"
#include "StepSequencerDemo.h"

//==============================================================================
/*
*/
class EditFileManager  : public juce::Component
{
public:
    EditFileManager()
    {
        Helpers::addAndMakeVisible (*this, { &newProjectButton, &closeProjectButton, &loadProjectButton, &saveProjectButton, &saveAsProjectButton });

        newProjectButton.onClick  = [this] {
            stepSequencer = std::make_unique<StepSequencerDemo>();
            stepSequencer->setBounds(0, 30, 600, 400);
            addAndMakeVisible(stepSequencer.get());
        };
        
        closeProjectButton.onClick = [this] {
            if(stepSequencer != nullptr)
            {
                removeChildComponent(stepSequencer.get());
                stepSequencer.reset();
            }
        };
        
        loadProjectButton.onClick = [this] {
            editFile = new juce::File(juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("TestTracktionFile.xml"));
            stepSequencer = std::make_unique<StepSequencerDemo>(editFile);
            stepSequencer->setBounds(0, 30, 600, 400);
            addAndMakeVisible(stepSequencer.get());
        };
        
        saveProjectButton.onClick = [this] {
            if(stepSequencer)
            {
                te::EditFileOperations(*stepSequencer->edit).save(true, false, true);
            }
        };
        
        saveAsProjectButton.onClick = [this] {
            if(stepSequencer)
            {
                editFile = new juce::File(juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("TestTracktionFile_new_Version.xml"));
                te::EditFileOperations(*stepSequencer->edit).writeToFile(*editFile, false);
            }
        };
        
        setSize (600, 430);

    }

    ~EditFileManager() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    }

    void resized() override
    {
        auto r = getLocalBounds();
        r.setHeight(30);

        newProjectButton.setBounds (r.removeFromLeft(120).reduced (2));
        closeProjectButton.setBounds (r.removeFromLeft(120).reduced (2));
        loadProjectButton.setBounds (r.removeFromLeft(120).reduced (2));
        saveProjectButton.setBounds (r.removeFromLeft(120).reduced (2));
        saveAsProjectButton.setBounds (r.removeFromLeft(120).reduced (2));

    }

private:
    
    TextButton  newProjectButton { "New Project" },
                closeProjectButton { "Close Project" },
                loadProjectButton { "Load Project" },
                saveProjectButton { "Save Project" },
                saveAsProjectButton { "SaveAs Project" } ;
    
    std::unique_ptr<StepSequencerDemo> stepSequencer;
    
    juce::File* editFile;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditFileManager)
};
