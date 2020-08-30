#pragma once

#include <iostream>
#include <string>
#include <SDL.h>

/* Get the resource path for resources located in Resources/subDir */
std::string getResourcePath(const std::string& subDir = "")
{
	// We need to choose the path seperator properly base on which
	// platform we're running on, since Windows uses a different
	// seperator than most systems
#ifdef __WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	// This will hold the base resource path
	// We give it static lifetime so that we'll only need to call
	// SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty())
	{
		// SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char* basePath = SDL_GetBasePath();
		if (basePath)
		{
			baseRes = basePath;
			SDL_free(basePath);
		}
		else
		{
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		baseRes = baseRes + ".." + PATH_SEP + "Resources" + PATH_SEP;
	}
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}