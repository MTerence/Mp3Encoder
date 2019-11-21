//
//  mp3_encoder.cpp
//  Mp3Encoder
//
//  Created by Ternence on 2019/11/20.
//  Copyright © 2019 machao. All rights reserved.
//

#include "mp3_encoder.hpp"


int Mp3Encoder::Init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate) {
    int ret = -1;
    //以读二进制文件的方式打开pcm音频数据，
    pcmFile = fopen(pcmFilePath, "rb");
    if (pcmFile) {
        //以写入二进制文件的方式打开MP3文件
        mp3File = fopen(mp3FilePath, "wb");
        if (mp3File) {
            //初始化lame
            lameClient = lame_init();
            lame_set_in_samplerate(lameClient, sampleRate);
            lame_set_out_samplerate(lameClient, sampleRate);
            lame_set_num_channels(lameClient, channels);
            lame_set_brate(lameClient, bitRate/1000);
            lame_init_params(lameClient);
            ret = 0;
        }
    }
    return  ret;
}

void Mp3Encoder::Encode() {
    int buffer_size = 1024 * 256;
    short *buffer = new short[buffer_size/2]();
    short *leftbuffer = new short[buffer_size/4]();
    short *rightbuffer = new short[buffer_size/4]();
    unsigned char *mp3_buffer = new unsigned char[buffer_size]();
    size_t read_bufferSize = 0;
    //while循环，每次读取一段buffer_size大小的pcm数据buffer，然后编码该buffer
    while ((read_bufferSize = fread(buffer, 2, buffer_size/2, pcmFile)) > 0) {
        //在编码buffer之前，将该buffer的左右声道拆分开
        for (int i = 0; i < read_bufferSize; i++) {
            if (i % 2 == 0) {
                leftbuffer[i/2] = buffer[i];
            }else {
                rightbuffer[i/2] = buffer[i];
            }
        }
        //lame编码器编码
        size_t wrote_size = lame_encode_buffer(lameClient, (short int *)leftbuffer, (short int *)rightbuffer, (int)(read_bufferSize/2), mp3_buffer, buffer_size);
        //将编码之后的数据写入MP3文件中
        fwrite(mp3_buffer, 1, wrote_size, mp3File);
    }
    
    delete [] buffer;
    delete [] leftbuffer;
    delete [] rightbuffer;
    delete [] mp3_buffer;
}

//关闭pcm文件，MP3文件，销毁lame
void Mp3Encoder:: Destory() {
    if (pcmFile) {
        fclose(pcmFile);
    }
    
    if (mp3File) {
        fclose(mp3File);
        lame_close(lameClient);
    }
}
