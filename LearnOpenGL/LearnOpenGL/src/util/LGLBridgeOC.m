//
//  LGLBridgeOC.m
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#import "LGLBridgeOC.h"


const char *lgl_filepath(const char *name)
{
    if (!name) {
        return NULL;
    }
    NSString *fp = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:name] ofType:nil];
    const char *path = fp.UTF8String;
    return path;
}

int lgl_read_jpg(const char *name, int *w, int *h, uint8_t **buf, size_t *buf_size)
{
    if (!name) {
        return -1;
    }
    NSString *path = [NSBundle.mainBundle pathForResource:[NSString stringWithUTF8String:name]
                                                   ofType:nil];
    UIImage *image = [UIImage imageWithContentsOfFile:path];
    CGImageRef imageRef = image.CGImage;
    
    GLsizei width = (GLsizei)CGImageGetWidth(imageRef);
    GLsizei height = (GLsizei)CGImageGetHeight(imageRef);
    *buf_size = width * height * 4;
    *buf = calloc(*buf_size, sizeof(uint8_t));
    *w = width;
    *h = height;
    CGContextRef spriteContext = CGBitmapContextCreate(*buf,
                                                       width,
                                                       height,
                                                       8,
                                                       width * 4,
                                                       CGImageGetColorSpace(imageRef),
                                                       kCGImageAlphaPremultipliedLast);
    
    CGContextDrawImage(spriteContext, CGRectMake(0, 0, width, height), imageRef);
    CGContextRelease(spriteContext);    
    return 0;
}
