#pragma once
#ifndef UDSC2_INTERNAL_EXPORT_H
#define UDSC2_INTERNAL_EXPORT_H

#ifndef UDSC2_API
#   if (defined _WIN32 || defined _WIN64) && defined UDSC2_SHARED
#       ifdef UDSC2_BUILD
#           define UDSC2_API __declspec(dllexport)
#       else
#           define UDSC2_API __declspec(dllimport)
#   endif // UDSC2_BUILD
#   else
#       define UDSC2_API
#   endif // WIN && UDSC2_SHARED
#endif // UDSC2_API

#endif // UDSC2_INTERNAL_EXPORT_H
