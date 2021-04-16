//
//  FlutterComponents.h
//  LearnOpenGL
//
//  Created by zuer on 2021/4/12.
//

#import <Foundation/Foundation.h>
#import <Flutter/Flutter.h>
#import <GeneratedPluginRegistrant.h>

NS_ASSUME_NONNULL_BEGIN

@interface FlutterComponents : NSObject
@property (nonatomic, strong, readonly) FlutterEngine *flt;
@property (nonatomic, strong, readonly) FlutterViewController *fltController;


+ (FlutterComponents *)components;

- (void)startFlutterWithWindow:(UIWindow *)window;
- (void)startFlutterWithViewController:(UIViewController *)vc;
@end


NS_ASSUME_NONNULL_END
