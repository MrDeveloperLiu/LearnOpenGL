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

#import "BMFFileManager.h"
#import "FlutterBmfmapPlugin.h"
#import "BMFAnnotationHandles.h"
#import "BMFAnnotationViewManager.h"
#import "BMFHeatMapHandles.h"
#import "BMFMapView.h"
#import "BMFMapViewController.h"
#import "BMFMapViewHandle.h"
#import "BMFMapViewHandles.h"
#import "BMFOverlayHandles.h"
#import "BMFOverlayViewManager.h"
#import "BMFProjectionHandles.h"
#import "BMFUserLocationHandles.h"
#import "BMFAnnotation.h"
#import "BMFArcline.h"
#import "BMFCircle.h"
#import "BMFGroundOverlay.h"
#import "BMFPolygon.h"
#import "BMFPolyline.h"
#import "BMFAsyncTileLayer.h"
#import "BMFSyncTileLayer.h"
#import "BMFURLTileLayer.h"
#import "BMFAnnotationMethodConst.h"
#import "BMFHeatMapConst.h"
#import "BMFMapCallBackConst.h"
#import "BMFMapMethodConst.h"
#import "BMFOfflineMapMethodConst.h"
#import "BMFOverlayMethodConst.h"
#import "BMFProjectionConst.h"
#import "BMFUserLocationConst.h"
#import "BMFAnnotationModel.h"
#import "BMFArclineModel.h"
#import "BMFCircleModel.h"
#import "BMFEdgeInsets.h"
#import "BMFGroundModel.h"
#import "BMFHeatMapModel.h"
#import "BMFHollowShapeModel.h"
#import "BMFIndoorMapInfoModel.h"
#import "BMFMapPoiModel.h"
#import "BMFMapStatusModel.h"
#import "BMFOLSearchRecordModel.h"
#import "BMFPolygonModel.h"
#import "BMFPolylineModel.h"
#import "BMFTileModel.h"
#import "BMFUserLocationModel.h"
#import "BMFOfflineMap.h"
#import "BMFOfflineMapHandle.h"
#import "BMFOfflineMapHandles.h"
#import "BMFOfflineMapManager.h"

FOUNDATION_EXPORT double flutter_baidu_mapapi_mapVersionNumber;
FOUNDATION_EXPORT const unsigned char flutter_baidu_mapapi_mapVersionString[];

