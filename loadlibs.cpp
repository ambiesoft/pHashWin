
#ifdef _DEBUG
#pragma message("Loading Debug libs")

#pragma comment(lib, "libpng16d.lib")
#pragma comment(lib, "libsndfile-1.lib")
#pragma comment(lib, "libsamplerate-0.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "zlibd.lib")

#else
#pragma message("Loading Release libs")

#pragma comment(lib, "libpng16.lib")
#pragma comment(lib, "libsndfile-1.lib")
#pragma comment(lib, "libsamplerate-0.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "zlib.lib")
#endif