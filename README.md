# Mp3Encoder

lame库将pcm音频数据转mp3编码格式


## lame包编译 [https://www.jianshu.com/p/685c2de554c1](https://www.jianshu.com/p/685c2de554c1)

编码相关代码是在 mp3_encoder.hpp  、mp3_encoder.cpp两个C++类中实现

mp3_encoder.hpp 代码

<h1> class Mp3Encoder {
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
<<<<<<< HEAD
};

mp3_encoder.hpp 代码
