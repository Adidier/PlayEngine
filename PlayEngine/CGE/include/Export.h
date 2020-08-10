#ifndef _EXPORT_H_
#define _EXPORT_H_

#ifdef PLAYENGINE_EXPORTS
#define PLAYENGINE __declspec(dllexport)
#else
#define PLAYENGINE __declspec(dllimport)
#endif


#endif