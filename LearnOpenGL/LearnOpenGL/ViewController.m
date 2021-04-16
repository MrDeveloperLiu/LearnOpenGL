//
//  ViewController.m
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#import "ViewController.h"
#import "LGLView.h"

#include "LGLRenderRect.h"
#include "LGLRenderLight.h"
#include "LGLRenderTexture.h"



@interface ViewController ()
@property (nonatomic, strong) LGLView *glView;
@end

@implementation ViewController

- (void)dealloc{
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self startOpenGL];
}

- (void)startOpenGL{
    _glView = [[LGLView alloc] initWithFrame:self.view.bounds];
//    _glView.protocol = lgl_rect_protocol();
//    _glView.protocol = lgl_light_protocol();
    _glView.protocol = lgl_texture_protocol();
    [self.view addSubview:_glView];
}
@end
