//
//  LGLView.m
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#import "LGLView.h"


@interface LGLView ()
@property (nonatomic, assign) NSTimeInterval renderTs;
@property (nonatomic, assign) NSInteger renderFps;
@property (nonatomic, assign) NSInteger renderCount;
@end

@implementation LGLView

- (void)dealloc{
    if (_renderBuffer) glDeleteRenderbuffers(1, &_renderBuffer);
    if (_frameBuffer) glDeleteFramebuffers(1, &_frameBuffer);
}

+ (Class)layerClass{ return CAEAGLLayer.class; }

- (instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    
    self.contentScaleFactor = UIScreen.mainScreen.scale;
    _glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    if (!_glContext) {
        return nil;
    }
    [EAGLContext setCurrentContext:_glContext];
    _glLayer = (CAEAGLLayer *)self.layer;
    _glLayer.opaque = NO;
    _glLayer.drawableProperties = @{
        kEAGLDrawablePropertyRetainedBacking : @(NO),
        kEAGLDrawablePropertyColorFormat : kEAGLColorFormatRGBA8
    };
                
    glGenRenderbuffers(1, &_renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
    [_glContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:_glLayer];
    
    glGenFramebuffers(1, &_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _renderBuffer);
        
    _camera = [[LCamera alloc] init];
    _camera.ratio = CGRectGetWidth(frame)/CGRectGetHeight(frame);
    _camera.pos = GLKVector3Make(0, 0, 4);
    [self GLGuesture];
    return self;
}

- (void)setProtocol:(LGLViewProtocol)protocol{
    if ((&_protocol) == (&protocol)) {
        return;
    }
    _protocol = protocol;
    _protocol.bridge_ctx = (__bridge void *)self;
    _protocol.mvp_bridge = mvp_bridge;
    _protocol.viewport_bridge = viewport_bridge;
    _protocol.mvp_light_bridge = mvp_light_bridge;
    _protocol.camera_eye = camera_eye;
}

void mvp_bridge(struct LGLViewProtocol *protocol, GLuint program)
{
    LGLView *v = (__bridge LGLView *)protocol->bridge_ctx;
    
    //物体
    GLuint midx = glGetUniformLocation(program, protocol->m_name);
    GLKMatrix4 model = GLKMatrix4Identity;
    glUniformMatrix4fv(midx, 1, GL_FALSE, model.m);
    //观察
    GLuint vidx = glGetUniformLocation(program, protocol->v_name);
    GLKMatrix4 view = [v.camera view];
    glUniformMatrix4fv(vidx, 1, GL_FALSE, view.m);
    //投影
    GLuint pidx = glGetUniformLocation(program, protocol->p_name);
    GLKMatrix4 projection = [v.camera projection];
    glUniformMatrix4fv(pidx, 1, GL_FALSE, projection.m);
}

void mvp_light_bridge(struct LGLViewProtocol *protocol, GLuint program, GLfloat p[3])
{
    LGLView *v = (__bridge LGLView *)protocol->bridge_ctx;
    
    //物体
    GLuint midx = glGetUniformLocation(program, protocol->m_name);
    GLKMatrix4 model = GLKMatrix4MakeTranslation(p[0], p[1], p[2]);
    model = GLKMatrix4Scale(model, 0.2, 0.2, 0.2);
    glUniformMatrix4fv(midx, 1, GL_FALSE, model.m);
    //观察
    GLuint vidx = glGetUniformLocation(program, protocol->v_name);
    GLKMatrix4 view = [v.camera view];
    glUniformMatrix4fv(vidx, 1, GL_FALSE, view.m);
    //投影
    GLuint pidx = glGetUniformLocation(program, protocol->p_name);
    GLKMatrix4 projection = [v.camera projection];
    glUniformMatrix4fv(pidx, 1, GL_FALSE, projection.m);
}

void camera_eye(struct LGLViewProtocol *protocol, GLfloat *eyes, GLfloat *front)
{
    if (eyes) {
        LGLView *v = (__bridge LGLView *)protocol->bridge_ctx;
        eyes[0] = v.camera.pos.x;
        eyes[1] = v.camera.pos.y;
        eyes[2] = v.camera.pos.z;
    }
    if (front) {
        LGLView *v = (__bridge LGLView *)protocol->bridge_ctx;
        front[0] = v.camera.front.x;
        front[1] = v.camera.front.y;
        front[2] = v.camera.front.z;
    }
}

void viewport_bridge(struct LGLViewProtocol *protocol)
{
    LGLView *v = (__bridge LGLView *)protocol->bridge_ctx;
    
    glViewport(0, 0,
               CGRectGetWidth(v.frame) * v.contentScaleFactor,
               CGRectGetHeight(v.frame) * v.contentScaleFactor);
}

#define kAvoid 0
#define kFps 0

- (void)render{
#if kAvoid
    if (!_camera.needDisplay) {
        return;
    }
    [_camera setDisplayed];
#endif
    if (_protocol.clear) {
        _protocol.clear(&_protocol);
    }
    if (_protocol.render) {
        _protocol.render(&_protocol);
    }
    [_glContext presentRenderbuffer:GL_RENDERBUFFER];
#if kFps
    [self countingFps];
#endif
}

- (void)countingFps{
    NSTimeInterval now = [[NSDate date] timeIntervalSince1970];
    if (_renderTs <= 0) {
        _renderTs = now;
    }
    if (now - _renderTs >= 1) {
        _renderTs = now;
        self.renderFps = _renderCount;
        _renderCount = 0;
    }else{
        _renderCount ++;
    }
}

- (void)setRenderFps:(NSInteger)renderFps{
    _renderFps = renderFps;
    NSLog(@"fps: %td", renderFps);
}

- (void)start{
    if (_protocol.start) {
        _protocol.start(&_protocol);
    }
    if (_protocol.create_program) {
        _protocol.create_program(&_protocol);
    }
    _displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render)];
    [_displayLink addToRunLoop:NSRunLoop.mainRunLoop forMode:NSRunLoopCommonModes];
}

- (void)stop{
    [_displayLink invalidate];
    _displayLink = nil;
    
    if (_protocol.stop) {
        _protocol.stop(&_protocol);
    }
    if (_protocol.delete_program) {
        _protocol.delete_program(&_protocol);
    }
}


- (void)GLGuesture{
    UIPinchGestureRecognizer *pinchGR = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(pinchGRAction:)];
    [self addGestureRecognizer:pinchGR];
    
    UIPanGestureRecognizer *panGR = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(panGRAction:)];
    [self addGestureRecognizer:panGR];

}

- (void)pinchGRAction:(id)sender{
    [self.camera pinchGRAction:sender];
}

- (void)panGRAction:(id)sender{
    [self.camera panGRAction:sender view:self];
}

@end
