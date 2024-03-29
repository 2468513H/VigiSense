#include <cstdint>
#include <chrono>
#include "MAX30102.h"

//Code refactored from HeartRate.h

class sensor{
	public:
		
		sensor();
		~sensor();
		//Check which functions are fine as is and which need editing/removing
		void begin();
		void stop();
		int getSafeIRHeartRate();
		int getLatestIRHeartRate();
		int getLatestRedHeartRate();
		float getLatestTemperatureF();
		void HRcalc();
		void stopHRcalc();
		int getSpO2();
	private:
		MAX30102* _sensor;
		bool running = false;
		bool runningHR = false;

        //Check which functions are fine as is and which need editing/removing
		
		const int static BPM_BUFFER_SIZE = 100;
		int32_t bpmBuffer[BPM_BUFFER_SIZE];
		int nextBPMBufferIndex = 0;
		
		const int static SPO2_BUFFER_SIZE = 100;
		int32_t spo2Buffer[SPO2_BUFFER_SIZE];
		int nextSPO2BufferIndex = 0;

		std::chrono::time_point<std::chrono::system_clock> timeLastLoopRan;
		// IR Data
		std::chrono::time_point<std::chrono::system_clock> timeLastIRHeartBeat;
		int32_t irLastValue; 
		int latestIRBPM;
		int averageIRBPM;
		// Red Data
		std::chrono::time_point<std::chrono::system_clock> timeLastRedHeartBeat;
		uint64_t redLastValue; 
		int latestRedBPM;
		// Temperature Data
		float latestTemperature = -999;

		// For Peak Detection
		int32_t localMaximaIR;
		int32_t localMinimaIR;
		int32_t localMaximaRed;
		int32_t localMinimaRed;
		const static int8_t PAST_PEAKS_SIZE = 2;
		int32_t pastMaximasIR[PAST_PEAKS_SIZE];
		int32_t pastMinimasIR[PAST_PEAKS_SIZE];
		int32_t pastMaximasRed[PAST_PEAKS_SIZE];
		int32_t pastMinimasRed[PAST_PEAKS_SIZE];
		// SpO2 data
		int R;
		int latestSpO2;


		void loopThread();
		void runHRCalculationLoop();
		void updateTemperature();
		void resetCalculations();
		int32_t Derivative(int32_t data);
		int32_t getPeakThreshold();
		bool peakDetect(int32_t data);
};
