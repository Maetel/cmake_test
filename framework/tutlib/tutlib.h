
#if defined (WIN32) && ( defined (BUILD_SHARED_LIBS) || defined (BUILD_STATIC_LIBS) )
#if defined (_MSC_VER)
#pragma warning(disable: 4251)
#endif
   #if defined(TUTLIB_EXPORT)
     #define  TUTLIB_EXPORT __declspec(dllexport)
   #else
     #define  TUTLIB_EXPORT __declspec(dllimport)
   #endif
#else
  #define TUTLIB_EXPORT
#endif

class TUTLIB_EXPORT TestClass
{
  public:
    int function(){
      return 100;
    }
};