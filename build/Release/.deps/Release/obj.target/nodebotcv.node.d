cmd_Release/obj.target/nodebotcv.node := flock ./Release/linker.lock g++ -shared -pthread -rdynamic -m64  -Wl,-soname=nodebotcv.node -o Release/obj.target/nodebotcv.node -Wl,--start-group Release/obj.target/nodebotcv/main.o -Wl,--end-group /usr/local/lib/libopencv_bioinspired.so /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_cuda.so /usr/local/lib/libopencv_cudaarithm.so /usr/local/lib/libopencv_cudabgsegm.so /usr/local/lib/libopencv_cudacodec.so /usr/local/lib/libopencv_cudafeatures2d.so /usr/local/lib/libopencv_cudafilters.so /usr/local/lib/libopencv_cudaimgproc.so /usr/local/lib/libopencv_cudaoptflow.so /usr/local/lib/libopencv_cudastereo.so /usr/local/lib/libopencv_cudawarping.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_ocl.so /usr/local/lib/libopencv_optim.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_shape.so /usr/local/lib/libopencv_softcascade.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_superres.so /usr/local/lib/libopencv_ts.a /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so /usr/lib/x86_64-linux-gnu/libXext.so /usr/lib/x86_64-linux-gnu/libX11.so /usr/lib/x86_64-linux-gnu/libICE.so /usr/lib/x86_64-linux-gnu/libSM.so /usr/lib/x86_64-linux-gnu/libGL.so /usr/lib/x86_64-linux-gnu/libGLU.so -lrt -lpthread -lm -ldl
