//
//  LGLBridgeOC.h
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//
#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#endif

extern const char *lgl_filepath(const char *name);

extern int lgl_read_jpg(const char *name, int *w, int *h, uint8_t **buf, size_t *buf_size);
