#ifndef __ABSTRACTCOMUNICATIONTASK__
#define __ABSTRACTCOMUNICATIONTASK__
#include "Task.h"
#include "Listeners.h"
#include "CommonSettings.h"
#include "event.h"

#define MAX_MESSAGE_LISTENERS 5

class AbstractComunicationTask : public Task, public MessageEventSource {
public:
    /* to add a new listener */
    bool addListener(MessageListener* listener) {
        if (nListeners < MAX_MESSAGE_LISTENERS) {
            this->listeners[nListeners++] = listener;
            return true;
        }
        else {
            return false;
        }
    }
protected:
    AbstractComunicationTask() {
        this->nListeners = 0;
    }

    int nListeners;
    MessageListener* listeners[MAX_MESSAGE_LISTENERS];
};

#endif

