#ifndef AGL_HTTP_WRAPPER_H
#define AGL_HTTP_WRAPPER_H

#include <string>


namespace agl
{
	std::string
	ReadHttpData(const std::wstring& server,
			const std::wstring& resource,
			const std::wstring& method = L"GET");
}
#endif // AGL_HTTP_WRAPPER_H