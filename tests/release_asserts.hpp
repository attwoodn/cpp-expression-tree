#pragma once

#ifdef NDEBUG
  #undef NDEBUG
    #include <cassert>
      #define NDEBUG
#else
    #include <cassert>
#endif