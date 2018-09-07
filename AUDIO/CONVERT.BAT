D:\Apps\ffmpeg-20180903-23fe072-win64-static\bin\ffmpeg -i DRAGON.WAV -ar 25033 -y -f s8 -c:a pcm_s8 -af "pan=mono|c0=c1" loop.raw
D:\Apps\ffmpeg-20180903-23fe072-win64-static\bin\ffmpeg -i OH_YES.WAV -ar 12517 -y -f s8 -c:a pcm_s8 -af "pan=mono|c0=c1" voice.raw
D:\Apps\ffmpeg-20180903-23fe072-win64-static\bin\ffmpeg -i ARCHERY.WAV -ar 12517 -y -f s8 -c:a pcm_s8 stereo.raw