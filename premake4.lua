 solution "lls"
  configurations { "Debug", "Release" }
 
  configuration { "Debug" }
    targetdir "./build/debug"
  configuration { "Release" }
    targetdir "./build/release"

  if _ACTION == "clean" then
    os.rmdir("./build")
  end

project "lls"
    language    "C"
    kind        "ConsoleApp"
    includedirs    { "inc/", 
                     "exp/",
                     "/Library/Frameworks/GStreamer.framework/Headers/"
                   }

    files          { 
                     "src/main.c",
                     "src/conn_serv.c",
                     "src/nw_streamer.c",
                     "src/media_serv.c"
                   }
    location         "build"
    buildoptions   { "`pkg-config --cflags glib-2.0 gio-2.0`" }
    linkoptions    { "`pkg-config --libs glib-2.0 gio-2.0`" }
--@{linux
    buildoptions   { "`pkg-config --cflags gstreamer-1.0`" }
    linkoptions    { "`pkg-config --libs gstreamer-1.0`" }
--@}linux
    libdirs        { "/Library/Frameworks/GStreamer.framework/Libraries/" }
    links          { "gstreamer-1.0" }
