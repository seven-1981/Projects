#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
#include <fstream>

#include "Audio/AudioCardLister.hpp"
#include "Audio/ALSACardInfoGetter.hpp"
#include "Audio/ALSACardInfo.hpp"
#include "Audio/ALSACardConfigurator.hpp"
#include "Audio/AudioCardManager.hpp"
#include "Audio/ALSACardConfiguration.hpp"
#include "AudioRecorder.hpp"
#include "ALSARecordingService.hpp"
#include "Buffer.hpp"
#include "Audio/Wavfiles/WavFile.hpp"


void set_console_location(int col, int row)
{
	//We use special escape sequences to control the cursor
	//Note: this part is probably only Linux compatible
	std::cout << "\033[" << std::to_string(row) << ";" << std::to_string(col) << "H" << std::flush;
}
	      
int main (int argc, char **argv)
{
	//Clear screen
	std::cout << "\033[2J\033[1;1H";
	
	AudioCardLister lister;
	ALSACardInfoGetter infoGetter;
	lister.init(&infoGetter);
	ALSACardConfigurator configurator;
	AudioCardManager manager;
	manager.init_lister(&lister);
	manager.init_configurator(&configurator);
	ALSACardConfiguration_t config;
	std::cout << "select_and_configure() = " <<(int)manager.select_and_configure(config) << std::endl;

	std::vector<ALSACardInfo_t> cardInfo = lister.get_cardInfos();
	unsigned int n = cardInfo.size();
	std::cout << "Num of soundcards: " << n << std::endl;
	for (unsigned int i = 0; i < n; ++i)
	{
		std::cout << "Sound card " << i << ": " << cardInfo.at(i).name << std::endl;
	}

	AudioRecorder recorder;
	ALSARecordingService service;
	recorder.init(&service);
	std::cout << "Preparing = " << (int)recorder.prepare_recorder(config) << std::endl;
	Buffer<short unsigned int> buffer;
	std::cout << "Capture = " << (int)recorder.capture_samples(config, buffer) << std::endl;

	WavHeader_t header;
	std::fstream fs("/home/pi/CPP/BPMDetector/record.wav", std::ios_base::out | std::ios_base::binary);
	WavFile wavfile(fs);
	wavfile.write_header(header);
	for (unsigned int i = 0; i < buffer.get_size(); ++i)
	{
		wavfile << buffer[i];
	}
	wavfile.finish();
	fs.close();

	return 0;
}
