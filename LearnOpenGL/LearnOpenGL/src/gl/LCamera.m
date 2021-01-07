//
//  LCamera.m
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#import "LCamera.h"



typedef enum {
    Unkown = 0,
    Horizontal = 1,
    Vertical,
} Dirction;



@implementation LCamera

- (instancetype)init{
    self = [super init];
    
    _pitch = 0;
    _yaw = GLKMathDegreesToRadians(-90);
    
    _pos = GLKVector3Make(0, 0, 3);
    _worldUp = GLKVector3Make(0, 1, 0);
    
    _fov = 45;
    _near = 0.3;
    _far = 100;
    
    _horizontalSpeed = 0.08;
    _verticalSpeed = 0.08;
    
    _perspective = YES;
    
    [self updateView];
    [self updateProjection];
    return self;
}


- (GLKMatrix4)perspectiveProjection{
    GLKMatrix4 p = GLKMatrix4MakePerspective(GLKMathDegreesToRadians(_fov), _ratio, _near, _far);
    return p;
}

- (GLKMatrix4)othroProjection{
    GLKMatrix4 p = GLKMatrix4MakeOrtho(_insets.left, _insets.right, _insets.bottom, _insets.top, _near, _far);
    return p;
}

@end


@implementation LCamera (Guesture)

- (void)pinchGRAction:(UIPinchGestureRecognizer *)sender{
    static CGFloat from = 0;
    if (sender.state == UIGestureRecognizerStateBegan)
    {
        from = sender.scale;
    }
    else if (sender.state == UIGestureRecognizerStateChanged)
    {
        CGFloat detla = sender.scale - from;
        GLfloat fov = self.fov + detla;
        if (fov < 1) fov = 1;
        if (fov > 45) fov = 45;
        self.fov = fov;
    }
    else
    {
        from = 0;
    }
}

- (void)panGRAction:(UIPanGestureRecognizer *)sender view:(UIView *)view{
    static Dirction direction = Unkown;
    static BOOL pitch = NO;
    CGPoint velocity = [sender velocityInView:view];
    if (sender.state == UIGestureRecognizerStateBegan)
    {
        pitch = (sender.numberOfTouches > 1);
        direction = (fabs(velocity.x) > fabs(velocity.y)) ? Horizontal : Vertical;
    }
    else if (sender.state == UIGestureRecognizerStateChanged)
    {
        CGPoint translate = [sender translationInView:view];
        if (pitch)
        {
            if (direction == Horizontal) {
                GLfloat degree = GLKMathRadiansToDegrees(self.yaw) + (translate.x * self.horizontalSpeed);
                self.yaw = GLKMathDegreesToRadians(degree);
            }else{
                GLfloat pi = self.pitch + translate.y;
                if (pi > 89) pi = 89;
                if (pi < -89) pi = -89;
                self.pitch = pi;
            }
        }
        else
        {
            if (direction == Horizontal) {
                //right
                if (translate.x > 0) {
                    self.pos = GLKVector3Add(self.pos, GLKVector3MultiplyScalar(GLKVector3Normalize(GLKVector3CrossProduct(self.front, self.up)), self.horizontalSpeed));
                //left
                }else{
                    self.pos = GLKVector3Subtract(self.pos, GLKVector3MultiplyScalar(GLKVector3Normalize(GLKVector3CrossProduct(self.front, self.up)), self.horizontalSpeed));
                }
                
            }else{
                //down
                if (translate.y > 0) {
                    self.pos = GLKVector3Add(self.pos, GLKVector3MultiplyScalar(self.front, self.verticalSpeed));
                //up
                }else{
                    self.pos = GLKVector3Subtract(self.pos, GLKVector3MultiplyScalar(self.front, self.verticalSpeed));
                }
            }

        }
    }
    else
    {
        direction = Unkown;
    }
    [sender setTranslation:CGPointZero inView:view];
}

@end

@implementation LCamera (Update)

- (void)setPos:(GLKVector3)pos{
    _pos = pos;
    [self updateView];
}

- (void)setUp:(GLKVector3)up{
    _up = up;
    [self updateView];
}

- (void)setFront:(GLKVector3)front{
    _front = front;
    [self updateView];
}

- (void)setPitch:(GLfloat)pitch{
    _pitch = pitch;
    [self updateView];
}

- (void)setYaw:(GLfloat)yaw{
    _yaw = yaw;
    [self updateView];
}

- (void)setFov:(GLfloat)fov{
    _fov = fov;
    [self updateProjection];
}

- (void)setRatio:(GLfloat)ratio{
    _ratio = ratio;
    [self updateProjection];
}

- (void)setNear:(GLfloat)near{
    _near = near;
    [self updateProjection];
}

- (void)setFar:(GLfloat)far{
    _far = far;
    [self updateProjection];
}

- (void)setInsets:(UIEdgeInsets)insets{
    _insets = insets;
    [self updateProjection];
}

//更新前轴（由于俯仰角与偏航角的改变，自动调用）
- (void)updateView{
    GLKVector3 front;
    front.x = cos(GLKMathDegreesToRadians(_pitch)) * cos(_yaw);
    front.y = sin(GLKMathDegreesToRadians(_pitch));
    front.z = cos(GLKMathDegreesToRadians(_pitch)) * sin(_yaw);
    //上轴
    _front = GLKVector3Normalize(front);
    //右轴
    _right = GLKVector3Normalize(GLKVector3CrossProduct(_front, _worldUp));
    //上轴
    _up = GLKVector3Normalize(GLKVector3CrossProduct(_right, _front));
    //中轴
    GLKVector3 center = GLKVector3Add(_pos, _front);
    //lookat
    _view = GLKMatrix4MakeLookAt(_pos.x, _pos.y, _pos.z, center.x, center.y, center.z, _up.x, _up.y, _up.z);
    _needDisplay = YES;
}

- (void)updateProjection{
    if (_perspective) {
        _projection = [self perspectiveProjection];
    }else{
        _projection = [self othroProjection];
    }
    _needDisplay = YES;
}

- (void)setDisplayed{
    _needDisplay = NO;
}
@end
