
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
            if(stepSequencer != nullptr)
            {
                removeChildComponent(stepSequencer.get());
                stepSequencer.reset();
            }
            stepSequencer = std::make_unique<StepSequencerDemo>(engine);
            stepSequencer->setBounds(0, 30, getWidth(), getHeight()-30);
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
            fileChooser.reset (new juce::FileChooser ("Choose a edit file", juce::File::getSpecialLocation(juce::File::userDocumentsDirectory), "*.tracktionedit", true));
            fileChooser->launchAsync (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
                 [this] (const juce::FileChooser& chooser)
                 {
                    if(!this->fileChooser->getURLResult().isEmpty() && this->fileChooser->getURLResult().getLocalFile().exists())
                    {
                        if(stepSequencer != nullptr)
                        {
                            removeChildComponent(stepSequencer.get());
                            stepSequencer.reset();
                        }
                        stepSequencer = std::make_unique<StepSequencerDemo>(engine, this->fileChooser->getURLResult());
                        stepSequencer->setBounds(0, 30, getWidth(), getHeight()-30);
                        addAndMakeVisible(stepSequencer.get());
                    }
                 });
        };
        
        saveProjectButton.onClick = [this] {
            if(stepSequencer)
                te::EditFileOperations(*stepSequencer->edit).save(true, true, true);
        };
        
        saveAsProjectButton.onClick = [this] {
            if(stepSequencer)
                te::EditFileOperations(*stepSequencer->edit).saveAs();
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

        newProjectButton.setBounds (r.removeFromLeft(getWidth()/5).reduced (2));
        closeProjectButton.setBounds (r.removeFromLeft(getWidth()/5).reduced (2));
        loadProjectButton.setBounds (r.removeFromLeft(getWidth()/5).reduced (2));
        saveProjectButton.setBounds (r.removeFromLeft(getWidth()/5).reduced (2));
        saveAsProjectButton.setBounds (r.removeFromLeft(getWidth()/5).reduced (2));

        if(stepSequencer)
            stepSequencer->setBounds(0, 30, getWidth(), getHeight()-30);
        
    }
    

private:
    
    te::Engine engine { ProjectInfo::projectName };
    
    std::unique_ptr<juce::FileChooser> fileChooser;
    
    TextButton  newProjectButton { "New Project" },
                closeProjectButton { "Close Project" },
                loadProjectButton { "Load Project" },
                saveProjectButton { "Save Project" },
                saveAsProjectButton { "SaveAs Project" } ;
    
    std::unique_ptr<StepSequencerDemo> stepSequencer;
    
    juce::File* editFile;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditFileManager)
};
