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
    int Init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate);
    void Encode();
    void Destory();
};

#endif /* mp3_encoder_hpp */
