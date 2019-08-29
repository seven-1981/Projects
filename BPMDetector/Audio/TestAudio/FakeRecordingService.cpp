#include "FakeRecordingService.hpp"


const int RETURN_EBADFD = -77;  //Values from ALSA library
const int RETURN_EPIPE = -32;
const int RETURN_ESTRPIPE = -86;
const int RETURN_NO_ERROR = 0;
const int RETURN_ANY_ERROR = -1;


int FakeRecordingService::pcm_readi(int size)
{
    switch (m_state)
    {
        case State_CaptureSuccess:
            return size;
            break;

        case State_CaptureReturns_EBADFD_DropError:
	    case State_CaptureReturns_EBADFD_DropSuccess_RecoverError:
	    case State_CaptureReturns_EBADFD_DropSuccess_RecoverSuccess:
            if (pcm_drop() < 0)
                return RETURN_EBADFD;
            if (pcm_recover() < 0)
                return RETURN_EBADFD;
            else
                return size;
            break;

        case State_CaptureReturns_EPIPE_RestSuccessful:
            return RETURN_EPIPE;
            break;

	    case State_CaptureReturns_ESTRPIPE_RestSuccessful:
            return RETURN_ESTRPIPE;
            break;
        
        default:
            return RETURN_EBADFD;
            break;
    }
}

int FakeRecordingService::pcm_drop()
{
    switch (m_state)
    {
        case State_CaptureSuccess:
            //Should not happen, therefore error
            return RETURN_ANY_ERROR;
            break;

        case State_CaptureReturns_EBADFD_DropError:
            return RETURN_ANY_ERROR;
            break;

	    case State_CaptureReturns_EBADFD_DropSuccess_RecoverError:
	    case State_CaptureReturns_EBADFD_DropSuccess_RecoverSuccess:
            return RETURN_NO_ERROR;
            break;

        case State_CaptureReturns_EPIPE_RestSuccessful:
	    case State_CaptureReturns_ESTRPIPE_RestSuccessful:
            return RETURN_NO_ERROR;
            break;
        
        default:
            return RETURN_ANY_ERROR;
            break;        
    }
}

int FakeRecordingService::pcm_recover()
{
    switch (m_state)
    {
        case State_CaptureSuccess:
        case State_CaptureReturns_EBADFD_DropError:
            //Should not happen, therefore error
            return RETURN_ANY_ERROR;
            break;

	    case State_CaptureReturns_EBADFD_DropSuccess_RecoverError:
            return RETURN_ANY_ERROR;
            break;

	    case State_CaptureReturns_EBADFD_DropSuccess_RecoverSuccess:
            return RETURN_NO_ERROR;
            break;

        case State_CaptureReturns_EPIPE_RestSuccessful:
	    case State_CaptureReturns_ESTRPIPE_RestSuccessful:
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
