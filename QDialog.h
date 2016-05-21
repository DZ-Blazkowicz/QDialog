
#ifndef __QDIALOG_H
#define __QDIALOG_H

// tolua_begin

namespace dialog {

    bool isAvailable();
    const char* getErrorString();
    int getError();
    bool alertBox(const char*, const char*, int, int, const char*, const char*, const char*);
    bool isOpen(int nId);
    bool close(int nId);
    void start();
    void stop();
    
} //namespace dialog

// tolua_end

#endif // QDIALOG_H
