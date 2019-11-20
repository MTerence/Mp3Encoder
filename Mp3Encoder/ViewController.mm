//
//  ViewController.m
//  Mp3Encoder
//
//  Created by Ternence on 2019/11/20.
//  Copyright © 2019 machao. All rights reserved.
//

#import "ViewController.h"
#import "mp3_encoder.hpp"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    UIButton *encodeBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    [encodeBtn setTitle:@"Encoder" forState:UIControlStateNormal];
    encodeBtn.backgroundColor = [UIColor lightGrayColor];
    encodeBtn.frame = CGRectMake((self.view.frame.size.width - 100)/2, (self.view.frame.size.height - 40)/2, 100, 40);
    [encodeBtn addTarget:self action:@selector(onEncoderBtnClick) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:encodeBtn];
}

- (void)onEncoderBtnClick{
    Mp3Encoder *encoder = new Mp3Encoder();
    const char *pcmFilePath = [[[[NSBundle mainBundle]bundlePath] stringByAppendingPathComponent:@"NocturneNo2inEflat_44.1k_s16le.pcm"]cStringUsingEncoding:NSUTF8StringEncoding];
    const char *mp3FilePath = [[self documentsPath:@"NocturneNo2inEflat_44.1k_s16le.mp3"]cStringUsingEncoding:NSUTF8StringEncoding];
    NSLog(@"filePath: %s",mp3FilePath);
    int sampleRate = 44100;
    int channels = 2;
    int bitRate = 128 * 1024;
    encoder->Init(pcmFilePath, mp3FilePath, sampleRate, channels, bitRate);
    encoder->Encode();
    encoder->Destory();
    delete encoder;
    
    NSLog(@"Encoder Success");
    
}

- (NSString *)documentsPath:(NSString *)fileName{
    NSArray *path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [path objectAtIndex:0];
    return [documentsDirectory stringByAppendingPathComponent:fileName];
}


@end
