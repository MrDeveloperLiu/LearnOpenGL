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
