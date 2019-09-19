#include "FakeRecordingService.hpp"

#include "globals.hpp"
#include "ALSACardConfiguration.hpp"


const int RETURN_EBADFD = -77;  //Values from ALSA library
const int RETURN_EPIPE = -32;
const int RETURN_ESTRPIPE = -86;
const int RETURN_EAGAIN = -11;
const int RETURN_NO_ERROR = 0;
const int RETURN_ANY_ERROR = -1;

const int RECOVER_SILENT = 1;


Errors_e FakeRecordingService::set_handle(GEN_CARD_CONFIG_TYPE& config)
{
    CARD_CONFIG_TYPE& typedConfig = dynamic_cast<CARD_CONFIG_TYPE&>(config);
    if (typedConfig.INITIALIZED == true)
    {
        m_isHandleSet = true;
        return Errors_e::NO_ERROR;
    }
    else
    {
        return Errors_e::AUDIO_RECORDER_NOT_INITIALIZED;
    }
    return Errors_e::NO_ERROR;
}

bool FakeRecordingService::is_handleSet()
{
    return m_isHandleSet;
}

int FakeRecordingService::pcm_readi(void* buffer, int size)
{
    switch (m_state)
    {
        case State_CaptureSuccess:
            return size;
            break;

        case State_CaptureReturns_EBADFD_RecoverNotPossible:
            IGNORE pcm_drop();
            return pcm_recover(RETURN_EBADFD, RECOVER_SILENT);
            break;

        case State_CaptureReturns_EPIPE_RecoverError:
        case State_CaptureReturns_EPIPE_RecoverSuccess:
            IGNORE pcm_drop();
            return pcm_recover(RETURN_EPIPE, RECOVER_SILENT);
            break;

        case State_CaptureReturns_ESTRPIPE_RecoverError:
        case State_CaptureReturns_ESTRPIPE_RecoverSuccess:
            IGNORE pcm_drop();
            return pcm_recover(RETURN_ESTRPIPE, RECOVER_SILENT);
            break;
        
        default:
            return RETURN_ANY_ERROR;
            break;
    }
}

int FakeRecordingService::pcm_drop()
{
    //Drop return value is ignored, we set it to error 
    //to remind us when that behaviour changes
    return RETURN_ANY_ERROR;
}

int FakeRecordingService::pcm_recover(int err, int silent)
{
    switch (m_state)
    {
        case State_CaptureSuccess:
            //pcm_recover is not called upon success
            return RETURN_ANY_ERROR;
            break;

        case State_CaptureReturns_EBADFD_RecoverNotPossible:
            return RETURN_EBADFD;
            break;

        case State_CaptureReturns_EPIPE_RecoverError:
            return RETURN_EPIPE;
            break;

        case State_CaptureReturns_EPIPE_RecoverSuccess:
            return RETURN_NO_ERROR;
            break;

        case State_CaptureReturns_ESTRPIPE_RecoverError:
            return RETURN_ESTRPIPE;
            break;

        case State_CaptureReturns_ESTRPIPE_RecoverSuccess:
            return RETURN_NO_ERROR;
            break;

        default:
            return RETURN_ANY_ERROR;
            break;        
    }
}

void FakeRecordingService::set_state(FakeRecordingServiceStates_e state)
{
	m_state = state;
}
