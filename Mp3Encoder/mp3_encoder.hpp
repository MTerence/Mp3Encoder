//
//  mp3_encoder.hpp
//  Mp3Encoder
//
//  Created by Ternence on 2019/11/20.
//  Copyright © 2019 machao. All rights reserved.
//

#ifndef mp3_encoder_hpp
#define mp3_encoder_hpp

#include <stdio.h>
#include "lame.h"


class Mp3Encoder {
private:
    FILE *pcmFile;
    FILE *mp3File;
    lame_t lameClient;
    
public:
    //Init接口，输入pcm文件路径 、mp3存储文件路径, 采样率、声道数、比特率设置
    int Init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate);
    //具体编码方法
    void Encode();
    //内存释放
    void Destory();
};

#endif /* mp3_encoder_hpp */
