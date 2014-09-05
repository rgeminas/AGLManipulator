#include "HttpWrapper.h"

#include <Windows.h>
#include <winhttp.h>
#include <vector>
#include <sstream>
#include "arduino.h"

namespace agl
{
	std::string
	ReadHttpData(const std::wstring& server,
			const std::wstring& resource,
			const std::wstring& method)
	{
		DWORD dwSize = 0;
		DWORD dwDownloaded = 0;
		LPSTR pszOutBuffer;
		std::vector<std::string>  vFileContent;
		BOOL  bResults = FALSE;
		HINTERNET  hSession = NULL,
			hConnect = NULL,
			hRequest = NULL;

		// Use WinHttpOpen to obtain a session handle.
		hSession = WinHttpOpen(L"WinHTTP Example/1.0",
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS, 0);

		// Specify an HTTP server.
		if (hSession)
			hConnect = WinHttpConnect(hSession, server.c_str(),
			INTERNET_DEFAULT_HTTP_PORT, 0);

		// Create an HTTP request handle.
		if (hConnect)
			hRequest = WinHttpOpenRequest(hConnect, method.c_str(), resource.c_str(),
			NULL, WINHTTP_NO_REFERER,
			NULL,
			NULL);

		// Send a request.
		if (hRequest)
			bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0, WINHTTP_NO_REQUEST_DATA, 0,
			0, 0);


		// End the request.
		if (bResults)
			bResults = WinHttpReceiveResponse(hRequest, NULL);

		// Keep checking for data until there is nothing left.
		if (bResults)
		do
		{
			// Check for available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				Log(L"Error %u in WinHttpQueryDataAvailable.\n",
				GetLastError());

			// Allocate space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				Log(L"Out of memory\n");
				dwSize = 0;
			}
			else
			{
				// Read the Data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded))
				{
					Log(L"Error %u in WinHttpReadData.\n",
						GetLastError());
				}
				else
				{
					Log(L"%s", pszOutBuffer);
					// Data in vFileContent
					vFileContent.push_back(pszOutBuffer);
				}

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}

		} while (dwSize > 0);


		// Report any errors.
		if (!bResults)
			Log(L"Error %d has occurred.\n", GetLastError());

		// Close any open handles.
		if (hRequest) WinHttpCloseHandle(hRequest);
		if (hConnect) WinHttpCloseHandle(hConnect);
		if (hSession) WinHttpCloseHandle(hSession);

		std::stringstream strbuf;
		for (auto str : vFileContent)
		{
			strbuf << str;
		}
		return strbuf.str();
	}
}