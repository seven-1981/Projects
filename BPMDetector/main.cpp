#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
#include <alsa/asoundlib.h>

#include "Audio/AudioCardLister.hpp"
#include "Audio/ALSACardInfoGetter.hpp"
#include "Audio/ALSACardInfo.hpp"
#include "Audio/ALSACardConfigurator.hpp"
#include "Audio/AudioCardManager.hpp"


//Global data for audio capture
snd_pcm_t *capture_handle;
unsigned int sample_rate = 44100;
//Total frame size
unsigned int num_frames_tot = 1024;
//Frame size of one window
unsigned int num_frames_rec = 256;
//Number of bins considered in calculation
const int fft_bins = 120;
//Number of bins displayed in graph
int fft_bars = 11;

//Buffer for audio data
short* buf = (short*)malloc(num_frames_rec * sizeof(short));

//Capture callback
int capture_callback (snd_pcm_sframes_t nframes)
{
	int err;
	if ((err = snd_pcm_readi(capture_handle, buf, nframes)) < 0) {
		std::cout << "write failed " << snd_strerror(err) << std::endl;
	}
	return err;
}

void set_console_location(int col, int row)
{
	//We use special escape sequences to control the cursor
	//Note: this part is probably only Linux compatible
	std::cout << "\033[" << std::to_string(row) << ";" << std::to_string(col) << "H" << std::flush;
}

void init_audio()
{
	//Parameters
	snd_pcm_hw_params_t *hw_params;
	snd_pcm_sw_params_t *sw_params;
	snd_pcm_sframes_t frames_to_deliver;

	int err;
	std::string card_name = "hw:1,0";

	if ((err = snd_pcm_open(&capture_handle, card_name.c_str(), SND_PCM_STREAM_CAPTURE, 0)) < 0) {
		std::cout << "cannot open audio device " << snd_strerror(err) << std::endl; 
		exit(1);
	}
		   
	if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
		std::cout << "cannot allocate hardware parameter structure " << snd_strerror(err) << std::endl;
		exit(1);
	}
				 
	if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
		std::cout << "cannot initialize hardware parameter structure " << snd_strerror(err) << std::endl;
		exit(1);
	}
	
	if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		std::cout << "cannot set access type " << snd_strerror(err) << std::endl;
		exit(1);
	}
	
	if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		std::cout << "cannot set sample format " << snd_strerror(err) << std::endl;
		exit(1);
	}
	
	if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &sample_rate, 0)) < 0) {
		std::cout << "cannot set sample rate " << snd_strerror(err) << std::endl;
		exit(1);
	}
	
	if ((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 1)) < 0) {
		std::cout << "cannot set channel count " << snd_strerror(err) << std::endl;
		exit(1);
	}
	
	if ((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
		std::cout << "cannot set parameters " << snd_strerror(err) << std::endl;
		exit(1);
	}
	
	snd_pcm_hw_params_free(hw_params);
	
	/* tell ALSA to wake us up whenever num_frames or more frames
	   of capture data can be delivered. Also, tell
	   ALSA that we'll start the device ourselves.
	*/
	
	if ((err = snd_pcm_sw_params_malloc(&sw_params)) < 0) {
		std::cout << "cannot allocate software parameters structure " << snd_strerror(err) << std::endl;
		exit(1);
	}

	if ((err = snd_pcm_sw_params_current(capture_handle, sw_params)) < 0) {
		std::cout << "cannot initialize software parameters structure " << snd_strerror(err) << std::endl;
		exit(1);
	}

	if ((err = snd_pcm_sw_params_set_avail_min(capture_handle, sw_params, num_frames_rec)) < 0) {
		std::cout << "cannot set minimum available count " << snd_strerror(err) << std::endl;
		exit(1);
	}

	if ((err = snd_pcm_sw_params_set_start_threshold(capture_handle, sw_params, 0U)) < 0) {
		std::cout << "cannot set start mode " << snd_strerror(err) << std::endl;
		exit(1);
	}

	if ((err = snd_pcm_sw_params(capture_handle, sw_params)) < 0) {
		std::cout << "cannot set software parameters " << snd_strerror(err) << std::endl;
		exit(1);
	}
	
	/* the interface will interrupt the kernel every 4096 frames, and ALSA
	   will wake up this program very soon after that.
	*/
	
	if ((err = snd_pcm_prepare(capture_handle)) < 0) {
		std::cout << "cannot prepare audio interface for use " << snd_strerror(err) << std::endl;
		exit(1);
	}

	if ((err = snd_pcm_start(capture_handle)) < 0) {
		std::cout << "cannot start capturing " << snd_strerror(err) << std::endl;
		exit(1);
	}
}
	      
int main (int argc, char **argv)
{
	AudioCardLister lister;
	ALSACardInfoGetter infoGetter;
	lister.init(&infoGetter);
	ALSACardConfigurator configurator;
	AudioCardManager manager;
	manager.init_lister(&lister);
	manager.init_configurator(&configurator);
	manager.select_and_configure(); 
	
	//Clear screen
	std::cout << "\033[2J\033[1;1H";

	//Write found config
	std::vector<ALSACardInfo_t> cardInfo = lister.get_cardInfos();
	unsigned int n = cardInfo.size();
	std::cout << "Num of soundcards: " << n << std::endl;
	for (unsigned int i = 0; i < n; ++i)
	{
		std::cout << "Sound card " << i << ": " << cardInfo.at(i).name << std::endl;
	}

	// //Init audio device
	// init_audio();

	// int err;
	// snd_pcm_sframes_t frames_to_deliver; 
	
	// int cycles = 0;
	// while(cycles++ < 100) 
	// {
	
	// 	/* wait till the interface is ready for data, or 1 second
	// 	   has elapsed.
	// 	*/
	
	// 	if ((err = snd_pcm_wait(capture_handle, 1000)) < 0) {
	// 	        std::cout << "poll failed " << snd_strerror(err) << std::endl;
	// 	        break;
	// 	}	           
	
	// 	/* find out how much space is available for playback data */
	
	// 	if ((frames_to_deliver = snd_pcm_avail_update(capture_handle)) < 0) {
	// 		if (frames_to_deliver == -EPIPE) {
	// 			std::cout << "an xrun occured" << std::endl;
	// 			break;
	// 		} else {
	// 			std::cout << "unknown ALSA avail update return value" << std::endl;
	// 			break;
	// 		}
	// 	}

	// 	std::cout << "Frames to deliver: " << frames_to_deliver << std::endl;
	
	// 	frames_to_deliver = frames_to_deliver > num_frames_rec ? num_frames_rec : frames_to_deliver;
	
	// 	/* deliver the data */
	
	// 	if (capture_callback(frames_to_deliver) != frames_to_deliver) {
	// 	        std::cout << "capture callback failed" << std::endl;
	// 		break;
	// 	}
	// }
	
	// snd_pcm_close(capture_handle);
	
	

	return 0;
}

