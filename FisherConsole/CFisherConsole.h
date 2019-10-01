#pragma once

#ifdef FISHER_EXPORT
#define FISHER_API __declspec(dllexport)
#else
#define FISHER_API __declspec(dllimport)
#endif  // FISHER_EXPORT
