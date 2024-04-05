#pragma once
#include "DiagnosisInterface.h"
#include "Sensor.h"
#include <thread>

class SPO2Tracker:public diagnosisInterface {
    public:
        SPO2Tracker(testParent *s);
        /**
         * 0. find what functions are called from the true constructor above (in this case: CTRL+F on _s(variable saved with the instance), then see which functions are called)
         * 1. make constructor for with input from new class
         * 2. make the new class with the constructor name, and the function mentioned in 0
         * 3. in the cpp file for this header, define the constructor with the new class
         * 4. define the function mentioned in 0 for the test class
         * 
         * */ 
        ~SPO2Tracker();
        void start();
        void stop();
        void ping();
        int getVal();
        void tracker();
        testParent* _s; 
    protected:
        bool threadRunning = false;
        void pingThread();
        // define symptom table here
		std::vector<symptomRange> symptomRanges {
			{0,88,"Critically Low Oxygen concentration"},
			{88,92,"Concerningly Low Oxygen Concentration"},
			{92,100,"Healthy Oxygen Concentration"}};

};