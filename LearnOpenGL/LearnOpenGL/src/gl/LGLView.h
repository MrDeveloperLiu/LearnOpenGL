//
//  LGLView.h
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#ifdef __OBJC__
#import <UIKit/UIKit.h>
#import "LCamera.h"
#endif

#include "LGLProgram.h"


@interface LGLView : UIView

@property (nonatomic, strong) LCamera *camera;

@property (nonatomic, strong) CAEAGLLayer *glLayer;
@property (nonatomic, strong) EAGLContext *glContext;

@property (nonatomic) GLuint frameBuffer;
@property (nonatomic) GLuint renderBuffer;

@property (nonatomic, strong) CADisplayLink *displayLink;

@property (nonatomic) LGLViewProtocol protocol;

- (void)start;
- (void)stop;

@end
