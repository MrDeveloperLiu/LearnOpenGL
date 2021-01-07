//
//  LCamera.h
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#import <Foundation/Foundation.h>

#import <GLKit/GLKit.h>
#import <CoreGraphics/CoreGraphics.h>

@interface LCamera : NSObject

@property (nonatomic) GLfloat ratio;

@property (nonatomic) GLKVector3 pos;
@property (nonatomic) GLKVector3 front;
@property (nonatomic) GLKVector3 up;
@property (nonatomic) GLKVector3 right;
@property (nonatomic) GLKVector3 worldUp;

@property (nonatomic) GLfloat pitch;//俯仰角
@property (nonatomic) GLfloat yaw;//偏航角

@property (nonatomic) GLfloat fov;//视野
@property (nonatomic) GLfloat near;//近视点
@property (nonatomic) GLfloat far;//远视点

@property (nonatomic) UIEdgeInsets insets;//正射投影值

@property (nonatomic) GLfloat horizontalSpeed;
@property (nonatomic) GLfloat verticalSpeed;

@property (nonatomic) GLKMatrix4 view;
@property (nonatomic) GLKMatrix4 projection;

@property (nonatomic) BOOL perspective;

@property (nonatomic, readonly) BOOL needDisplay;

- (GLKMatrix4)perspectiveProjection;
- (GLKMatrix4)othroProjection;
@end


@interface LCamera (Guesture)
- (void)pinchGRAction:(UIPinchGestureRecognizer *)sender;
- (void)panGRAction:(UIPanGestureRecognizer *)sender view:(UIView *)view;
@end


@interface LCamera (Update)
- (void)updateView;
- (void)updateProjection;
- (void)setDisplayed;
@end
