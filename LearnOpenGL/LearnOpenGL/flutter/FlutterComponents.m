//
//  FlutterComponents.m
//  LearnOpenGL
//
//  Created by zuer on 2021/4/12.
//

#import "FlutterComponents.h"
#import "AppDelegate.h"

@interface FlutterComponents ()
@property (nonatomic, strong) FlutterEngine *flt;
@property (nonatomic, strong) FlutterViewController *fltController;
@property (nonatomic, strong) FlutterMethodChannel *methodChannel;
@end

@implementation FlutterComponents

+ (FlutterComponents *)components{
    static FlutterComponents *_instance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _instance = [self new];
    });
    return _instance;
}

- (FlutterEngine *)flt{
    if (!_flt) {
        _flt = [[FlutterEngine alloc] initWithName:@"Flutter" project:nil];
        [_flt runWithEntrypoint:nil];
        [GeneratedPluginRegistrant registerWithRegistry:_flt];
    }
    return _flt;
}

- (FlutterViewController *)fltController{
    if (!_fltController) {
        _fltController = [[FlutterViewController alloc] initWithEngine:self.flt nibName:nil bundle:nil];
        //flt2native channel
        _methodChannel = [FlutterMethodChannel methodChannelWithName:@"com.flutter" binaryMessenger:(id<FlutterBinaryMessenger>)_fltController];
        [_methodChannel setMethodCallHandler:^(FlutterMethodCall * _Nonnull call, FlutterResult  _Nonnull result) {
            //list
        }];
        //native2flutter
//        [_methodChannel invokeMethod:@"launched" arguments:nil result:nil];    
    }
    return _fltController;
}

- (void)startFlutterWithWindow:(UIWindow *)window{
    NSAssert([window isKindOfClass:UIWindow.class], @"startFlutterWithWindow: must be a UIWindow");
    window.rootViewController = self.fltController;
}

- (void)startFlutterWithViewController:(UIViewController *)vc{
    NSAssert([vc isKindOfClass:UIViewController.class], @"startFlutterWithViewController: must be a UIViewController");
    [vc presentViewController:self.fltController animated:YES completion:nil];
}


@end
