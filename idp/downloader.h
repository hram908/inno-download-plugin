#pragma once

#include <windows.h>
#include <wininet.h>
#include <map>
#include "tstring.h"
#include "netfile.h"
#include "timer.h"
#include "ui.h"
#include "securityoptions.h"

using namespace std;

class Downloader
{
public:
	Downloader();
	~Downloader();

	void      addFile(tstring url, tstring filename, DWORDLONG size = FILE_SIZE_UNKNOWN);
	void      clearFiles();
	bool	  downloadFiles();
	DWORDLONG getFileSizes();
	int       filesCount();
	bool      filesDownloaded();
	DWORD	  getLastError();
	tstring	  getLastErrorStr();
	void      setUI(UI *newUI);
	void      setUserAgent(tstring agent);
	void      setSecurityOptions(SecurityOptions opt);
	void      setCancelPointer(bool *cancel);

protected:
	bool openInternet();
	bool closeInternet();
	bool downloadFile(NetFile *netFile);
	void updateProgress(NetFile *file);
	void updateFileName(NetFile *file);
	void updateSpeed(NetFile *file, Timer *timer);
	void updateSizeTime(NetFile *file, Timer *timer);
	void updateStatus(tstring status);
	void setMarquee(bool marquee, bool total = true);
	void storeError();
	void storeError(tstring msg);
	bool downloadCancelled();
	tstring msg(string key);
	
	map<tstring, NetFile *> files; 
	DWORDLONG				filesSize;
	DWORDLONG				downloadedFilesSize;
	HINTERNET				internet;
	Timer					sizeTimeTimer;
	DWORD					errorCode;
	tstring					errorStr;
	UI                     *ui;
	SecurityOptions         securityOptions;
	tstring                 userAgent;
	bool                   *cancelPointer;
};
