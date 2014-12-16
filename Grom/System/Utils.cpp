// Free open-source Grom library

#include "Grom/System/PrecompiledHeader.h"

#ifdef CFG_POSIX
#  include <unistd.h>
#endif

#include "Grom/System/Exception.h"
#include "Grom/System/Utils.h"

namespace Sys
{

void RunTimeAssert(bool statement)
{
  if (!statement)
    throw new SystemException("internal error: run-time assertion failed");
}

void ValidateIndex(int index, int count)
{
  if (index < 0 || index >= count)
    throw CreateIndexOutOfBoundsException(index);
}

void ValidateRange(int index, int range, int count)
{
  if (index < 0 || range < 0 || index + range > count)
    throw CreateRangeOutOfBoundsException(index, range);
}

int NormalizeRange(int index, int range, int count)
{
  if (index + range > count)
    range = count - index;
  return range;
}

void Sleep(int milliseconds)
{
#ifdef CFG_WIN32
  ::Sleep(milliseconds);
#endif
#ifdef CFG_POSIX
  usleep(milliseconds * 1000);
#endif
}

} // namespace Sys
