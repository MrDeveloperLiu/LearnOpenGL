//
//  AppDelegate.m
//  LearnOpenGL
//
//  Created by zuer on 2020/12/31.
//

#import "AppDelegate.h"
#import "ViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];    
    [self.window makeKeyAndVisible];
//    self.window.rootViewController = [ViewController new];
    [FlutterComponents.components startFlutterWithWindow:self.window];
    
    return YES;
}


@end
