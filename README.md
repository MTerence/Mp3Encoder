# Mp3Encoder

####lame库将pcm音频数据转mp3编码格式，以iOS为例，具体编码方法类是`c++`所写，**`iOS`** 和**`Android`** 都可用, 

####Android导入lame静态库后， 直接导入mp3_encoder.hpp  mp3_encoder.cpp类调用即可转码

#### lame包编译参考[https://www.jianshu.com/p/685c2de554c1](https://www.jianshu.com/p/685c2de554c1)

编码相关代码是在 mp3_encoder.hpp  、mp3_encoder.cpp两个C++类中实现

**`mp3_encoder.hpp `**代码

```
class Mp3Encoder {
    private:
    FILE *pcmFile;
    FILE *mp3File;
lame_t lameClient;

public:
    //Init接口，输入pcm文件路径 、mp3存储文件路径, 采样率、声道数、比特率设置
    int Init(const char *pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate);
    //读取pcm数据，调用lame编码
    void Encode();
    //内存释放，销毁资源
    void Destory();
};

```

**`mp3_encoder.cpp`** 代码

```
//初始化lame
int Mp3Encoder::Init(const char *pcmFilePath, const char *mp3FilePath, int  sampleRate, int channels, int bitRate) {
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

//编码方法
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
```
