#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "FlutterBmfsearchPlugin.h"
#import "BMFSearchMethodConst.h"
#import "BMFBusLineSearch.h"
#import "BMFDistrictSearch.h"
#import "BMFGeocodeSearch.h"
#import "BMFPoiSearch.h"
#import "BMFPoiSearchType.h"
#import "BMFRecommendStopSearch.h"
#import "BMFRouteSearch.h"
#import "BMFRouteSearchType.h"
#import "BMFShareURLSearch.h"
#import "BMFSuggestionSearch.h"
#import "BMFWeatherSearch.h"
#import "BMFBuslineSearchHandler.h"
#import "BMFDistrictSearchHandler.h"
#import "BMFGeoCodeSearchHandler.h"
#import "BMFPoiSearchHandler.h"
#import "BMFRecommendStopSearchHandler.h"
#import "BMFRouteSearchHandler.h"
#import "BMFSearchHandle.h"
#import "BMFSearchHandles.h"
#import "BMFSearchManager.h"
#import "BMFShareURLSearchHandler.h"
#import "BMFSuggestionSearchHandler.h"
#import "BMFWeatherSearchHandler.h"

FOUNDATION_EXPORT double flutter_baidu_mapapi_searchVersionNumber;
FOUNDATION_EXPORT const unsigned char flutter_baidu_mapapi_searchVersionString[];

