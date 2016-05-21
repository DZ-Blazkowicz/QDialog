
#include "QDialog.h"
#include "s3eDialog.h"
#include "QLuaHelpers.h"
#include "lua.h"

using namespace quick;

namespace dialog {

//------------------------------------------------------------------------------
//C++ callbacks -> Lua events:

int32 FinishedCallback(s3eDialogCallbackData* data, void* userData)
{
    LUA_EVENT_PREPARE("dialog");
    LUA_EVENT_SET_INTEGER("dialogId", data->m_ButtonPressed);
	LUA_EVENT_SET_INTEGER("buttonPressed", data->m_Id);

    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

//------------------------------------------------------------------------------
//Functions:

bool isAvailable()
{
    return (bool)s3eDialogAvailable();
}

const char* getErrorString()
{
    return s3eDialogGetErrorString();
}

int getError()
{
    return s3eDialogGetError();
}

bool alertBox(const char* message, const char* title, int id, int numberOfButtons, const char* buttonOne, const char * buttonTwo, const char * buttonThree)
{
	s3eDialogAlertInfo info;
	info.m_Message = message;
	info.m_Title = title;
	info.m_Id = id;

	info.m_Button[0] = NULL;
	info.m_Button[1] = NULL;
	info.m_Button[2] = NULL;

	info.m_Button[0] = buttonOne;
	if (numberOfButtons >= 2)
		info.m_Button[1] = buttonTwo;
	if (numberOfButtons >= 3)
		info.m_Button[2] = buttonThree;
    return s3eDialogAlertBox(&info) == S3E_RESULT_SUCCESS ? true : false;
}

bool isOpen(int nId)
{
    return (bool)s3eDialogIsOpen(nId);
}

bool close(int nId)
{
    return s3eDialogClose(nId) == S3E_RESULT_SUCCESS ? true : false;
}

void start()
{
    //Register all callbacks here:
    s3eDialogRegister(S3E_DIALOG_FINISHED, (s3eCallback)FinishedCallback, NULL);
}

void stop()
{
    //Un-register all callbacks here:
    s3eDialogUnRegister(S3E_DIALOG_FINISHED, (s3eCallback)FinishedCallback);
}

} //namespace dialog
